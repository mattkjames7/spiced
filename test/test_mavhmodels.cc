#include <gtest/gtest.h>
#include <cmath>
#include "../include/spiced.h"

class MavHModelsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Test data
        R = {1.0f, 1.0f, 3.0f, 3.0f, 5.0f, 5.0f, 3.0f, 3.0f, 5.0f, 5.0f};
        M = {12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 6.0f, 6.0f, 6.0f, 6.0f};
        f107 = {80.0f, 150.0f, 80.0f, 150.0f, 80.0f, 150.0f, 80.0f, 150.0f, 80.0f, 150.0f};
        
        expav = {NAN, NAN, 12.318951f, 12.318951f, 5.4738965f, 5.4738965f,
                 13.072797f, 13.072797f, 5.1035433f, 5.1035433f};
        
        expann = {NAN, NAN, 11.570872f, 13.486695f, 4.463351f, 7.5160146f,
                  12.105549f, 13.816255f, 4.301272f, 6.5384946f};
        
        n = 10;
        out.resize(n);
    }
    
    std::vector<float> R, M, f107, expav, expann, out;
    int n;
};

TEST_F(MavHModelsTest, AverageMavHModel) {
    AvMavHModel av;
    
    av.Model(n, M.data(), R.data(), true, false, true, 1, 3, out.data());
    
    // Check results (skip first two NaN values)
    for (int i = 2; i < n; i++) {
        EXPECT_NEAR(out[i], expav[i], 0.01f) 
            << "Mismatch at index " << i << ": M=" << M[i] << ", R=" << R[i];
    }
    
    // Verify first two are NaN
    EXPECT_TRUE(std::isnan(out[0]));
    EXPECT_TRUE(std::isnan(out[1]));
}

TEST_F(MavHModelsTest, ANNMavHModel) {
    ANNMavHModel ann(&_binary_mavhann_bin_start);
    
    ann.Model(n, M.data(), R.data(), f107.data(), true, false, true, 1, 3, out.data());
    
    // Check results (skip first two NaN values)
    for (int i = 2; i < n; i++) {
        EXPECT_NEAR(out[i], expann[i], 0.01f) 
            << "Mismatch at index " << i 
            << ": M=" << M[i] << ", R=" << R[i] << ", F10.7=" << f107[i];
    }
    
    // Verify first two are NaN
    EXPECT_TRUE(std::isnan(out[0]));
    EXPECT_TRUE(std::isnan(out[1]));
}
