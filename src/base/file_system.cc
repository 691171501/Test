//
// Created by xuchaowu on 19-10-31.
//

#include "file_system.h"


namespace  zsequity {
    namespace rawdata {

        namespace fs= boost::filesystem;

        void EnsureDirectory(const FilePath &path) {
            try {
                fs::create_directories(path);
            } catch (const fs::filesystem_error &) {
                if (!fs::exists(path) || !fs::is_directory(path)) {
                    LOG(FATAL) << "Directory {" << path.string() << ") created failed";
                }
            }
        }

        std::string AbsPath(const std::string &path) {
            CHECK_GT(path.size(), 0);

            if (path[0] == '/') {
                return path;
            } else if (path[0] == '~') {
                std::string tail = path.substr(1);
                char *home = std::getenv("HOME");
                if (home == nullptr || std::strlen(home) == 0) {
                    return tail;
                } else {
                    return std::string(home) + tail;
                }
            } else {
                return boost::filesystem::system_complete(path).string();
            }

        }
    }
}
