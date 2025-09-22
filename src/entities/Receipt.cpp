#include "Receipt.h"
#include <iostream>

void Receipt::generateReceipt(const Order& order) {
    customerName = order.getCustomerName();
    totalAmount = order.calculatePrice();
    receiptText = "Receipt for " + customerName + " - Total: $" + std::to_string(totalAmount);
}

void Receipt::printReceipt() {
    std::cout << receiptText << std::endl;
}