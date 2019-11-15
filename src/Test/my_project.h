//
// Created by xuchaowu on 10/22/19.
//

#ifndef TEST_MY_PROJECT_H
#define TEST_MY_PROJECT_H

#include <iostream>

class my_project {

public:
    my_project() {
        std::cout << "hello" << std::endl;
    }

    void print_data(int n) {
        std::cout << "n: " << n <<std::endl;

    }

private:
    int pos_;
    double price;
};


#endif //TEST_MY_PROJECT_H
