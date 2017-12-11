/***************************************************************************
 * 
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file parser.h
 * @author susidian(susidian@baidu.com)
 * @date 2017/11/08 15:48:46
 * @brief 通用词表解析 
 *  
 **/

#ifndef  GOODCODER_SUSIDIAN_C_ID_16575_PARSER_H
#define  GOODCODER_SUSIDIAN_C_ID_16575_PARSER_H

#include <sstream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

#include "util.h"

namespace parser {
class DictParse {
public:
    template <typename T>
    RetCode parse(const std::string& col_str, T& value);

    template <typename T>
    RetCode parse(const std::string& col_str, 
            const std::string& sep, std::vector<T>& value_vec);
};

/**
 * @brief 解析内置类型
 * @param string& 待转换的类型
 * @param T& 解析结果 
 * @return SUCCESS 成功  其它 失败
 */  
template <typename T>
RetCode DictParse::parse(const std::string& col_str, T& value) {
    if (col_str.empty()) {
        std::cout << "column error, input empty" << std::endl; 
        return EMPTY_STR;
    }

    std::stringstream str;
    str << col_str;
    if (str >> value) {
        return SUCCESS;
    } 
    std::cout << "convert error, column:" << col_str << std::endl;
    return ERROR_CONVERT;
}

/**
 * @brief 模板特化，解析字符串
 * @param string& 待转换的类型
 * @param T& 解析结果
 * @return SUCCESS 成功 其它 失败
 */  
template<>
RetCode DictParse::parse(const std::string& col_str, char*& value) {
    if (col_str.empty() || value == NULL) {
        std::cout << "column error, input empty" << std::endl; 
        return EMPTY_STR;
    }
    if (snprintf(value, col_str.size() + 1, col_str.c_str()) < 0) {
        std::cout << "convert error, column:" << col_str << std::endl;
        return ERROR_CONVERT;
    } 
    return SUCCESS;
}

/**
 * @brief 重载函数，解析形如num:item1,item2,item3的数组
 * @param string& 待转换的类型
 * @param const string& 分隔符
 * @param vector<T>& 解析结果vector
 * @return SUCCESS 成功 其它 失败
 */  
template <typename T>
RetCode DictParse::parse(const std::string& col_str,
        const std::string& sep,
        std::vector<T>& value_vec) {
    if (col_str.empty() || sep.empty()) {
        std::cout << "column error, input:" << col_str << "; seperator:" << sep << std::endl; 
        return EMPTY_STR;
    } 
    std::vector<std::string> str_vec;
    boost::split(str_vec, col_str, boost::is_any_of(sep));
    std::vector<std::string>::iterator str_iter = str_vec.begin();
    for (; str_iter != str_vec.end(); ++str_iter) {
        T a;
        if (parse(*str_iter, a) != SUCCESS) {
            std::cout << "convert error, column:" << col_str << std::endl;
            return ERROR_CONVERT;
        }
        value_vec.push_back(a);
    }
    return SUCCESS;
}

}

#endif  //GOODCODER_SUSIDIAN_C_ID_16575_PARSER_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
