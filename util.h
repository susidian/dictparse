#ifndef  GOODCODER_SUSIDIAN_C_ID_16575_UTIL_H
#define  GOODCODER_SUSIDIAN_C_ID_16575_UTIL_H

#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace parser {

const char SEPARATOR[] = "\t";
const char INT[] = "int";
const char FLOAT[] = "float";
const char STRING[] = "string";
const char UINT32_T[] = "uint32_t";
const char UINT64_T[] = "uint64_t";
const char INT_ARRAY[] = "int_array";
const char FLOAT_ARRAY[] = "float_array";
const char STRING_ARRAY[] = "string_array";
const char UINT32_ARRAY[] = "uint32_array";
const char UINT64_ARRAY[] = "uint64_array";
const char USER_TYPE[] = "user_type";

enum RetCode {
    SUCCESS,
    EMPTY_STR,
    EMPTY_VEC,
    ERROR_LENGTH,
    ERROR_CONVERT,
    BAD_ALLOC,
    INPUT_CLOUMNS_ERROR,
    INPUT_FORMAT_ERROR
};

RetCode check_format(const std::string &format_str) {
    if (format_str.empty()) {
        std::cout << "check_format, input empty" << std::endl;
        return EMPTY_STR;
    }
    if (format_str == INT
            || format_str == FLOAT
            || format_str == STRING
            || format_str == UINT32_T
            || format_str == UINT64_T
            || format_str == INT_ARRAY
            || format_str == FLOAT_ARRAY
            || format_str == STRING_ARRAY
            || format_str == UINT32_ARRAY
            || format_str == UINT64_ARRAY
            || format_str == USER_TYPE) {
        return SUCCESS;
    }
    std::cout << "check_format, input type error" << std::endl;
    return INPUT_FORMAT_ERROR;
}

RetCode set_dict_format(const std::string &format_file,
        size_t &columns,
        std::vector<std::string> &line_format_vec) {
    if (format_file.empty()) {
        std::cout << "set_dict_format, input file empty" << std::endl;
        return EMPTY_STR;
    }

    std::ifstream input(format_file.c_str());
    std::string columns_str;
    std::stringstream str;
    if (getline(input, columns_str)) {
        if (columns_str.empty()) {
            std::cout << "column error, column:" << columns_str << std::endl;
            return INPUT_CLOUMNS_ERROR;
        }
        str << columns_str;
        columns = 0; 
        if ((str >> columns) == 0 || columns <= 0) {
            std::cout << "column error, column:" << columns_str << std::endl;
            return INPUT_CLOUMNS_ERROR; 
        }
    }
    line_format_vec.clear();
    std::string format_str;
    while (std::getline(input, format_str)) {
        if (format_str.empty() || check_format(format_str) != SUCCESS) {
            std::cout << "column error, column:" << format_str << std::endl;
            return INPUT_FORMAT_ERROR;
        }
        line_format_vec.push_back(format_str);
    }

    if (line_format_vec.empty() || columns != line_format_vec.size()) {
        std::cout << "column error, columns:" << columns << std::endl;
        return INPUT_FORMAT_ERROR;
    }

    return SUCCESS;
}

template<typename T>
RetCode append_log(std::string &result, T &value) {
    std::stringstream str;
    std::string value_str;
    str << value;
    str >> value_str;

    if (result.empty()) {
        result.append(value_str);
    } else {
        result.append(SEPARATOR);
        result.append(value_str); 
    }

    return SUCCESS;
}

template<typename T>
int append_array_log(std::string &result, const std::string sep, std::vector<T> &value) {
    if (value.empty()) {
        return EMPTY_VEC;
    }

    std::stringstream str;
    std::string value_str;

    if (!result.empty()) {
        result.append(SEPARATOR);
    }
    size_t n = value.size();
    for (size_t i = 0; i < n-1; ++i) {
        str << value.at(i);
        str >> value_str;
        result.append(value_str);
        result.append(sep);
        str.clear();
        value_str.clear();
    }
    str << value.at(n-1);
    str >> value_str;
    result.append(value_str);

    return SUCCESS;
}

}

#endif  //GOODCODER_SUSIDIAN_C_ID_16575_UTIL_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
