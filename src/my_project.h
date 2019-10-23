//
// Created by xuchaowu on 10/22/19.
//

#ifndef TEST_MY_PROJECT_H
#define TEST_MY_PROJECT_H

class my_project {

public:
    my_project();

    void print_data(int n) {
           print("current_data: %d ", n);
    }

private:
    int pos_;
};


#endif //TEST_MY_PROJECT_H
