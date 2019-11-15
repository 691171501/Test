//
// Created by xuchaowu on 19-10-28.
//

#ifndef MDL_QUEUE_H
#define MDL_QUEUE_H
#include <iostream>
#include <mutex>
#include <functional>
#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <atomic>

namespace  zsequity {
    namespace rawdata {
        template<class T, size_t MaxCapacity>
        class Queue {
        public:
            void Push(T input) {
                std::unique_lock<std::mutex> lock(mutex_);
                if (closed) {
                    return;
                }
                if (deque_.size() >= MaxCapacity) {
                    cv_not_full_.wait(lock);
                } else {
                    deque_.push_back(std::move(input));
                    cv_not_empty_.notify_one();
                }
                return;
            }

            bool Pop(T &out) {
                std::unique_lock<std::mutex> lock(mutex_);
                if (closed) {
                    return false;
                }

                if (deque_.empty()) {
                    cv_not_empty_.wait(lock);
                    if (deque_.empty() && !closed) {
                        return false;
                    }
                }

                out = std::move(deque_.front());
                deque_.pop_front();
                cv_not_full_.notify_one();
                return true;
            }

            void Close() {
                std::unique_lock<std::mutex> lock(mutex_);
                closed = true;
                cv_not_empty_.notify_all();
            }

        private:
            std::mutex mutex_;
            std::condition_variable cv_not_full_, cv_not_empty_;
            std::atomic<bool> closed;
            std::deque<T> deque_;
        };
    }
}

#endif //MDL_QUEUE_H
