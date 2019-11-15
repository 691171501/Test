//
// Created by xuchaowu on 19-11-7.
//

#include "LCS.h"
#include <string.h>
#include <algorithm>
#include <deque>
//std::tuple<int , std::vector<int>, std::vector<int>>

std::tuple<int, std::deque<int> , std::deque<int>>  Lsc(std::vector<int>&a,std::vector<int>&b, int direct) {

    const int lsize= a.size() +1;
    const int rsize= b.size() +1;
    int DP[lsize][rsize] ;
    memset(&DP, 0x00, sizeof(DP));
    for (int i = 1 ; i < lsize; i++)
        for (int j  = 1; j  < rsize; ++j ) {
            if (a[i-1] == b[j-1]) {
                DP[i][j] = std::max(DP[i][j], DP[i-1][j-1] +1);
            } else {
                DP[i][j] = std::max(DP[i][j -1], DP[i-1][j]);
            }
        }



    int k = lsize -1;
    int r = rsize -1 ;
    std::deque<int> lindex;
    std::deque<int> rindex;

    while (DP[k][r] >0 && k > 0 && r > 0) {
        if  (a[k -1] == b[r-1]) {
            lindex.push_front(k-1);
            rindex.push_front(r-1);
            k--;
            r--;
        } else {
            if (DP[k][r-1] == DP[k-1][r])  {
                if (direct ==0)
                    k--;
                else
                    r--;
            } else {
                if (DP[k][r-1] > DP[k-1][r]) r--;
                else
                    k--;
            }

        }
    }
    std::tuple<int, std::deque<int> , std::deque<int>> result = std::make_tuple(DP[lsize-1][rsize-1], lindex , rindex);
    return  result;

}