#include <iostream>
#include <xmmintrin.h>
#include <pmmintrin.h>
#include <string>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include "parser.h"
#include "user_type.h"
#include "util.h"

bool parse_line(const std::string &line,
        std::vector<std::string> &format_vec,
        size_t col_num,
        std::string &result_str) {
    std::vector<std::string> col_vec;
    boost::split(col_vec, line, boost::is_any_of("\t"));
    if (col_vec.size() != col_num) {
        std::cout << "line error, column num:" << col_vec.size() 
            << " not equal " << col_num << std::endl;
        return false;
    }
    
    std::vector<std::string>::iterator col_iter = col_vec.begin();
    int index = 0;
    for (; col_iter != col_vec.end() && index < format_vec.size(); ++col_iter, ++index) {
        int type_int = -1;
        float type_float = 0.000001;
        char* type_string = NULL;
        uint32_t type_uint32 = 0;
        uint64_t type_uint64 = 0;
        std::vector<uint64_t> uint64_vec;
        std::vector<char*> string_vec;
        std::vector<float> float_vec;
        std::vector<uint32_t> uint32_vec;
        std::vector<int> int_vec;
        parser::UserType user_type;
        parser::DictParse dict_parse;

        if (format_vec.at(index) == "int") {
            if (dict_parse.parse<int>(*col_iter, type_int) != parser::SUCCESS) {
                std::cout << "line error, column:" << index + 1
                    << " should be int" << std::endl;
                return false;
            } 
            parser::append_log(result_str, type_int);
        } else if (format_vec.at(index) == "float") {
            if (dict_parse.parse<float>(*col_iter, type_float) != parser::SUCCESS) {
                std::cout << "line error, column:" << index + 1
                    << " should be float" << std::endl;
                return false;
            }
            parser::append_log(result_str, type_float);
        } else if (format_vec.at(index) == "string") {
            if (type_string != NULL) {
                delete type_string;
                type_string = NULL;
            }
            type_string = new char[col_vec.at(index).size() + 1];
            if (dict_parse.parse<char*>(*col_iter, type_string) != parser::SUCCESS) {
                if (type_string != NULL) {
                    delete type_string;
                    type_string = NULL;
                }
                std::cout << "line error, parse column:" << index + 1 
                    << " not success" << std::endl;
                return false;
            }
            parser::append_log(result_str, type_string);
        } else if (format_vec.at(index) == "uint32_t") {
            if (dict_parse.parse<uint32_t>(*col_iter, type_uint32) != parser::SUCCESS) {
                std::cout << "line error, parse column:" << index + 1
                    << " not success" << std::endl;
                return false;
            }
            parser::append_log(result_str, type_uint32);
        } else if (format_vec.at(index) == "uint64_t") {
            if (dict_parse.parse<uint64_t>(*col_iter, type_uint64) != parser::SUCCESS) {
                std::cout << "line error, parse column:" << index + 1
                    << " not success" << std::endl;
                return false;
            }
            parser::append_log(result_str, type_uint64);
        } else if (format_vec.at(index) == "int_array") {
            const std::string sep(",");
            if (dict_parse.parse<int>(*col_iter, sep, int_vec) != parser::SUCCESS) {
                std::cout << "line error, parse column:" << index + 1
                    << " not success" << std::endl;
                return false;
            }
            parser::append_array_log(result_str, sep, int_vec);
        } else if (format_vec.at(index) == "float_array") {
            const std::string sep(",");
            if (dict_parse.parse<float>(*col_iter, sep, float_vec) != parser::SUCCESS) {
                std::cout << "line error, parse column:" << index + 1
                    << " not success" << std::endl;
                return false;
            }
            parser::append_array_log(result_str, sep, float_vec);
        } else if (format_vec.at(index) == "string_array") {
            const std::string sep(",");
            if (dict_parse.parse<char*>(*col_iter, sep, string_vec) != parser::SUCCESS) {
                std::cout << "line error, parse column:" << index + 1
                    << " not success" << std::endl;
                return false;
            }
            parser::append_array_log(result_str, sep, string_vec);
        } else if (format_vec.at(index) == "uint32_array") {
            const std::string sep(",");
            if (dict_parse.parse<uint32_t>(*col_iter, sep, uint32_vec) != parser::SUCCESS) {
                std::cout << "line error, parse column:" << index + 1
                    << " not success" << std::endl;
                return false;
            }
            parser::append_array_log(result_str, sep, uint32_vec);
        } else if (format_vec.at(index) == "uint64_array") {
            const std::string sep(",");
            if (dict_parse.parse<uint64_t>(*col_iter, sep, uint64_vec) != parser::SUCCESS) {
                std::cout << "line error, parse column:" << index + 1
                    << " not success" << std::endl;
                return false;
            }
            parser::append_array_log(result_str, sep, uint64_vec);
        } else if (format_vec.at(index) == "user_type") {
            const std::string sep(",");
            if (parse_user_type_process(*col_iter, sep, user_type) != parser::SUCCESS) {
                std::cout << "line error, parse column:" << index + 1
                    << " not success" << std::endl;
                return false;
            }
            parser::append_user_type_log(user_type, sep, result_str);
        } else {
            std::cout << "input line type error" << std::endl;
            return false;
        } 
    }
    return true;
}

int main(int argc, char *argv[]) {
    MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);

    std::string dict_file, format_file;
    opterr = 0;
    int ch;
    while ((ch = getopt(argc, argv, "f:h:t")) != -1) {
        printf("optind: %d\n", optind);
        switch (ch) {
            case 'f':
                printf("have option -f\n");
                dict_file = optarg;
                break;
            case 'h':
                printf("have option -h\n");
                printf("usage: ./demo -f dict_file -t format_file");
                return 0;
            case 't':
                printf("have option -h\n");
                format_file = optarg;
                break;
            case '?':
                printf("unknown option %c\n", (char)optopt);
                printf("usage: ./demo -f dict_file -t format_file");
                return 0;
            default:
                printf("unknown option %c\n", (char)optopt);
                printf("usage: ./demo -f dict_file -t format_file");
                return 0;
        }
    }

    size_t col_num = 0;
    std::vector<std::string> format_vec;

    // ÉèÖÃ´Ê±íÎÄ¼þ¸ñÊ½
    if (parser::set_dict_format(format_file, col_num, format_vec) != parser::SUCCESS) {
        return -1;
    }

    if (dict_file.empty() || col_num <= 0 || format_vec.empty()) {
        return -1;
    }

    std::ifstream input(dict_file.c_str());
    std::string line;
    while (std::getline(input, line)) {
        std::string result_str;
        if (parse_line(line, format_vec, col_num, result_str)) {
            std::cout << result_str << std::endl;
        }
    }
    input.close();

    return 0;
}
