/***************************************************************************
 * 
 * Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file user_type.h
 * @author susidian(susidian@baidu.com)
 * @date 2017/11/08 19:44:33
 * @brief 
 *  
 **/

#ifndef  GOODCODER_SUSIDIAN_C_ID_16575_USER_TYPE_H
#define  GOODCODER_SUSIDIAN_C_ID_16575_USER_TYPE_H

#include <boost/algorithm/string.hpp>

#include "parser.h"
#include "util.h"

namespace parser {
// �û��Զ�������
struct UserType {
    int column_1; // �ֶ�1
    int column_2; // �ֶ�2
    int column_3; // �ֶ�3
}; 

/**
 * @brief �����û��Զ�������
 * @param string& ��ת��������
 * @param const string& �ָ���
 * @param UserType& �������
 * @return SUCCESS �ɹ� ���� ʧ��
 */  
RetCode parse_user_type_process(
        const std::string& col_str,
        const std::string& sep,
        UserType& value) {
    if (col_str.empty() || sep.empty()) {
        std::cout << "column error, input empty" << std::endl;
        return EMPTY_STR;
    } 
    
    std::vector<std::string> str_vec; 
    boost::split(str_vec, col_str, boost::is_any_of(sep));
    if (str_vec.size() != 3) {
        std::cout << "input error, column:" << col_str << ", length is not 3" << std::endl;
        return ERROR_LENGTH;
    }

    DictParse* parse = new (std::nothrow) DictParse();

    if (parse->parse<int>(str_vec.at(0), value.column_1) != SUCCESS
            || parse->parse<int>(str_vec.at(1), value.column_2) != SUCCESS
            || parse->parse<int>(str_vec.at(2), value.column_3) != SUCCESS) {
        delete parse;
        std::cout << "convert error, column:" << col_str << std::endl;
        return ERROR_CONVERT;
    }
   
    delete parse; 
    return SUCCESS; 
}

/**
 * @brief ׷���û��Զ���������־
 * @param string& ��־
 * @param const string& �ָ���
 * @param UserType& �û��Զ�������
 * @return SUCCESS �ɹ� ���� ʧ��
 */  
RetCode append_user_type_log(UserType &value, const std::string &sep, std::string &result) {
    std::stringstream str;
    std::string value_str;

    if (!result.empty()) {
        result.append(SEPARATOR);
    }
    str.clear();
    value_str.clear();
    str << value.column_1;
    str >> value_str;
    result.append(value_str);
    result.append(sep);

    str.clear();
    value_str.clear();
    str << value.column_2;
    str >> value_str;
    result.append(value_str);
    result.append(sep);

    str.clear();
    value_str.clear();
    str << value.column_3;
    str >> value_str;
    result.append(value_str);

    return SUCCESS;
}

}

#endif  //GOODCODER_SUSIDIAN_C_ID_16575_USER_TYPE_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
