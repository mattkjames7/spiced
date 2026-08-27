#include "annmodel.h"

#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

#include "ann_model_params.h"
#include "mavtrans.h"
#include "rescale.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct ANNModel::Impl {
    ANNModelType type;
    std::unique_ptr<ann::NetworkFunc> network;
    std::unique_ptr<MavTrans> mav_transform;
    int component_count;

    explicit Impl(ANNModelType model_type) : type(model_type), component_count(0) {
        const ANNModelParams *params = nullptr;
        switch (type) {
            case ANNModelType::MavH: params = &mavhann; break;
            case ANNModelType::MavPS: params = &mavcpsann; break;
            case ANNModelType::MavPT: params = &mavcptann; break;
            case ANNModelType::Prob: params = &probann; break;
            case ANNModelType::PS: params = &psann; break;
            case ANNModelType::PT: params = &ptann; break;
        }

        std::vector<int> layers(params->layers.begin(), params->layers.end());
        network = std::make_unique<ann::NetworkFunc>(
            static_cast<int>(layers.size()), layers.data(),
            "softplus", "linear", "mean_squared");
        std::copy(params->scale0.begin(), params->scale0.end(), network->scale0_);
        std::copy(params->scale1.begin(), params->scale1.end(), network->scale1_);

        for (size_t layer = 0; layer < params->weights.size(); ++layer) {
            for (size_t row = 0; row < params->weights[layer].size(); ++row) {
                for (size_t column = 0; column < params->weights[layer][row].size(); ++column) {
                    network->W_->matrix[layer]->data[row][column] =
                        params->weights[layer][row][column];
                }
            }
        }
        for (size_t layer = 0; layer < params->biases.size(); ++layer) {
            for (size_t row = 0; row < params->biases[layer].size(); ++row) {
                for (size_t column = 0; column < params->biases[layer][row].size(); ++column) {
                    network->B_->matrix[layer]->data[row][column] =
                        params->biases[layer][row][column];
                }
            }
        }

        component_count = (network->s_[network->L_ - 1] - 1) / 2;
        if (type == ANNModelType::MavPS || type == ANNModelType::MavPT) {
            mav_transform = std::make_unique<MavTrans>();
        }
    }

    bool is_direct_model() const {
        return type == ANNModelType::MavH || type == ANNModelType::Prob;
    }

    bool is_mav_model() const {
        return type == ANNModelType::MavH || type == ANNModelType::MavPS ||
               type == ANNModelType::MavPT;
    }

    float minimum_radius() const {
        return type == ANNModelType::MavPS ? 1.5f : 2.0f;
    }

    void reverse_transform(int n, float *R, float *values) {
        switch (type) {
            case ANNModelType::MavPS:
                mav_transform->PSRevTransform(n, R, values, values);
                break;
            case ANNModelType::MavPT:
                mav_transform->PTRevTransform(n, R, values, values);
                break;
            case ANNModelType::PS:
            case ANNModelType::PT:
                for (int i = 0; i < n; ++i) values[i] = unscaleDensity(values[i]);
                break;
            default:
                break;
        }
    }
};

ANNModel::ANNModel(ANNModelType type) : impl_(new Impl(type)) {
    ann_ = impl_->network.get();
}

ANNModel::~ANNModel() { delete impl_; }

void ANNModel::ModelComponents(int n, float *mlt, float *R,
                               float *scaled_activity, float *dc,
                               float **periodic) {
    const int outputs = impl_->component_count * 2 + 1;
    std::vector<std::vector<float>> inputs(n, std::vector<float>(2));
    std::vector<std::vector<float>> predictions(n, std::vector<float>(outputs));
    std::vector<float *> input_ptrs(n);
    std::vector<float *> prediction_ptrs(n);
    for (int point = 0; point < n; ++point) {
        inputs[point][0] = rescaleR(R[point]);
        inputs[point][1] = scaled_activity[point];
        input_ptrs[point] = inputs[point].data();
        prediction_ptrs[point] = predictions[point].data();
    }
    ann_->Predict(n, input_ptrs.data(), prediction_ptrs.data());

    for (int point = 0; point < n; ++point) {
        dc[point] = predictions[point][0];
        const float angle = mlt[point] * 2.0f * static_cast<float>(M_PI);
        for (int component = 0; component < impl_->component_count; ++component) {
            const float real = predictions[point][component + 1];
            const float imag = predictions[point][component + 1 + impl_->component_count];
            const float frequency = static_cast<float>(component + 1) / 24.0f;
            periodic[component][point] =
                real * std::cos(angle * frequency) - imag * std::sin(angle * frequency);
        }
    }
}

void ANNModel::ModelComponentsCart(int n, float *x, float *y,
                                   float *scaled_activity, float *dc,
                                   float **periodic) {
    std::vector<float> mlt(n);
    std::vector<float> radius(n);
    for (int i = 0; i < n; ++i) {
        radius[i] = std::sqrt(x[i] * x[i] + y[i] * y[i]);
        mlt[i] = std::fmod(12.0f * std::atan2(-y[i], -x[i]) /
                          static_cast<float>(M_PI) + 24.0f, 24.0f);
    }
    ModelComponents(n, mlt.data(), radius.data(), scaled_activity, dc, periodic);
}

void ANNModel::Model(int n, float *mlt, float *R, float *activity,
                     bool show_dc, bool only_dc, bool validate,
                     int m0, int m1, float *out) {
    Model(n, mlt, R, activity, show_dc, only_dc, validate, m0, m1, false, out);
}

void ANNModel::Model(int n, float *mlt, float *R, float *activity,
                     bool show_dc, bool only_dc, bool validate,
                     int m0, int m1, bool reverse, float *out) {
    const int components = impl_->component_count;
    std::vector<float> dc(n);
    std::vector<float> scaled_activity(n);
    std::vector<std::vector<float>> periodic(components, std::vector<float>(n));
    std::vector<float *> periodic_ptrs(components);
    for (int i = 0; i < n; ++i) {
        scaled_activity[i] = impl_->type == ANNModelType::MavH
            ? rescaleF107(activity[i]) : rescaleSMR(activity[i]);
    }
    for (int i = 0; i < components; ++i) periodic_ptrs[i] = periodic[i].data();
    ModelComponents(n, mlt, R, scaled_activity.data(), dc.data(), periodic_ptrs.data());

    for (int point = 0; point < n; ++point) {
        out[point] = impl_->is_direct_model() && !show_dc && !only_dc ? 0.0f : dc[point];
    }
    if (!only_dc) {
        const int first = std::max(0, m0 - 1);
        const int last = std::min(components - 1, m1 - 1);
        for (int component = first; component <= last; ++component) {
            for (int point = 0; point < n; ++point) out[point] += periodic[component][point];
        }
    }

    if (reverse && !impl_->is_direct_model()) {
        impl_->reverse_transform(n, R, out);
        impl_->reverse_transform(n, R, dc.data());
    }
    if (!impl_->is_direct_model() && !only_dc && !show_dc) {
        for (int point = 0; point < n; ++point) out[point] -= dc[point];
    }

    if (validate) {
        for (int point = 0; point < n; ++point) {
            if (R[point] > 5.9f || R[point] < impl_->minimum_radius()) {
                out[point] = NAN;
            } else if (impl_->type == ANNModelType::Prob && show_dc) {
                out[point] = std::clamp(out[point], 0.0f, 1.0f);
            } else if (impl_->is_mav_model() && show_dc &&
                       (impl_->type == ANNModelType::MavH || reverse)) {
                out[point] = std::clamp(out[point], 1.0f, 16.0f);
            }
        }
    }
}

void ANNModel::ModelCart(int n, float *x, float *y, float *activity,
                         bool show_dc, bool only_dc, bool validate,
                         int m0, int m1, float *out) {
    ModelCart(n, x, y, activity, show_dc, only_dc, validate, m0, m1, false, out);
}

void ANNModel::ModelCart(int n, float *x, float *y, float *activity,
                         bool show_dc, bool only_dc, bool validate,
                         int m0, int m1, bool reverse, float *out) {
    std::vector<float> mlt(n);
    std::vector<float> radius(n);
    for (int i = 0; i < n; ++i) {
        radius[i] = std::sqrt(x[i] * x[i] + y[i] * y[i]);
        mlt[i] = std::fmod(12.0f * std::atan2(-y[i], -x[i]) /
                          static_cast<float>(M_PI) + 24.0f, 24.0f);
    }
    Model(n, mlt.data(), radius.data(), activity, show_dc, only_dc,
          validate, m0, m1, reverse, out);
}
