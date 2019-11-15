//
// Created by xuchaowu on 19-10-29.
//

#ifndef MDL_EXIT_SYS_H
#define MDL_EXIT_SYS_H

#include <csignal>
#include <functional>
#include "boost/asio.hpp"
#include <mutex>
#include "common.h"

namespace  zsequity {
    class ExitSys {
    public:
        using IoService = boost::asio::io_service;
        using AsioErrorCode = boost::system::error_code;
        using Callback = std::function<void ()>;
        static void Init() {
            std::call_once(g_init_flag_, [] {
                g_instance_ = new ExitSys();
            });
        }

        ExitSys(const ExitSys& rhs) = delete;
        ExitSys& operator = (const ExitSys& rhs) = delete;

        static  void Exit() {ExitImpl();}

        static void AddCallBack(Callback func) {
            std::lock_guard<std::mutex> lock (glb().mutex_);
            CHECK(!glb().stopping_);
            glb().exit_funcs_.push_back(std::move(func));
        }

        static  void WaitUntilExited() {
            AsioErrorCode  err;
            glb().io_service_.run(err);
            CHECK(!err) << err;

        }

    private:
        static  ExitSys& glb() {
            CHECK_NOTNULL(g_instance_);
            return  *g_instance_;
        }

        static void  SignalHandle(const AsioErrorCode& err , int signal) {
            LOG(WARNING) << "SIGNAL: " << signal;
            CHECK(!err);
            ExitImpl();
        }

        ExitSys() {
            signal_set_.async_wait(SignalHandle);
        }

        static void ExitImpl();

    private:
        static  std::once_flag g_init_flag_;
        static ExitSys* g_instance_;
        IoService  io_service_;

        const IoService::work io_service_work_{io_service_};
        boost::asio::signal_set signal_set_{io_service_, SIGINT};
        std::mutex mutex_;
        bool stopping_ = false;
        std::vector<Callback> exit_funcs_;
    };
}








#endif //MDL_EXIT_SYS_H
