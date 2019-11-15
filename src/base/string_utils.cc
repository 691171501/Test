//
// Created by xuchaowu on 10/10/19.
//

#include "string_utils.h"
#include "common.h"
namespace zsequity{
    namespace  rawdata{

        std::vector<std::string> StringSplit(const std::string& data, const std::string& delimiter) {
            CHECK(!delimiter.empty());

            std::vector<std::string> result;
            size_t  cur =0;

            for (size_t index = 0; (index = data.find(delimiter, cur)) != std::string::npos; ) {
                result.push_back(data.substr(cur, index - cur));
                cur = index + delimiter.size();
            }

            result.push_back(data.substr(cur));
            return result;
        }
    }
}