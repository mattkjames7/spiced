#include <gtest/gtest.h>
#include <cmath>
#include "../include/spiced.h"

class CAPITest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize models before running tests
        initModels();
        
        // Common test data
        n = 5;
        mlt = {0.0f, 6.0f, 12.0f, 18.0f, 3.0f};
        R = {3.0f, 3.0f, 3.0f, 3.0f, 5.0f};
        out.resize(n);
        
        // For Cartesian tests
        x = {3.0f, 0.0f, -3.0f, 0.0f, 5.0f};
        y = {0.0f, 3.0f, 0.0f, -3.0f, 0.0f};
    }
    
    int n;
    std::vector<float> mlt, R, x, y, out;
};

// Tests for getAvMavH
TEST_F(CAPITest, GetAvMavH) {
    getAvMavH(n, mlt.data(), R.data(), true, false, true, 1, 3, out.data());
    
    // Verify we get reasonable output
    for (int i = 0; i < n; i++) {
        if (R[i] >= 2.0f && R[i] <= 6.0f) {
            // Within valid range - should have valid output
            EXPECT_FALSE(std::isnan(out[i])) 
                << "Valid input should not produce NaN at index " << i;
            EXPECT_GT(out[i], 0.0f) 
                << "Average ion mass should be positive at index " << i;
            EXPECT_LT(out[i], 50.0f) 
                << "Average ion mass should be < 50 amu at index " << i;
        }
    }
}

TEST_F(CAPITest, GetAvMavHCart) {
    getAvMavHCart(n, x.data(), y.data(), true, false, true, 1, 3, out.data());
    
    // Verify we get reasonable output
    for (int i = 0; i < n; i++) {
        float r = sqrt(x[i]*x[i] + y[i]*y[i]);
        if (r >= 2.0f && r <= 6.0f) {
            // Within valid range
            EXPECT_FALSE(std::isnan(out[i])) 
                << "Valid Cartesian input should not produce NaN at index " << i;
            EXPECT_GT(out[i], 0.0f) 
                << "Average ion mass should be positive at index " << i;
        }
    }
}

// Tests for getScaledMavH
TEST_F(CAPITest, GetScaledMavH) {
    std::vector<float> f107(n, 100.0f);
    
    getScaledMavH(n, mlt.data(), R.data(), f107.data(), true, false, true, 1, 3, out.data());
    
    for (int i = 0; i < n; i++) {
        if (R[i] >= 2.0f && R[i] <= 6.0f) {
            EXPECT_FALSE(std::isnan(out[i])) 
                << "Valid input should not produce NaN at index " << i;
            EXPECT_GT(out[i], 0.0f) 
                << "Scaled average ion mass should be positive at index " << i;
        }
    }
}

// Tests for getAvProb
TEST_F(CAPITest, GetAvProb) {
    getAvProb(n, mlt.data(), R.data(), true, false, true, 1, 3, out.data());
    
    for (int i = 0; i < n; i++) {
        if (R[i] >= 2.0f && R[i] <= 6.0f) {
            EXPECT_FALSE(std::isnan(out[i])) 
                << "Valid input should not produce NaN at index " << i;
            EXPECT_GE(out[i], 0.0f) 
                << "Probability should be >= 0 at index " << i;
            EXPECT_LE(out[i], 1.0f) 
                << "Probability should be <= 1 at index " << i;
        }
    }
}

TEST_F(CAPITest, GetAvProbCart) {
    getAvProbCart(n, x.data(), y.data(), true, false, true, 1, 3, out.data());
    
    for (int i = 0; i < n; i++) {
        float r = sqrt(x[i]*x[i] + y[i]*y[i]);
        if (r >= 2.0f && r <= 6.0f) {
            EXPECT_FALSE(std::isnan(out[i])) 
                << "Valid Cartesian input should not produce NaN at index " << i;
            EXPECT_GE(out[i], 0.0f) 
                << "Probability should be >= 0 at index " << i;
            EXPECT_LE(out[i], 1.0f) 
                << "Probability should be <= 1 at index " << i;
        }
    }
}

// Tests for getScaledProb
TEST_F(CAPITest, GetScaledProb) {
    std::vector<float> smr(n, 0.0f);
    
    getScaledProb(n, mlt.data(), R.data(), smr.data(), true, false, true, 1, 3, out.data());
    
    for (int i = 0; i < n; i++) {
        if (R[i] >= 2.0f && R[i] <= 6.0f) {
            EXPECT_FALSE(std::isnan(out[i])) 
                << "Valid input should not produce NaN at index " << i;
            EXPECT_GE(out[i], 0.0f) 
                << "Scaled probability should be >= 0 at index " << i;
        }
    }
}

// Tests for getAvPS
TEST_F(CAPITest, GetAvPS) {
    getAvPS(n, mlt.data(), R.data(), true, false, true, 1, 3, true, out.data());
    
    for (int i = 0; i < n; i++) {
        if (R[i] >= 2.0f && R[i] <= 6.0f) {
            EXPECT_FALSE(std::isnan(out[i])) 
                << "Valid input should not produce NaN at index " << i;
            EXPECT_GT(out[i], 0.0f) 
                << "Plasmasphere density should be positive at index " << i;
            EXPECT_LT(out[i], 10000.0f) 
                << "Plasmasphere density should be reasonable at index " << i;
        }
    }
}

TEST_F(CAPITest, GetAvPSCart) {
    getAvPSCart(n, x.data(), y.data(), true, false, true, 1, 3, true, out.data());
    
    for (int i = 0; i < n; i++) {
        float r = sqrt(x[i]*x[i] + y[i]*y[i]);
        if (r >= 2.0f && r <= 6.0f) {
            EXPECT_FALSE(std::isnan(out[i])) 
                << "Valid Cartesian input should not produce NaN at index " << i;
            EXPECT_GT(out[i], 0.0f) 
                << "Plasmasphere density should be positive at index " << i;
        }
    }
}

// Tests for getScaledPS
TEST_F(CAPITest, GetScaledPS) {
    std::vector<float> smr(n, 0.0f);
    
    getScaledPS(n, mlt.data(), R.data(), smr.data(), true, false, true, 1, 3, true, out.data());
    
    for (int i = 0; i < n; i++) {
        if (R[i] >= 2.0f && R[i] <= 6.0f) {
            EXPECT_FALSE(std::isnan(out[i])) 
                << "Valid input should not produce NaN at index " << i;
            EXPECT_GT(out[i], 0.0f) 
                << "Scaled plasmasphere density should be positive at index " << i;
        }
    }
}

// Tests for getAvPT
TEST_F(CAPITest, GetAvPT) {
    getAvPT(n, mlt.data(), R.data(), true, false, true, 1, 3, true, out.data());
    
    for (int i = 0; i < n; i++) {
        if (R[i] >= 2.0f && R[i] <= 6.0f) {
            EXPECT_FALSE(std::isnan(out[i])) 
                << "Valid input should not produce NaN at index " << i;
            EXPECT_GT(out[i], 0.0f) 
                << "Plasma trough density should be positive at index " << i;
            EXPECT_LT(out[i], 1000.0f) 
                << "Plasma trough density should be reasonable at index " << i;
        }
    }
}

TEST_F(CAPITest, GetAvPTCart) {
    getAvPTCart(n, x.data(), y.data(), true, false, true, 1, 3, true, out.data());
    
    for (int i = 0; i < n; i++) {
        float r = sqrt(x[i]*x[i] + y[i]*y[i]);
        if (r >= 2.0f && r <= 6.0f) {
            EXPECT_FALSE(std::isnan(out[i])) 
                << "Valid Cartesian input should not produce NaN at index " << i;
            EXPECT_GT(out[i], 0.0f) 
                << "Plasma trough density should be positive at index " << i;
        }
    }
}

// Tests for getScaledPT
TEST_F(CAPITest, GetScaledPT) {
    std::vector<float> smr(n, 0.0f);
    
    getScaledPT(n, mlt.data(), R.data(), smr.data(), true, false, true, 1, 3, true, out.data());
    
    for (int i = 0; i < n; i++) {
        if (R[i] >= 2.0f && R[i] <= 6.0f) {
            EXPECT_FALSE(std::isnan(out[i])) 
                << "Valid input should not produce NaN at index " << i;
            EXPECT_GT(out[i], 0.0f) 
                << "Scaled plasma trough density should be positive at index " << i;
        }
    }
}

// Tests for combined models
TEST_F(CAPITest, GetAvMav) {
    getAvMav(n, mlt.data(), R.data(), true, false, true, 1, 3, out.data());
    
    for (int i = 0; i < n; i++) {
        if (R[i] >= 2.0f && R[i] <= 6.0f) {
            EXPECT_FALSE(std::isnan(out[i])) 
                << "Valid input should not produce NaN at index " << i;
            EXPECT_GT(out[i], 0.0f) 
                << "Combined average ion mass should be positive at index " << i;
            EXPECT_LT(out[i], 50.0f) 
                << "Combined average ion mass should be < 50 amu at index " << i;
        }
    }
}

TEST_F(CAPITest, GetAvMavCart) {
    getAvMavCart(n, x.data(), y.data(), true, false, true, 1, 3, out.data());
    
    for (int i = 0; i < n; i++) {
        float r = sqrt(x[i]*x[i] + y[i]*y[i]);
        if (r >= 2.0f && r <= 6.0f) {
            EXPECT_FALSE(std::isnan(out[i])) 
                << "Valid Cartesian input should not produce NaN at index " << i;
            EXPECT_GT(out[i], 0.0f) 
                << "Combined average ion mass should be positive at index " << i;
        }
    }
}

TEST_F(CAPITest, GetScaledMav) {
    std::vector<float> smr(n, 0.0f);
    
    getScaledMav(n, mlt.data(), R.data(), smr.data(), true, false, true, 1, 3, out.data());
    
    for (int i = 0; i < n; i++) {
        if (R[i] >= 2.0f && R[i] <= 6.0f) {
            EXPECT_FALSE(std::isnan(out[i])) 
                << "Valid input should not produce NaN at index " << i;
            EXPECT_GT(out[i], 0.0f) 
                << "Scaled combined average ion mass should be positive at index " << i;
        }
    }
}

// Test validation mode - points outside range should be NaN
TEST_F(CAPITest, ValidationMode) {
    std::vector<float> R_invalid = {1.0f, 7.0f, 10.0f};  // Outside valid range
    std::vector<float> mlt_invalid = {0.0f, 0.0f, 0.0f};
    std::vector<float> out_invalid(3);
    
    getAvMavH(3, mlt_invalid.data(), R_invalid.data(), true, false, true, 1, 3, out_invalid.data());
    
    // All should be NaN because they're outside valid range
    for (int i = 0; i < 3; i++) {
        EXPECT_TRUE(std::isnan(out_invalid[i])) 
            << "Points outside valid range should be NaN with validation at index " << i;
    }
}

// Test without validation - points outside range should still produce output
TEST_F(CAPITest, NoValidationMode) {
    std::vector<float> R_invalid = {1.5f, 6.5f};  // Slightly outside typical range
    std::vector<float> mlt_invalid = {0.0f, 0.0f};
    std::vector<float> out_invalid(2);
    
    getAvMavH(2, mlt_invalid.data(), R_invalid.data(), true, false, false, 1, 3, out_invalid.data());
    
    // Without validation, should still produce output (may or may not be NaN depending on model)
    // Just ensure the function doesn't crash
    SUCCEED() << "Function completed without validation mode";
}

// Test DC only mode
TEST_F(CAPITest, DCOnlyMode) {
    std::vector<float> out_dc(n);
    
    getAvMavH(n, mlt.data(), R.data(), true, true, true, 1, 3, out_dc.data());
    
    // DC only output should be different from full output
    getAvMavH(n, mlt.data(), R.data(), true, false, true, 1, 3, out.data());
    
    bool has_difference = false;
    for (int i = 0; i < n; i++) {
        if (!std::isnan(out[i]) && !std::isnan(out_dc[i])) {
            if (fabs(out[i] - out_dc[i]) > 0.01f) {
                has_difference = true;
                break;
            }
        }
    }
    
    EXPECT_TRUE(has_difference) << "DC-only mode should produce different output";
}
