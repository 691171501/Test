//
// Created by xuchaowu on 19-10-28.
//

#ifndef MDL_TIME_UTILS_H
#define MDL_TIME_UTILS_H

#include <ctime>
#include <limits>
#include <cstdio>
#include <thread>


namespace  zsequity {
   using TimestampNs  = int64_t;
   constexpr  TimestampNs  kTimestampNsInf = std::numeric_limits<TimestampNs>::max();
   constexpr  int64_t  KE9 = 1000000000LL;
   constexpr  int64_t  KE6 = 1000000LL;
   constexpr  int64_t  KE3 = 1000LL;
   constexpr int64_t  kOneDayNs = 24 * 60 * 60 * KE9;

   struct DateTime {
       enum class ToStringType {
           kDateOnly,
           kTimeOnly,
           kFull
       };

       int year;
       int month;
       int day;
       int hour;
       int minute;
       int second;
       int nanosecond;

       static  DateTime FromTimestampNs(TimestampNs ts) {
           auto time_t_ts =(std::time_t) (ts/ KE9);
           tm tm_ts;
           localtime_r(&time_t_ts, &tm_ts);
           DateTime dt {
               tm_ts.tm_year + 1900,
               tm_ts.tm_mon + 1,
               tm_ts.tm_mday,
               tm_ts.tm_hour,
               tm_ts.tm_min,
               tm_ts.tm_sec,
               static_cast<int>(ts % KE9)
           };

           if (dt.second > 59) {
               dt.second = 59;
           }
           return  dt;
       }

   };


   inline TimestampNs NowUtcNS() {
       timespec ts;
       clock_gettime(CLOCK_REALTIME, &ts);
       return  ts.tv_sec * KE9 + ts.tv_nsec;
   }

}


#endif //MDL_TIME_UTILS_H
