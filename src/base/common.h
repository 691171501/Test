//
// Created by xuchaowu on 9/11/19.
//

#pragma  once

#include <glog/logging.h>
#include <gflags/gflags.h>


#define LOGINFO LOG(INFO)
#define LOGWARN LOG(WARNING)
#define LOGERROR LOG(ERROR)
#define LOGFATAL LOG(FATAL)

namespace zsequity{

void InitSystem(std::string log_prefix, std::string log_folder = "");

}

