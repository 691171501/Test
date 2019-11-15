//
// Created by xuchaowu on 19-10-31.
//

#ifndef WIND_DATA_FETCHER_FILE_SYSTEM_H
#define WIND_DATA_FETCHER_FILE_SYSTEM_H
#include "common.h"
#include <boost/filesystem.hpp>


namespace  zsequity {
    namespace  rawdata {

        using FilePath = boost::filesystem::path;
        void EnsureDirectory(const FilePath& path);
        std::string AbsPath(const std::string& path);
    }
}



#endif //WIND_DATA_FETCHER_FILE_SYSTEM_H
