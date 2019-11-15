//
// Created by xuchaowu on 19-10-29.
//
#include "exit_sys.h"
using namespace zsequity;


std::once_flag ExitSys::g_init_flag_;
ExitSys* ExitSys::g_instance_ = nullptr;

void ExitSys::ExitImpl() {
    std::unique_lock<std::mutex> lock (glb().mutex_);
    if(glb().stopping_) {
        lock.unlock();
        WaitUntilExited();
    } else {
        glb().stopping_ = true;
        std::vector<Callback > call;
        glb().exit_funcs_.swap(call);
        lock.unlock();
        while (!call.empty()) {
            call.back()();
            call.pop_back();
        }
        glb().io_service_.stop();

    }

}

