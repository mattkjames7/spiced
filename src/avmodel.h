#pragma once

enum class AvModelType {
    MavH,
    MavPS,
    MavPT,
    Prob,
    PS,
    PT,
};

class AvModel {
public:
    explicit AvModel(AvModelType type);
    ~AvModel();

    AvModel(const AvModel &) = delete;
    AvModel &operator=(const AvModel &) = delete;

    void DC(int n, float *R, float *dc);
    void Model(int n, float *mlt, float *R, bool show_dc, bool only_dc,
               bool validate, int m0, int m1, float *out);
    void Model(int n, float *mlt, float *R, bool show_dc, bool only_dc,
               bool validate, int m0, int m1, bool reverse_transform,
               float *out);
    void ModelCart(int n, float *x, float *y, bool show_dc, bool only_dc,
                   bool validate, int m0, int m1, float *out);
    void ModelCart(int n, float *x, float *y, bool show_dc, bool only_dc,
                   bool validate, int m0, int m1, bool reverse_transform,
                   float *out);
    void ModelComponents(int n, float *mlt, float *R, float *dc, float **periodic);
    void ModelComponentsCart(int n, float *x, float *y, float *dc, float **periodic);

private:
    struct Impl;
    Impl *impl_;
};
