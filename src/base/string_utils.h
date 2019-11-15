//
// Created by xuchaowu on 10/10/19.
//

#ifndef EQUITY_SERVER_STRING_UTILS_H
#define EQUITY_SERVER_STRING_UTILS_H
#include <vector>
#include <cstdlib>
#include <ctype.h>
#include <algorithm>

namespace zsequity{
    namespace  rawdata{

        template <typename  UnaryPredicate = decltype(::isspace)>
        std::string TrimLeft(std::string s, UnaryPredicate is_space = ::isspace) {
            s.erase(s.begin(), std::find_if(
                    s.begin(), s.end(), [&is_space](const char& c){
                        return !is_space(c);}
            ));

            return  s ;
        }

        template <typename  UnaryPredicate = decltype(::isspace)>
        std::string TrimRight(std::string s, UnaryPredicate is_space = ::isspace) {
            s.erase(std::find_if(s.rbegin(), s.rend(), [&is_space](const char& c){
                        return !is_space(c); }).base(), s.end());

            return  s ;
        }

        template <typename  UnaryPredicate = decltype(::isspace)>
        std::string Trim(std::string s, UnaryPredicate is_space = ::isspace){
            return TrimLeft(TrimRight(s, is_space), is_space);
        }

        std::vector<std::string> StringSplit(const std::string& data, const std::string& delimiter);
    }
}



#endif //EQUITY_SERVER_STRING_UTILS_H
