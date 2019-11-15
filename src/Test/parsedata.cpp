//
// Created by xuchaowu on 19-10-30.
//

#include "parsedata.h"


bool getdatahead(std::ifstream& is,
                 int64_t& recv_time,
                 int& type ,
                 int& len) {
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

    if (!f(&recv_time, sizeof(recv_time))) {
        std::cout << "get recv_time error" <<std::endl;
        return false;
    }

    if (!f(&type, sizeof(type))) {
        std::cout << "get type error" <<std::endl;
        return false;
    }

    if (!f(&len, sizeof(len))) {
        std::cout << "get len error" <<std::endl;
        return false;
    }
    return true;

}

int64_t  ll_mkt_len =0;
int64_t  ll_trade_len {0};
int64_t  ll_order_len {0};
int64_t  ll_index_len {0};
int64_t  ll_all_len {0};