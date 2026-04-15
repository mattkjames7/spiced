#include <gtest/gtest.h>
#include <cmath>
#include "../include/spiced.h"

class MavTransTest : public ::testing::Test {
protected:
    void SetUp() override {
        n = 8;
        r = {2.0f, 2.0f, 3.0f, 3.0f, 4.0f, 4.0f, 5.0f, 5.0f};
        m = {2.0f, 5.0f, 2.0f, 5.0f, 2.0f, 5.0f, 2.0f, 5.0f};
        
        // Expected values from Python
        mtpspy = {0.47947973f, 0.7380855f, 0.28179038f, 0.3156063f, 
                  0.31757033f, 0.3726183f, 0.5091318f, 0.8288679f};
        mtptpy = {0.494816f, 0.78397655f, 0.5080598f, 0.8254361f, 
                  0.51894397f, 0.8608151f, 0.6200251f, 1.2505854f};
        
        mtps.resize(n);
        mtpt.resize(n);
        mps.resize(n);
        mpt.resize(n);
    }
    
    int n;
    std::vector<float> r, m;
    std::vector<float> mtpspy, mtptpy;
    std::vector<float> mtps, mtpt, mps, mpt;
};

TEST_F(MavTransTest, PSTransformForward) {
    MavTrans MT;
    
    MT.PSTransform(n, r.data(), m.data(), mtps.data());
    
    // Check forward transformation matches Python results
    for (int i = 0; i < n; i++) {
        EXPECT_NEAR(mtps[i], mtpspy[i], 0.001f) 
            << "PS transform mismatch at index " << i 
            << ": R=" << r[i] << ", m=" << m[i];
    }
}

TEST_F(MavTransTest, PSTransformRoundTrip) {
    MavTrans MT;
    
    // Forward transform
    MT.PSTransform(n, r.data(), m.data(), mtps.data());
    
    // Reverse transform
    MT.PSRevTransform(n, r.data(), mtps.data(), mps.data());
    
    // Should get back original m values
    for (int i = 0; i < n; i++) {
        EXPECT_NEAR(mps[i], m[i], 0.001f) 
            << "PS round-trip failed at index " << i 
            << ": R=" << r[i] << ", original m=" << m[i];
    }
}

TEST_F(MavTransTest, PTTransformForward) {
    MavTrans MT;
    
    MT.PTTransform(n, r.data(), m.data(), mtpt.data());
    
    // Check forward transformation matches Python results
    for (int i = 0; i < n; i++) {
        EXPECT_NEAR(mtpt[i], mtptpy[i], 0.001f) 
            << "PT transform mismatch at index " << i 
            << ": R=" << r[i] << ", m=" << m[i];
    }
}

TEST_F(MavTransTest, PTTransformRoundTrip) {
    MavTrans MT;
    
    // Forward transform
    MT.PTTransform(n, r.data(), m.data(), mtpt.data());
    
    // Reverse transform
    MT.PTRevTransform(n, r.data(), mtpt.data(), mpt.data());
    
    // Should get back original m values
    for (int i = 0; i < n; i++) {
        EXPECT_NEAR(mpt[i], m[i], 0.001f) 
            << "PT round-trip failed at index " << i 
            << ": R=" << r[i] << ", original m=" << m[i];
    }
}
