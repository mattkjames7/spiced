#include <gtest/gtest.h>
#include <cmath>
#include "../include/spiced.h"

class ProbModelsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Test data
        R = {1.0f, 1.0f, 3.0f, 3.0f, 5.0f, 5.0f, 3.0f, 3.0f, 5.0f, 5.0f};
        M = {12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 6.0f, 6.0f, 6.0f, 6.0f};
        SMR = {0.0f, -70.0f, 0.0f, -70.0f, 0.0f, -70.0f, 0.0f, -70.0f, 0.0f, -70.0f};
        
        expav = {NAN, NAN, 0.93885595f, 0.93885595f, 0.69902945f,
                 0.69902945f, 0.95432794f, 0.95432794f, 0.7166161f, 0.7166161f};
        
        expann = {NAN, NAN, 1.0f, 0.37598833f, 0.78744745f,
                  0.3163298f, 1.0f, 0.2835528f, 0.8313806f, 0.0f};
        
        n = 10;
        out.resize(n);
    }
    
    std::vector<float> R, M, SMR, expav, expann, out;
    int n;
};

TEST_F(ProbModelsTest, AverageProbModel) {
    AvModel av(AvModelType::Prob);
    
    av.Model(n, M.data(), R.data(), true, false, true, 1, 3, out.data());
    
    // Check results (skip first two NaN values)
    for (int i = 2; i < n; i++) {
        EXPECT_NEAR(out[i], expav[i], 0.001f) 
            << "Mismatch at index " << i << ": M=" << M[i] << ", R=" << R[i];
    }
    
    // Verify first two are NaN
    EXPECT_TRUE(std::isnan(out[0]));
    EXPECT_TRUE(std::isnan(out[1]));
}

TEST_F(ProbModelsTest, ANNProbModel) {
    ANNProbModel ann;
    
    ann.Model(n, M.data(), R.data(), SMR.data(), true, false, true, 1, 3, out.data());
    
    // Check results (skip first two NaN values)
    for (int i = 2; i < n; i++) {
        EXPECT_NEAR(out[i], expann[i], 0.001f) 
            << "Mismatch at index " << i 
            << ": M=" << M[i] << ", R=" << R[i] << ", SMR=" << SMR[i];
    }
    
    // Verify first two are NaN
    EXPECT_TRUE(std::isnan(out[0]));
    EXPECT_TRUE(std::isnan(out[1]));
}
