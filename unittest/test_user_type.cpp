#include <gtest/gtest.h>
#include <string>
#include "user_type.h"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TestUserType, test_user_type_case1) {
    parser::UserType user_type;
    std::string col_str("32,43,45");
    int ret = parser::parse_user_type_process(col_str, ",", user_type); // 解析用户自定义类型
    ASSERT_EQ(parser::SUCCESS, ret);
    ASSERT_EQ(45, user_type.column_3);
}

TEST(TestUserType, test_user_type_case2) {
    parser::UserType user_type;
    std::string col_str("32,dfsa,45");
    int ret = parser::parse_user_type_process(col_str, ",", user_type); // 解析用户自定义类型
    ASSERT_EQ(parser::ERROR_CONVERT, ret);
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
