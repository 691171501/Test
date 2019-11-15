//
// Created by xuchaowu on 10/22/19.
//

#include "my_project.h"
#include <signal.h>
#include <stdio.h>
#include "parsedata.h"
#include "common.h"
#include "d_p.h"
#include "LCS.h"
#include "clockdiff_remote.h"


void handle(int num) {
    std::cout << "Receive signal: " << num << std::endl;
}

void test_signal() {
    sigset(SIGINT, handle);
    getchar();
}


void test_boost_signal() {
    zsequity::ExitSys::WaitUntilExited();

}


void  parse_wind_data() {
    ParseDataWind parse("/home/xuchaowu/fenxi_wind_data2");
//    parse.Parses<kLvl2MarketData>("lvl2market_20191030_night.raw");
//parse.Parses<kLvl2Trade>("lvl2trade_20191030_night.raw");
    //parse.Parses<kLvl2Orderdata>("lvl2order_20191030_night.raw");


//    parse.Parses<kLvl2IndexData>("lvl2index_20191030_night.raw");

    parse.Parses<kUNknowned>("lvl2_20191101_night.raw");
}

void get_data() {
    DP dp;
    char* ptr = dp.get_data();
    PK* p = (PK*)ptr;
    char* dv= new char[p->num];
    memcpy(dv, ptr, p->num);
    delete [] ptr;
    ptr = nullptr;
    PK* p2 = (PK*)dv;
    auto dd = (DATA*)(dv+ sizeof(PK));
    std::cout << p2->ll;
    delete [] dv;

}



void get_clock_diff_info () {
    ClockDiffRemote diff("47.100.245.244");
    diff.Execute();
}


enum BIT {

    a = 0x1,
    b = 0x2,
    c = 0x4,
    d = 0x8,
    e = 0x10,
    f = 0x20,
};

void  Testbit() {
    int data = a | e | c;
    if (data & a) {
        std::cout << "a" << std::endl;
    }

    if (data & b) {
        std::cout << "b" << std::endl;
    }

    if (data & c) {
        std::cout << "c" << std::endl;
    }
    if (data & d) {
        std::cout << "d" << std::endl;
    }

    if (data & e) {
        std::cout << "e" << std::endl;
    }
}


void TestLSC() {
//    std::vector<int> a{1,3,4,5,6,7,7,8};
//    std::vector<int> b{3,5,7,4,8,6,7,8,2};
//    std::vector<int> a{1,3,4,5,6,7,7,8};
//    std::vector<int> b;
//    auto data = Lsc(a,b, 0);
//    std::cout << "num: " << std::get<0>(data) << std::endl;
//    auto l = std::get<1>(data);
//    for (auto v : l )
//       std::cout << "a_index: " << v << " ,"<< a[v]<<  std::endl;
//
//    std::cout << "******************************************"<<std::endl;
//    auto r = std::get<2>(data);
//    for (auto v : r )
//        std::cout << "b_index: " << v <<" ,"<< b[v]<<std::endl;
//
//    std::cout << "^^^^^^^^^^^^^^^^^^^^^^^"<<std::endl;
//    auto data2 = Lsc(a,b, 1);
//    std::cout << "num: " << std::get<0>(data2) << std::endl;
//    auto l2 = std::get<1>(data2);
//    for (auto v : l2 )
//        std::cout << "a_index: " << v << " ,"<< a[v]<<  std::endl;
//
//    std::cout << "******************************************"<<std::endl;
//    auto r2 = std::get<2>(data2);
//    for (auto v : r2 )
//        std::cout << "b_index: " << v <<" ,"<< b[v]<<std::endl;

}


int zero_array(int64_t l, int64_t r)
{
    const int lz =l;
    const int  rz = r;
//    int  a[lz][rz] ={0};
//    memset(a, 0, sizeof(a));
    std::cout << "zero over" << std::endl;
}


void TestTransform () {

    std::vector<int> v1{1,2,3,5,6};
    std::vector<int> v2{6,5,5,6,5};
    std::vector<int> rr(v1.size(), 0);
    rr.reserve(v1.size() *2);
    std::transform(v1.begin(), v1.end(), v2.begin(), rr.begin(), [=](int l, int r) {
        return l*r;
    } );

    for (auto val : v1) {
        std::cout << val << std::endl;
    }

    std::cout << "&&&&&&&"<<std::endl;

    for (auto val : v2) {
        std::cout << val << std::endl;
    }

    std::cout << "&&&&&&&"<<std::endl;

    for (auto val : rr) {
        std::cout << val << std::endl;
    }
}





int main() {
//    zsequity::InitSystem("MDL");
//    std::thread th = std::thread([=] {
//        test_boost_signal();
//    });
//    zsequity::ExitSys::AddCallBack([]() {
//        std::cout << "my test signal " << std::endl;
//    });
////
//    get_data();
//    parse_wind_data();
//
//    std::cout << "ll_mkt_len: " << ll_mkt_len
//              <<"ll_trade_len: " << ll_trade_len
//              <<"ll_order_len: " << ll_order_len
//              <<"ll_index_len: " << ll_index_len
//              << std::endl;
//    parse_wind_data();
//    get_clock_diff_info();

//    getchar();
//    th.join();

    zero_array(584, 58);
//    TestTransform();
//    TestLSC();
//    Testbit();
    getchar();

    return  0;
}