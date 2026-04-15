#include <gtest/gtest.h>
#include <cmath>
#include "../include/spiced.h"

class MavPSModelsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Test data
        R = {1.0f, 1.0f, 3.0f, 3.0f, 5.0f, 5.0f, 3.0f, 3.0f, 5.0f, 5.0f};
        M = {12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 6.0f, 6.0f, 6.0f, 6.0f};
        smr = {0.0f, -70.0f, 0.0f, -70.0f, 0.0f, -70.0f, 0.0f, -70.0f, 0.0f, -70.0f};
        
        expav = {NAN, NAN, 1.3968269f, 1.3968269f, 2.1019368f, 2.1019368f,
                 1.4696023f, 1.4696023f, 1.980714f, 1.980714f};
        
        expann = {NAN, NAN, 1.3592811f, 1.485725f, 2.301059f, 2.5518396f,
                  1.5020472f, 1.6109227f, 1.8444198f, 2.7693517f};
        
        n = 10;
        out.resize(n);
    }
    
    std::vector<float> R, M, smr, expav, expann, out;
    int n;
};

TEST_F(MavPSModelsTest, AverageMavPSModel) {
    AvMavPSModel av(&_binary_mavcps_bin_start);
    
    av.Model(n, M.data(), R.data(), true, false, true, 1, 3, true, out.data());
    
    // Check results (skip first two NaN values)
    for (int i = 2; i < n; i++) {
        EXPECT_NEAR(out[i], expav[i], 0.01f) 
            << "Mismatch at index " << i << ": M=" << M[i] << ", R=" << R[i];
    }
    
    // Verify first two are NaN
    EXPECT_TRUE(std::isnan(out[0]));
    EXPECT_TRUE(std::isnan(out[1]));
}

TEST_F(MavPSModelsTest, ANNMavPSModel) {
    ANNMavPSModel ann(&_binary_mavcpsann_bin_start);
    
    ann.Model(n, M.data(), R.data(), smr.data(), true, false, true, 1, 3, true, out.data());
    
    // Check results (skip first two NaN values)
    for (int i = 2; i < n; i++) {
        EXPECT_NEAR(out[i], expann[i], 0.01f) 
            << "Mismatch at index " << i 
            << ": M=" << M[i] << ", R=" << R[i] << ", SMR=" << smr[i];
    }
    
    // Verify first two are NaN
    EXPECT_TRUE(std::isnan(out[0]));
    EXPECT_TRUE(std::isnan(out[1]));
}
