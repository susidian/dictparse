/***************************************************************************
 * 
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file test_parser.cpp
 * @author susidian(com@baidu.com)
 * @date 2017/11/09 18:38:42
 * @brief 解析内置类型 
 *  
 **/

#include <gtest/gtest.h>
#include <string>
#include "parser.h"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class TestDictParse : public ::testing::Test{
public:
    virtual ~TestDictParse() {}
    virtual void SetUp() {
        _dict_parse = new parser::DictParse();
    }
    virtual void TearDown() {
        delete _dict_parse;
    }
    parser::DictParse* _dict_parse;
};

TEST_F(TestDictParse, case_input_int) {
    int int_value;
    std::string col_str("23");
    int ret = _dict_parse->parse<int>(col_str, int_value); // 解析int类型
    ASSERT_EQ(parser::SUCCESS, ret);
    ASSERT_EQ(23, int_value);

    std::string col_err("hello");
    ret = _dict_parse->parse<int>(col_err, int_value);
    ASSERT_EQ(parser::ERROR_CONVERT, ret);
}

TEST_F(TestDictParse, case_input_float) {
    float float_value;
    std::string col_str("23.43");
    int ret = _dict_parse->parse<float>(col_str, float_value); // 解析float类型
    ASSERT_EQ(parser::SUCCESS, ret);
    ASSERT_FLOAT_EQ(23.43, float_value);

    std::string col_empty;
    ret = _dict_parse->parse<float>(col_empty, float_value);
    ASSERT_EQ(parser::EMPTY_STR, ret);
}

TEST_F(TestDictParse, case_input_string) {
    std::string col_str("is_string");
    char* string_value = new char[col_str.size() + 1];
    int ret = _dict_parse->parse<char*>(col_str, string_value); // 解析char*类型
    ASSERT_EQ(parser::SUCCESS, ret);
    ASSERT_STREQ(col_str.c_str(), string_value);
}

TEST_F(TestDictParse, case_input_uint32) {
    uint32_t uint32_value;
    std::string col_str("23");
    int ret = _dict_parse->parse<uint32_t>(col_str, uint32_value); // 解析uint32_t类型
    ASSERT_EQ(parser::SUCCESS, ret);
    ASSERT_EQ(23, uint32_value);
}

TEST_F(TestDictParse, case_input_uint64) {
    uint64_t uint64_value;
    std::string col_str("23");
    int ret = _dict_parse->parse<uint64_t>(col_str, uint64_value); // 解析uint64_t类型
    ASSERT_EQ(parser::SUCCESS, ret);
    ASSERT_EQ(23, uint64_value);
}

TEST_F(TestDictParse, case_input_int_vec) {
    std::vector<int> int_vec_value;
    std::string col_str("23,33,34");
    int ret = _dict_parse->parse<int>(col_str, ",", int_vec_value); // 解析数组类型
    ASSERT_EQ(parser::SUCCESS, ret);
    ASSERT_EQ(33, int_vec_value.at(1));

    std::string col_err("22,rt,43");
    ret = _dict_parse->parse<int>(col_err, ",", int_vec_value);
    ASSERT_EQ(parser::ERROR_CONVERT, ret);
}

TEST_F(TestDictParse, case_input_float_vec) {
    std::vector<float> float_vec_value;
    std::string col_str("2.43,33.6,34.23");
    int ret = _dict_parse->parse<float>(col_str, ",", float_vec_value); // 解析数组类型
    ASSERT_EQ(parser::SUCCESS, ret);
    ASSERT_FLOAT_EQ(33.6, float_vec_value.at(1));
}

TEST_F(TestDictParse, case_input_uint32_vec) {
    std::vector<uint32_t> uint32_vec_value;
    std::string col_str("243,336,323");
    int ret = _dict_parse->parse<uint32_t>(col_str, ",", uint32_vec_value); // 解析数组类型
    ASSERT_EQ(parser::SUCCESS, ret);
    ASSERT_EQ(336, uint32_vec_value.at(1));
}

TEST_F(TestDictParse, case_input_uint64_vec) {
    std::vector<uint64_t> uint64_vec_value;
    std::string col_str("43324,333426,3423123");
    int ret = _dict_parse->parse<uint64_t>(col_str, ",", uint64_vec_value); // 解析数组类型
    ASSERT_EQ(parser::SUCCESS, ret);
    ASSERT_EQ(333426, uint64_vec_value.at(1));
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
