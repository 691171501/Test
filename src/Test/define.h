//
// Created by xuchaowu on 19-10-25.
//

#ifndef MDL_DEFINE_H
#define MDL_DEFINE_H

#include <iostream>
#include <stdint.h>
#include "../include/TDFAPIStruct.h"


enum   MarketType {
    kUNknowned = 0,
    kLvl2IndexData = MSG_DATA_INDEX,
    kLvl2MarketData = MSG_DATA_MARKET,
    kLvl2Trade = MSG_DATA_TRANSACTION,
    kLvl2OrderQueue = MSG_DATA_ORDERQUEUE,
    kLvl2Orderdata = MSG_DATA_ORDER
};



#endif //MDL_DEFINE_H
