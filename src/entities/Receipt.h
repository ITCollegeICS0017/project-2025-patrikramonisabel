#pragma once
#include "Order.h"

class Receipt {
public:
    void generateReceipt(const Order& order);
    void printReceipt();
};