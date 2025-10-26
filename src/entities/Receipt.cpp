#include "Receipt.h"
#include <sstream>
#include <iomanip>

void Receipt::generateReceipt(const Order& order) {
    customerName = order.getCustomerName();
    totalAmount = order.calculatePrice();
    
    std::stringstream ss;
    ss << "========================================\n";
    ss << "           RECEIPT\n";
    ss << "========================================\n";
    ss << "Customer: " << customerName << "\n";
    ss << "Order Type: " << (order.getIsExpress() ? "Express" : "Standard") << "\n";
    ss << "Status: " << order.getStatus() << "\n";
    ss << "----------------------------------------\n";
    ss << "Total Amount: $" << std::fixed << std::setprecision(2) << totalAmount << "\n";
    ss << "========================================\n";
    
    receiptText = ss.str();
}

std::string Receipt::getReceiptText() const {
    return receiptText;
}

double Receipt::getTotalAmount() const {
    return totalAmount;
}

std::string Receipt::getCustomerName() const {
    return customerName;
}