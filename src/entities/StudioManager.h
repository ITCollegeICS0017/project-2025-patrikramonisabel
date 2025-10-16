#pragma once
#include "Order.h"
#include "Photographer.h"
#include "Receipt.h"
#include "Report.h"
#include <vector>
#include <string>

class StudioManager {
private:
    std::vector<Order> orders;
    std::vector<Receipt> receipts;
    Photographer photographer;
    Report report;

public:
    // Core business operations
    bool createNewOrder(const std::string& customerName, const std::string& photos, const std::string& orderType, bool isExpress);
    bool processOrder(int orderIndex);
    bool completeOrder(int orderIndex);
    bool generateReceipt(int orderIndex);
    double generateDailyReport();
    
    // Query operations
    std::vector<Order> getAllOrders() const;
    Order* getOrder(int index);
    double calculateTotalRevenue() const;
};

