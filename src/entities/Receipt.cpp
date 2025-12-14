#include "Receipt.h"
#include "StudioExceptions.h"
#include <iomanip>
#include <sstream>

void Receipt::generateReceipt(const Order& order, int orderIndex) {
    if (orderIndex < 0) {
        throw RepositoryException("Invalid order reference for receipt.");
    }

    orderId = orderIndex;
    customerName = order.getCustomerName();
    totalAmount = order.calculatePrice();
    
    std::stringstream ss;
    ss << "========================================\n";
    ss << "           RECEIPT\n";
    ss << "========================================\n";
    ss << "Customer: " << customerName << "\n";
    ss << "Order Type: " << (order.getIsExpress() ? "Express" : "Standard") << "\n";
    ss << "Status: " << order.getStatusString() << "\n";
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

int Receipt::getOrderId() const {
    return orderId;
}