#include <gtest/gtest.h>
#include <cmath>
#include "../include/spiced.h"

class PTModelsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Test data
        R = {1.0f, 1.0f, 3.0f, 3.0f, 5.0f, 5.0f, 3.0f, 3.0f, 5.0f, 5.0f};
        M = {12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 6.0f, 6.0f, 6.0f, 6.0f};
        SMR = {0.0f, -70.0f, 0.0f, -70.0f, 0.0f, -70.0f, 0.0f, -70.0f, 0.0f, -70.0f};
        
        expav = {NAN, NAN, 87.52281f, 87.52281f, 12.565765f, 12.565765f,
                 106.17181f, 106.17181f, 9.324627f, 9.324627f};
        
        expann = {NAN, NAN, 104.87785f, 62.84493f, 14.667002f, 11.64771f,
                  189.02615f, 55.981377f, 8.946179f, 3.5678644f};
        
        n = 10;
        out.resize(n);
    }
    
    std::vector<float> R, M, SMR, expav, expann, out;
    int n;
};

TEST_F(PTModelsTest, AveragePTModel) {
    AvPTModel av;
    
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

TEST_F(PTModelsTest, ANNPTModel) {
    ANNPTModel ann(&_binary_ptann_bin_start);
    
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
