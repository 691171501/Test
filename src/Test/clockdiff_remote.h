//
// Created by xuchaowu on 19-11-1.
//

#ifndef TEST_CLOCKDIFF_REMOTE_H
#define TEST_CLOCKDIFF_REMOTE_H

#include <iostream>
#include <string.h>

class ClockDiffRemote {
public:
    ClockDiffRemote(const std::string& ip) : ip_(ip) {}

    void Execute() {
        FILE* fp =NULL;
        char buf [1024];
        char result[40960];
        std::string cmd = "ping  -T tsandaddr  ";

        cmd += ip_;
        cmd += " -c 4";

//        cmd = "ls -al";
        std::cout << "cmd: " << cmd << std::endl;
        if ((fp = popen(cmd.c_str(), "r")) != NULL) {
            while (fgets(buf, 1024, fp) != NULL) {
                std::cout << "data: " << buf << std::endl;
                strcat(result, buf);
            }
            pclose(fp);
            fp = NULL;

        }

    }


private:
    std::string ip_;
};


#endif //TEST_CLOCKDIFF_REMOTE_H
