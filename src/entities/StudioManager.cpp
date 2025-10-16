#include "StudioManager.h"
#include <iostream>

bool StudioManager::createNewOrder(const std::string& customerName, const std::string& photos, 
                                    const std::string& orderType, bool isExpress) {
    Order newOrder;
    newOrder.storeOrderDetails(customerName, photos, orderType);
    newOrder.setExpress(isExpress);
    orders.push_back(newOrder);
    
    return true;
}

bool StudioManager::processOrder(int orderIndex) {
    if (orderIndex >= 0 && orderIndex < orders.size()) {
        photographer.addOrder(&orders[orderIndex]);
        orders[orderIndex].trackOrderStatus("Processing");
        return true;
    }
    return false;
}

bool StudioManager::completeOrder(int orderIndex) {
    if (orderIndex >= 0 && orderIndex < orders.size()) {
        orders[orderIndex].trackOrderStatus("Completed");
        return true;
    }
    return false;
}

bool StudioManager::generateReceipt(int orderIndex) {
    if (orderIndex >= 0 && orderIndex < orders.size()) {
        Receipt receipt;
        receipt.generateReceipt(orders[orderIndex]);
        receipts.push_back(receipt);
        receipt.printReceipt();
        return true;
    }
    return false;
}

double StudioManager::generateDailyReport() {
    report.generateDailyReport();
    report.showCompletedOrders(orders);
    double revenue = report.calculateDailyRevenue(receipts);
    return revenue;
}

std::vector<Order> StudioManager::getAllOrders() const {
    return orders;
}

Order* StudioManager::getOrder(int index) {
    if (index >= 0 && index < orders.size()) {
        return &orders[index];
    }
    return nullptr;
}

double StudioManager::calculateTotalRevenue() const {
    return report.calculateDailyRevenue(receipts);
}

