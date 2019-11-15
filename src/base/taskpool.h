//
// Created by xuchaowu on 19-10-29.
//

#ifndef MDL_TASKPOOL_H
#define MDL_TASKPOOL_H

#include <map>
#include "boost/asio.hpp"
#include "boost/asio/steady_timer.hpp"
#include <functional>
#include "common.h"
#include <memory>
#include <vector>
#include <thread>
#include <mutex>

template <typename  T, typename... Args>
std::unique_ptr<T> MakeUnique(Args&&... args) {
    return  std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}



namespace zsequity {

    class TaskPool {
    public:
        using IoService = boost::asio::io_service ;
        using AsioErrorCode = boost::system::error_code;
        using AsioWaitableTimer = boost::asio::basic_waitable_timer<std::chrono::steady_clock>;
        using Task = std::function<double()>;
        TaskPool(int thread_pool_size =1, int initial_timers = 8) {
            CHECK(1 <= thread_pool_size && thread_pool_size <= 8) << thread_pool_size;
            CHECK(0 <= initial_timers && initial_timers <= 256) << initial_timers;
            timers_buf_.reserve(256);
            for (int i =0; i < thread_pool_size ; i++) {
                thread_pool_.push_back(std::thread([this]{
                    io_service.run();
                }));
            }

            for (int i =0 ; i < initial_timers; i++) {
                timers_buf_.push_back(new AsioWaitableTimer(io_service));
            }
        }


        TaskPool(const TaskPool& rhs) = delete;
        TaskPool& operator= (const TaskPool& rhs) = delete;

        ~TaskPool() {
            for (auto& ths : thread_pool_) ths.join();
            io_service.stop();
            io_service_work_.reset();

            for (auto& kv : timers_) {
                delete kv.second;
            }

            for (auto& e : timers_buf_) {
                delete e;
            }

            tasks_.clear();
            timers_.clear();
            timers_buf_.clear();
        }

        void RegistTask(double sec, Task task) {
            CHECK_GE(sec, 0);
            CHECK_LE(sec, 1e6);
            std::lock_guard<std::mutex> lock(mutex_);
            int id = 0;
            if (tasks_.size() > 0) {
                id = tasks_.rbegin()->first +1 ;
            }

            AsioWaitableTimer * timer = nullptr;
            {
                if (timers_buf_.size() > 0) {
                    timer = timers_buf_.back();
                    timers_buf_.pop_back();
                    timer->expires_from_now(std::chrono::microseconds(static_cast<int64_t>(1e6 * sec)));
                } else {
                    timer = new AsioWaitableTimer(io_service, std::chrono::microseconds(static_cast<int64_t>(1e6 * sec)));
                }
            }

            tasks_.insert({id,std::move(task)});
            timers_.insert({id, timer});
            timer->async_wait(std::bind(&TaskPool::RunTask, this, id, std::placeholders::_1));
        }


    private:
        void RunTask(int id, AsioErrorCode err) {
            if(err == boost::asio::error::operation_aborted) {
                return;
            }

            Task  task;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                CHECK(tasks_.find(id) != tasks_.end()) << id;
                task = std::move(tasks_.at(id));
            }

            double sec = task() ;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                if(sec < 0) {
                    tasks_.erase(id);
                    CHECK(timers_.find(id) != timers_.end()) << id;
                    timers_buf_.push_back(timers_.at(id));
                    timers_.erase(id);
                } else {
                    CHECK(tasks_.find(id) != tasks_.end()) << id;
                    tasks_.at(id) = std::move(task);
                    CHECK(timers_.find(id) != timers_.end()) << id;
                    timers_.at(id)->expires_from_now(std::chrono::microseconds(static_cast<int64_t>(1e6 * sec)));
                    timers_.at(id)->async_wait(std::bind(&TaskPool::RunTask, this, id, std::placeholders::_1));
                }
            }
        }

    private:
        IoService  io_service;
        std::unique_ptr<IoService::work> io_service_work_ = MakeUnique<IoService::work>(io_service);
        std::vector<std::thread> thread_pool_;
        std::mutex   mutex_;
        std::map<int, Task> tasks_;
        std::map<int , AsioWaitableTimer*> timers_;
        std::vector<AsioWaitableTimer*> timers_buf_;
    };



}






#endif //MDL_TASKPOOL_H
