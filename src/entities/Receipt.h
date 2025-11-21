#pragma once
#include "Order.h"
#include <string>

class Receipt {
private:
    std::string customerName;
    double totalAmount;
    std::string receiptText;
    int orderId = -1;

public:
    void generateReceipt(const Order& order, int orderIndex);
    std::string getReceiptText() const;
    double getTotalAmount() const;
    std::string getCustomerName() const;
    int getOrderId() const;
};