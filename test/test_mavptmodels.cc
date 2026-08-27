#include <gtest/gtest.h>
#include <cmath>
#include "../include/spiced.h"

class MavPTModelsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Test data
        R = {1.0f, 1.0f, 3.0f, 3.0f, 5.0f, 5.0f, 3.0f, 3.0f, 5.0f, 5.0f};
        M = {12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 6.0f, 6.0f, 6.0f, 6.0f};
        smr = {0.0f, -70.0f, 0.0f, -70.0f, 0.0f, -70.0f, 0.0f, -70.0f, 0.0f, -70.0f};
        
        expav = {NAN, NAN, 1.9504597f, 1.9504597f, 2.6499078f, 2.6499078f,
                 2.1929426f, 2.1929426f, 3.029526f, 3.029526f};
        
        expann = {NAN, NAN, 1.7939754f, 1.899296f, 2.5001588f, 3.7644882f,
                  1.852312f, 2.4547524f, 3.2158868f, 5.6342287f};
        
        n = 10;
        out.resize(n);
    }
    
    std::vector<float> R, M, smr, expav, expann, out;
    int n;
};

TEST_F(MavPTModelsTest, AverageMavPTModel) {
    AvMavPTModel av;
    
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

TEST_F(MavPTModelsTest, ANNMavPTModel) {
    ANNMavPTModel ann;
    
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
