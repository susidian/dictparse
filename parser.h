/***************************************************************************
 * 
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file parser.h
 * @author susidian(susidian@baidu.com)
 * @date 2017/11/08 15:48:46
 * @brief ͨ�ôʱ���� 
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
 * @brief ������������
 * @param string& ��ת��������
 * @param T& ������� 
 * @return SUCCESS �ɹ�  ���� ʧ��
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
 * @brief ģ���ػ��������ַ���
 * @param string& ��ת��������
 * @param T& �������
 * @return SUCCESS �ɹ� ���� ʧ��
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
 * @brief ���غ�������������num:item1,item2,item3������
 * @param string& ��ת��������
 * @param const string& �ָ���
 * @param vector<T>& �������vector
 * @return SUCCESS �ɹ� ���� ʧ��
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
