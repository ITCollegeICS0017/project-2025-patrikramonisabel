#pragma once
#include "Order.h"
#include <string>

class Receipt {
private:
    std::string customerName;
    double totalAmount;
    std::string receiptText;

public:
    void generateReceipt(const Order& order);
    void printReceipt();
};