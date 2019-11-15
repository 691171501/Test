//
// Created by xuchaowu on 9/23/19.
//

#include "common.h"
#include "exit_sys.h"
#include "file_system.h"
#include "cmd_define.h"

namespace zsequity{

    using namespace rawdata;

    void InitSystem(std::string log_prefix, std::string log_folder)
    {

        EnsureDirectory(AbsPath(FLAGS_log_root_path));
        ExitSys::Init();
        google::InitGoogleLogging(log_prefix.c_str());
        google::InstallFailureSignalHandler();

        FLAGS_colorlogtostderr = true;
        std::string log_file_name;
        if (log_folder == "") {
            EnsureDirectory(AbsPath(FLAGS_log_root_path) + "logs");
            FLAGS_log_dir = AbsPath(FLAGS_log_root_path) + "logs";
            log_file_name = AbsPath(FLAGS_log_root_path) + "logs/" + log_prefix + "_";
        } else {
            EnsureDirectory(AbsPath(FLAGS_log_root_path) + "logs/" + log_folder);
            FLAGS_log_dir = AbsPath(FLAGS_log_root_path) + "logs" + log_folder;
            log_file_name = AbsPath(FLAGS_log_root_path) + "logs/" + log_folder + "/"+ log_prefix + "_";
        }

        google::SetLogDestination(google::INFO, log_file_name.c_str());
        google::SetLogSymlink(google::INFO, "");
        google::SetStderrLogging(google::WARNING);
        ExitSys::AddCallBack([] {
            google::ShutdownGoogleLogging();
        });
    }
}




