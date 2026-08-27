#pragma once

#include <ann.h>

enum class ANNModelType { MavH, MavPS, MavPT, Prob, PS, PT };

class ANNModel {
public:
    explicit ANNModel(ANNModelType type);
    ~ANNModel();

    ANNModel(const ANNModel &) = delete;
    ANNModel &operator=(const ANNModel &) = delete;

    void Model(int n, float *mlt, float *R, float *activity, bool show_dc,
               bool only_dc, bool validate, int m0, int m1, float *out);
    void Model(int n, float *mlt, float *R, float *activity, bool show_dc,
               bool only_dc, bool validate, int m0, int m1,
               bool reverse_transform, float *out);
    void ModelCart(int n, float *x, float *y, float *activity, bool show_dc,
                   bool only_dc, bool validate, int m0, int m1, float *out);
    void ModelCart(int n, float *x, float *y, float *activity, bool show_dc,
                   bool only_dc, bool validate, int m0, int m1,
                   bool reverse_transform, float *out);
    void ModelComponents(int n, float *mlt, float *R, float *scaled_activity,
                         float *dc, float **periodic);
    void ModelComponentsCart(int n, float *x, float *y, float *scaled_activity,
                             float *dc, float **periodic);

    ann::NetworkFunc *ann_;

private:
    struct Impl;
    Impl *impl_;
};
