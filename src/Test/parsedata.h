//
// Created by xuchaowu on 19-10-30.
//

#ifndef TEST_PARSEDATA_H
#define TEST_PARSEDATA_H

#include <iostream>
#include "define.h"
#include <fstream>
#include <vector>


extern int64_t  ll_mkt_len ;
extern int64_t  ll_trade_len ;
extern int64_t  ll_order_len ;
extern int64_t  ll_index_len ;
extern int64_t  ll_all_len ;


bool getdatahead(std::ifstream& is,
                 int64_t& recv_time,
                 int& type ,
                 int& len);

template <class T>
bool getdata(std::vector<T>& t, std::ifstream& is, size_t len) {
    auto f= [&is](void* p ,size_t size) ->bool {
        is.read(reinterpret_cast<char*> (p), size);
        if (is.eof()) {
            return false;
        }
        if (!is.good()) {
            std::cout << ": parse invalid " << std::endl;
            return false;
        }

        return true;
    };

    size_t size = len / sizeof(T);
    for (int i = 0 ; i < size; i++) {
        T l;
        if (!f(&l, sizeof(l))) {
            std::cout << "get data error" << std::endl;
            return false;
        }
        t.push_back(l);
    }

    return  true;
}




template <MarketType type>
class ParseData {
public:
    static void Parse(const std::string &filename) {

    }
};

template <>
class ParseData<kUNknowned> {
public:
    static  void Parse(const std::string &filename) {
        std::ifstream is;
        is.open(filename);
        int64_t recv_time = -1;
        int type = -1;
        int len = -1;
        while (getdatahead(is, recv_time, type, len)) {
           switch (type) {
               case kLvl2MarketData: {
                   std::vector<TDF_MARKET_DATA> data;
                   if(getdata(data, is, len)) {
                       if (data.size() > 0) {
//                           std::cout << "kLvl2Orderdata: " << data[0].szCode << std::endl;
                           ll_mkt_len +=  data.size();
                       }
                       std::vector<TDF_MARKET_DATA> s;
                       data.swap(s);
                   } else {
                       break;
                   }
                   break;
               }

               case kLvl2Orderdata: {
                   std::vector<TDF_ORDER> data;
                   if(getdata(data, is, len)) {
                       if (data.size() > 0) {
                           ll_order_len +=  data.size();
//                           std::cout << "kLvl2Orderdata:" << data[0].szCode << std::endl;
                       }
                       std::vector<TDF_ORDER> s;
                       data.swap(s);
                   } else {
                       break;
                   }
               }

               case kLvl2Trade: {
                   std::vector<TDF_TRANSACTION> data;
                   if(getdata(data, is, len)) {
                       if (data.size() > 0) {
                           ll_trade_len +=  data.size();
                           std::cout << "kLvl2Trade:" << data[0].szCode << std::endl;
                       }
                       std::vector<TDF_TRANSACTION> s;
                       std::cout << "ll_trade_len: " << std::endl
                        data.swap(s);
                   } else {
                       break;
                   }

                   break;
               }

               case kLvl2IndexData: {
                   std::vector<TDF_INDEX_DATA> data;
                   if(getdata(data, is, len)) {
                       if (data.size() > 0) {
                           ll_index_len +=  data.size();
//                           std::cout << "kLvl2index:" << data[0].szCode << std::endl;
                       }
                       std::vector<TDF_INDEX_DATA> s;
                       data.swap(s);
                   } else {
                       break;
                   }

                   break;
               }

               default:
                   break;
           }
        }
    }

private:
};




template <>
class ParseData<kLvl2MarketData> { ;
public:
    static  void Parse(const std::string &filename) {
        std::ifstream is;
        is.open(filename);
        std::vector<TDF_MARKET_DATA> data;
        int64_t  recv_time =-1;
        int type = -1;
        int len = -1;
        while (getdatahead(is, recv_time, type, len)) {
            if(getdata(data, is, len)) {
                if (data.size() > 0)
                    std::cout << data[0].szCode << std::endl;
                std::vector<TDF_MARKET_DATA> s;
                data.swap(s);
            } else {
                break;
            }
        }
    }
};


template <>
class ParseData<kLvl2Orderdata> { ;
public:
    static  void Parse(const std::string &filename) {
        std::ifstream is;
        is.open(filename);
        std::vector<TDF_ORDER> data;

        int64_t  recv_time =-1;
        int type = -1;
        int len = -1;
        while (getdatahead(is, recv_time, type, len)) {
            if(getdata(data, is, len)) {
                if (data.size() > 0)
                    std::cout << data[0].szCode << std::endl;
                std::vector<TDF_ORDER> s;
                data.swap(s);
            } else {
                break;
            }
        }

    }
};


template <>
class ParseData<kLvl2Trade> { ;
public:
    static  void Parse(const std::string &filename) {
        std::ifstream is;
        is.open(filename);
        std::vector<TDF_TRANSACTION> data;
        int64_t  recv_time =-1;
        int type = -1;
        int len = -1;
        while (getdatahead(is, recv_time, type, len)) {
            if(getdata(data, is, len)) {
                if (data.size() > 0)
                    std::cout << data[0].szCode << std::endl;
                std::vector<TDF_TRANSACTION> s;
                data.swap(s);
            } else {
                break;
            }
        }
    }
};


template <>
class ParseData<kLvl2IndexData> { ;
public:
    static  void Parse(const std::string &filename) {
        std::ifstream is;
        is.open(filename);
        std::vector<TDF_INDEX_DATA> data;

        int64_t  recv_time =-1;
        int type = -1;
        int len = -1;
        while (getdatahead(is, recv_time, type, len)) {
            if(getdata(data, is, len)) {
                if (data.size() > 0)
                    std::cout << data[0].szCode << std::endl;
                std::vector<TDF_INDEX_DATA> s;
                data.swap(s);
            } else {
                break;
            }
        }
    }
};


class ParseDataWind {
public:
    ParseDataWind(const std::string& file):base_path_(file){

    }

    template <MarketType type>
    bool Parses(std::string filename) {
        base_path_ = base_path_ + "/" + filename;
        ParseData<type>::Parse(base_path_);
    }

private:
    std::string base_path_;
};


#endif //TEST_PARSEDATA_H
