#ifndef  GOODCODER_SUSIDIAN_C_ID_16575_USER_TYPE_H
#define  GOODCODER_SUSIDIAN_C_ID_16575_USER_TYPE_H

#include <boost/algorithm/string.hpp>

#include "parser.h"
#include "util.h"

namespace parser {
// 用户自定义类型
struct UserType {
    int column_1; // 字段1
    int column_2; // 字段2
    int column_3; // 字段3
}; 

/**
 * @brief 解析用户自定义类型
 * @param string& 待转换的类型
 * @param const string& 分隔符
 * @param UserType& 解析结果
 * @return SUCCESS 成功 其它 失败
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
 * @brief 追加用户自定义类型日志
 * @param string& 日志
 * @param const string& 分隔符
 * @param UserType& 用户自定义类型
 * @return SUCCESS 成功 其它 失败
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

#endif  
