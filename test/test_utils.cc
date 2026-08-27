#include <gtest/gtest.h>
#include <cmath>
#include "../include/spiced.h"

class UtilityFunctionsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Test data will be set up in individual tests
    }
};

// Tests for rescaleR
TEST_F(UtilityFunctionsTest, RescaleR) {
    // rescaleR(R) = (R - 4.0)/2.0
    EXPECT_FLOAT_EQ(rescaleR(2.0f), -1.0f);
    EXPECT_FLOAT_EQ(rescaleR(3.0f), -0.5f);
    EXPECT_FLOAT_EQ(rescaleR(4.0f), 0.0f);
    EXPECT_FLOAT_EQ(rescaleR(5.0f), 0.5f);
    EXPECT_FLOAT_EQ(rescaleR(6.0f), 1.0f);
}

// Tests for rescaleSMR
TEST_F(UtilityFunctionsTest, RescaleSMR) {
    // Test with known values (Box-Cox transformation)
    float result1 = rescaleSMR(0.0f);
    EXPECT_FALSE(std::isnan(result1)) << "rescaleSMR(0) should not be NaN";
    
    float result2 = rescaleSMR(-70.0f);
    EXPECT_FALSE(std::isnan(result2)) << "rescaleSMR(-70) should not be NaN";
    
    // Test that different inputs produce different outputs
    EXPECT_NE(rescaleSMR(0.0f), rescaleSMR(-70.0f));
    
    // Test monotonicity for positive shift (higher SMR should give higher rescaled value)
    // Note: actual behavior depends on Box-Cox parameters
    float r1 = rescaleSMR(0.0f);
    float r2 = rescaleSMR(100.0f);
    EXPECT_NE(r1, r2) << "Different SMR values should produce different rescaled values";
}

// Tests for rescaleF107
TEST_F(UtilityFunctionsTest, RescaleF107) {
    // Test with typical F10.7 values
    float result1 = rescaleF107(80.0f);
    EXPECT_FALSE(std::isnan(result1)) << "rescaleF107(80) should not be NaN";
    
    float result2 = rescaleF107(150.0f);
    EXPECT_FALSE(std::isnan(result2)) << "rescaleF107(150) should not be NaN";
    
    float result3 = rescaleF107(100.0f);
    EXPECT_FALSE(std::isnan(result3)) << "rescaleF107(100) should not be NaN";
    
    // Test that different inputs produce different outputs
    EXPECT_NE(result1, result2);
    EXPECT_NE(result1, result3);
}

// Tests for unscaleDensity
TEST_F(UtilityFunctionsTest, UnscaleDensity) {
    // Test with transformed density values
    float result1 = unscaleDensity(0.0f);
    EXPECT_FALSE(std::isnan(result1)) << "unscaleDensity(0) should not be NaN";
    EXPECT_GT(result1, 0.0f) << "Density should be positive";
    
    float result2 = unscaleDensity(1.0f);
    EXPECT_FALSE(std::isnan(result2)) << "unscaleDensity(1) should not be NaN";
    EXPECT_GT(result2, 0.0f) << "Density should be positive";
    
    float result3 = unscaleDensity(-1.0f);
    EXPECT_FALSE(std::isnan(result3)) << "unscaleDensity(-1) should not be NaN";
    EXPECT_GT(result3, 0.0f) << "Density should be positive";
}

// Tests for polynomial - double version
TEST_F(UtilityFunctionsTest, PolynomialDouble) {
    // Test linear polynomial: y = 2 + 3x
    int nd = 1;
    double coef[] = {2.0, 3.0};
    int n = 5;
    float x[] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f};
    double y[5];
    double expected[] = {2.0, 5.0, 8.0, 11.0, 14.0};
    
    polynomial(nd, coef, n, x, y);
    
    for (int i = 0; i < n; i++) {
        EXPECT_NEAR(y[i], expected[i], 1e-10) 
            << "Linear polynomial mismatch at index " << i;
    }
}

TEST_F(UtilityFunctionsTest, PolynomialDoubleQuadratic) {
    // Test quadratic polynomial: y = 1 + 2x + 3x^2
    int nd = 2;
    double coef[] = {1.0, 2.0, 3.0};
    int n = 4;
    float x[] = {0.0f, 1.0f, 2.0f, -1.0f};
    double y[4];
    double expected[] = {1.0, 6.0, 17.0, 2.0};  // 1, 1+2+3, 1+4+12, 1-2+3
    
    polynomial(nd, coef, n, x, y);
    
    for (int i = 0; i < n; i++) {
        EXPECT_NEAR(y[i], expected[i], 1e-10) 
            << "Quadratic polynomial mismatch at index " << i;
    }
}

TEST_F(UtilityFunctionsTest, PolynomialDoubleCubic) {
    // Test cubic polynomial: y = 1 - x + 2x^2 - x^3
    int nd = 3;
    double coef[] = {1.0, -1.0, 2.0, -1.0};
    int n = 3;
    float x[] = {0.0f, 1.0f, 2.0f};
    double y[3];
    double expected[] = {1.0, 1.0, -1.0};  // 1, 1-1+2-1, 1-2+8-8
    
    polynomial(nd, coef, n, x, y);
    
    for (int i = 0; i < n; i++) {
        EXPECT_NEAR(y[i], expected[i], 1e-10) 
            << "Cubic polynomial mismatch at index " << i;
    }
}

// Tests for polynomial - float version
TEST_F(UtilityFunctionsTest, PolynomialFloat) {
    // Test linear polynomial: y = 2 + 3x
    int nd = 1;
    float coef[] = {2.0f, 3.0f};
    int n = 5;
    float x[] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f};
    float y[5];
    float expected[] = {2.0f, 5.0f, 8.0f, 11.0f, 14.0f};
    
    polynomial(nd, coef, n, x, y);
    
    for (int i = 0; i < n; i++) {
        EXPECT_NEAR(y[i], expected[i], 1e-5f) 
            << "Linear polynomial (float) mismatch at index " << i;
    }
}

TEST_F(UtilityFunctionsTest, PolynomialFloatQuadratic) {
    // Test quadratic polynomial: y = 1 + 2x + 3x^2
    int nd = 2;
    float coef[] = {1.0f, 2.0f, 3.0f};
    int n = 4;
    float x[] = {0.0f, 1.0f, 2.0f, -1.0f};
    float y[4];
    float expected[] = {1.0f, 6.0f, 17.0f, 2.0f};
    
    polynomial(nd, coef, n, x, y);
    
    for (int i = 0; i < n; i++) {
        EXPECT_NEAR(y[i], expected[i], 1e-5f) 
            << "Quadratic polynomial (float) mismatch at index " << i;
    }
}

// Tests for reverseArray - float version
TEST_F(UtilityFunctionsTest, ReverseArrayFloat) {
    float arr[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float expected[] = {5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    int n = 5;
    
    reverseArray(n, arr);
    
    for (int i = 0; i < n; i++) {
        EXPECT_FLOAT_EQ(arr[i], expected[i]) 
            << "Array reversal (float) failed at index " << i;
    }
}

TEST_F(UtilityFunctionsTest, ReverseArrayFloatEven) {
    float arr[] = {1.0f, 2.0f, 3.0f, 4.0f};
    float expected[] = {4.0f, 3.0f, 2.0f, 1.0f};
    int n = 4;
    
    reverseArray(n, arr);
    
    for (int i = 0; i < n; i++) {
        EXPECT_FLOAT_EQ(arr[i], expected[i]) 
            << "Array reversal (float, even) failed at index " << i;
    }
}

TEST_F(UtilityFunctionsTest, ReverseArrayFloatSingle) {
    float arr[] = {42.0f};
    float expected[] = {42.0f};
    int n = 1;
    
    reverseArray(n, arr);
    
    EXPECT_FLOAT_EQ(arr[0], expected[0]);
}

// Tests for reverseArray - double version
TEST_F(UtilityFunctionsTest, ReverseArrayDouble) {
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double expected[] = {5.0, 4.0, 3.0, 2.0, 1.0};
    int n = 5;
    
    reverseArray(n, arr);
    
    for (int i = 0; i < n; i++) {
        EXPECT_DOUBLE_EQ(arr[i], expected[i]) 
            << "Array reversal (double) failed at index " << i;
    }
}

TEST_F(UtilityFunctionsTest, ReverseArrayDoubleEven) {
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    double expected[] = {6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    int n = 6;
    
    reverseArray(n, arr);
    
    for (int i = 0; i < n; i++) {
        EXPECT_DOUBLE_EQ(arr[i], expected[i]) 
            << "Array reversal (double, even) failed at index " << i;
    }
}

// Test reverseArray twice returns to original
TEST_F(UtilityFunctionsTest, ReverseArrayDoubleReverse) {
    float arr[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float original[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    int n = 5;
    
    reverseArray(n, arr);
    reverseArray(n, arr);
    
    for (int i = 0; i < n; i++) {
        EXPECT_FLOAT_EQ(arr[i], original[i]) 
            << "Double reversal should restore original at index " << i;
    }
}
