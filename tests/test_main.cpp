#include <gtest/gtest.h>

float add(float a, float b);
float multiply(float a, float b);

TEST(MathTest, Addition) {
    EXPECT_EQ(add(3.5, 4.5), 8.0);
    EXPECT_EQ(add(-2.2, 2.2), 0.0);
    EXPECT_EQ(add(0.0, 0.0), 0.0);
}

TEST(MathTest, Multiplication) {
    EXPECT_EQ(multiply(5.5, 4.0), 22.0);
    EXPECT_EQ(multiply(2.0, -8.0), -16.0);
    EXPECT_EQ(multiply(3.0, 0.0), 0.0);
    EXPECT_EQ(multiply(0.0, 0.0), 0.0);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

float add(float a, float b) {
    return a + b;
}

float multiply(float a, float b) {
    return a * b;
}