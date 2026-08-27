#include <gtest/gtest.h>
#include <cmath>
#include "../include/spiced.h"

class PSModelsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Test data
        R = {1.0f, 1.0f, 3.0f, 3.0f, 5.0f, 5.0f, 3.0f, 3.0f, 5.0f, 5.0f};
        M = {12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 6.0f, 6.0f, 6.0f, 6.0f};
        SMR = {0.0f, -70.0f, 0.0f, -70.0f, 0.0f, -70.0f, 0.0f, -70.0f, 0.0f, -70.0f};
        
        expav = {NAN, NAN, 990.28314f, 990.28314f, 148.69296f, 148.69296f,
                 1032.8657f, 1032.8657f, 151.89738f, 151.89738f};
        
        expann = {NAN, NAN, 1061.2566f, 976.14343f, 137.02544f,
                  164.9483f, 1166.6492f, 849.7204f, 145.7129f, 125.961174f};
        
        n = 10;
        out.resize(n);
    }
    
    std::vector<float> R, M, SMR, expav, expann, out;
    int n;
};

TEST_F(PSModelsTest, AveragePSModel) {
    AvPSModel av;
    
    av.Model(n, M.data(), R.data(), true, false, true, 1, 3, true, out.data());
    
    // Check results (skip first two NaN values)
    for (int i = 2; i < n; i++) {
        EXPECT_NEAR(out[i], expav[i], 0.1f) 
            << "Mismatch at index " << i << ": M=" << M[i] << ", R=" << R[i];
    }
    
    // Verify first two are NaN
    EXPECT_TRUE(std::isnan(out[0]));
    EXPECT_TRUE(std::isnan(out[1]));
}

TEST_F(PSModelsTest, ANNPSModel) {
    ANNPSModel ann(&_binary_psann_bin_start);
    
    ann.Model(n, M.data(), R.data(), SMR.data(), true, false, true, 1, 3, true, out.data());
    
    // Check results (skip first two NaN values)
    for (int i = 2; i < n; i++) {
        EXPECT_NEAR(out[i], expann[i], 0.1f) 
            << "Mismatch at index " << i 
            << ": M=" << M[i] << ", R=" << R[i] << ", SMR=" << SMR[i];
    }
    
    // Verify first two are NaN
    EXPECT_TRUE(std::isnan(out[0]));
    EXPECT_TRUE(std::isnan(out[1]));
}
