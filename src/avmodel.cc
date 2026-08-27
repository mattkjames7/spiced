#include "avmodel.h"

#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

#include <ann.h>

#include "mavtrans.h"
#include "model_params.h"
#include "polynomial.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct AvModel::Impl {
    AvModelType type;
    std::vector<float> dc;
    std::vector<std::vector<float>> real;
    std::vector<std::vector<float>> imag;
    std::unique_ptr<MavTrans> mav_transform;

    explicit Impl(AvModelType model_type) : type(model_type) {
        const ModelParams *params = nullptr;
        switch (type) {
            case AvModelType::MavH: params = &mavh; break;
            case AvModelType::MavPS: params = &mavcps; break;
            case AvModelType::MavPT: params = &mavcpt; break;
            case AvModelType::Prob: params = &prob; break;
            case AvModelType::PS: params = &ps; break;
            case AvModelType::PT: params = &pt; break;
        }
        dc = params->dc;
        real = params->real;
        imag = params->imag;

        // These models use fitted nonlinear DC parameters rather than a
        // polynomial, so restore their original binary ordering.
        if (type == AvModelType::MavH || type == AvModelType::Prob) {
            std::reverse(dc.begin(), dc.end());
        }
        if (type == AvModelType::MavPS || type == AvModelType::MavPT) {
            mav_transform = std::make_unique<MavTrans>();
        }
    }

    int component_count() const {
        return static_cast<int>(std::min(real.size(), imag.size()));
    }

    float minimum_radius() const {
        return type == AvModelType::MavPS ? 1.5f : 2.0f;
    }

    bool is_direct_model() const {
        return type == AvModelType::MavH || type == AvModelType::Prob;
    }

    bool is_mav_model() const {
        return type == AvModelType::MavH || type == AvModelType::MavPS ||
               type == AvModelType::MavPT;
    }

    void periodic_components(int n, float *mlt, float *radius, float **out) {
        std::vector<float> angle(n);
        std::vector<float> real_values(n);
        std::vector<float> imag_values(n);
        for (int point = 0; point < n; ++point) {
            angle[point] = mlt[point] * 2.0f * static_cast<float>(M_PI);
        }

        for (int component = 0; component < component_count(); ++component) {
            polynomial(static_cast<int>(real[component].size()) - 1,
                       real[component].data(), n, radius, real_values.data());
            polynomial(static_cast<int>(imag[component].size()) - 1,
                       imag[component].data(), n, radius, imag_values.data());
            const float frequency = static_cast<float>(component + 1) / 24.0f;
            for (int point = 0; point < n; ++point) {
                out[component][point] =
                    real_values[point] * std::cos(frequency * angle[point]) -
                    imag_values[point] * std::sin(frequency * angle[point]);
            }
        }
    }

    void reverse_transform(int n, float *radius, float *values) {
        switch (type) {
            case AvModelType::MavPS:
                mav_transform->PSRevTransform(n, radius, values, values);
                break;
            case AvModelType::MavPT:
                mav_transform->PTRevTransform(n, radius, values, values);
                break;
            case AvModelType::PS:
            case AvModelType::PT:
                ann::ReverseBoxCox(n, values, 0.06542969f, 0.0f, 0.0f, 1.0f, values);
                break;
            default:
                break;
        }
    }
};

AvModel::AvModel(AvModelType type) : impl_(new Impl(type)) {}

AvModel::~AvModel() { delete impl_; }

void AvModel::DC(int n, float *R, float *out) {
    switch (impl_->type) {
        case AvModelType::MavH:
            for (int i = 0; i < n; ++i) {
                out[i] = impl_->dc[0] + impl_->dc[1] /
                    (1.0f + std::exp(-impl_->dc[2] * (R[i] - impl_->dc[3])));
            }
            break;
        case AvModelType::Prob:
            for (int i = 0; i < n; ++i) {
                out[i] = -1.0f /
                    (1.0f + std::exp(-impl_->dc[0] * (R[i] - impl_->dc[1]))) + 1.0f;
            }
            break;
        default:
            polynomial(static_cast<int>(impl_->dc.size()) - 1,
                       impl_->dc.data(), n, R, out);
            if (impl_->type == AvModelType::MavPS) {
                impl_->mav_transform->PSTransform(n, R, out, out);
            } else if (impl_->type == AvModelType::MavPT) {
                impl_->mav_transform->PTTransform(n, R, out, out);
            }
            break;
    }
}

void AvModel::ModelComponents(int n, float *mlt, float *R, float *dc,
                              float **periodic) {
    DC(n, R, dc);
    impl_->periodic_components(n, mlt, R, periodic);
}

void AvModel::ModelComponentsCart(int n, float *x, float *y, float *dc,
                                  float **periodic) {
    std::vector<float> mlt(n);
    std::vector<float> radius(n);
    for (int i = 0; i < n; ++i) {
        radius[i] = std::sqrt(x[i] * x[i] + y[i] * y[i]);
        mlt[i] = std::atan2(-y[i], -x[i]) * 12.0f / static_cast<float>(M_PI);
        if (mlt[i] < 0.0f) mlt[i] += 24.0f;
    }
    ModelComponents(n, mlt.data(), radius.data(), dc, periodic);
}

void AvModel::Model(int n, float *mlt, float *R, bool show_dc, bool only_dc,
                    bool validate, int m0, int m1, float *out) {
    Model(n, mlt, R, show_dc, only_dc, validate, m0, m1, false, out);
}

void AvModel::Model(int n, float *mlt, float *R, bool show_dc, bool only_dc,
                    bool validate, int m0, int m1, bool reverse_transform,
                    float *out) {
    const int components = impl_->component_count();
    std::vector<float> dc(n);
    std::vector<std::vector<float>> periodic(components, std::vector<float>(n));
    std::vector<float *> periodic_ptrs(components);
    for (int i = 0; i < components; ++i) periodic_ptrs[i] = periodic[i].data();
    ModelComponents(n, mlt, R, dc.data(), periodic_ptrs.data());

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

    if (reverse_transform && !impl_->is_direct_model()) {
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
            } else if (impl_->type == AvModelType::Prob && show_dc) {
                out[point] = std::clamp(out[point], 0.0f, 1.0f);
            } else if (impl_->is_mav_model() && show_dc &&
                       (impl_->type == AvModelType::MavH || reverse_transform)) {
                out[point] = std::clamp(out[point], 1.0f, 16.0f);
            }
        }
    }
}

void AvModel::ModelCart(int n, float *x, float *y, bool show_dc, bool only_dc,
                        bool validate, int m0, int m1, float *out) {
    ModelCart(n, x, y, show_dc, only_dc, validate, m0, m1, false, out);
}

void AvModel::ModelCart(int n, float *x, float *y, bool show_dc, bool only_dc,
                        bool validate, int m0, int m1, bool reverse_transform,
                        float *out) {
    std::vector<float> mlt(n);
    std::vector<float> radius(n);
    for (int i = 0; i < n; ++i) {
        radius[i] = std::sqrt(x[i] * x[i] + y[i] * y[i]);
        mlt[i] = std::atan2(-y[i], -x[i]) * 12.0f / static_cast<float>(M_PI);
        if (mlt[i] < 0.0f) mlt[i] += 24.0f;
    }
    Model(n, mlt.data(), radius.data(), show_dc, only_dc, validate,
          m0, m1, reverse_transform, out);
}
