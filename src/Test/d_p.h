//
// Created by xuchaowu on 19-10-31.
//

#ifndef TEST_D_P_H
#define TEST_D_P_H

#include <stdint.h>
#include <string.h>

struct DATA {
    double price;
    int op ;

};

struct PK {
    int num;
    int64_t  ll;
    DATA* data;
};


class DP {
public:
    DP() {
        memset(&p_, 0x00, sizeof(PK));
    }
    char* get_data() {
        char * data = new char[sizeof(PK) + sizeof(DATA)];
        DATA d;
        memset(&d, 0x000, sizeof(d));
        d.op = 100;
        d.price = 99.32;
        p_.num = sizeof(PK) + sizeof(DATA);
        p_.ll = 1230;
        memcpy(data, &p_, sizeof(p_));
        memcpy(data+ sizeof(p_), &d, sizeof(d));
        ((PK*)data)->data = (DATA*)(data + sizeof(p_));
    }

private:
    PK p_;
};


#endif //TEST_D_P_H
