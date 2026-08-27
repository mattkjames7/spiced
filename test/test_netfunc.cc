#include <gtest/gtest.h>
#include <cmath>
#include "../include/spiced.h"

class NetworkFuncTest : public ::testing::Test {
protected:
    void SetUp() override {
        n = 3;
        R = {3.0f, 4.0f, 5.0f};
        f107 = {100.0f, 110.0f, 120.0f};
        
        // Expected output values from Python
        exp = {
            {1.2105584e+01f, 1.6899067e-01f, 7.8518517e-02f, -2.7936012e-02f, 
             -5.1193756e-01f, -9.1861486e-03f, 6.0065776e-02f},
            {8.607196f, -0.0330897f, 0.0917391f, -0.06780973f, 
             -0.2998723f, 0.00932938f, 0.04171638f},
            {5.779167f, -0.35612214f, 0.15052514f, -0.1549341f, 
             -0.09519117f, -0.00899297f, 0.02072102f}
        };
        
        // Allocate input and output arrays
        anin.resize(n);
        anout.resize(n);
        for (int i = 0; i < n; i++) {
            anin[i].resize(7);
            anout[i].resize(7);
        }
    }
    
    int n;
    std::vector<float> R, f107;
    std::vector<std::vector<float>> exp;
    std::vector<std::vector<float>> anin, anout;
};

TEST_F(NetworkFuncTest, CreateNetworkFunc) {
    // Test that we can create a NetworkFunc object
    ANNMavHModel ann;
    
    // If we get here without crashing, the object was created successfully
    SUCCEED();
}

TEST_F(NetworkFuncTest, PredictModelComponents) {
    ANNMavHModel ann;
    
    // Prepare input - rescale R and F10.7 values
    std::vector<float*> anin_ptrs(n);
    std::vector<float*> anout_ptrs(n);
    
    for (int i = 0; i < n; i++) {
        anin[i][0] = rescaleR(R[i]);
        anin[i][1] = rescaleF107(f107[i]);
        anin_ptrs[i] = anin[i].data();
        anout_ptrs[i] = anout[i].data();
    }
    
    // Predict
    ann.ann_->Predict(n, anin_ptrs.data(), anout_ptrs.data());
    
    // Verify outputs match expected values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 7; j++) {
            EXPECT_NEAR(anout[i][j], exp[i][j], 0.01f)
                << "Mismatch at row " << i << ", component " << j
                << ": R=" << R[i] << ", F10.7=" << f107[i];
        }
    }
}
