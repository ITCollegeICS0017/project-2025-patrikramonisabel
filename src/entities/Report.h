#pragma once
#include "Order.h"
#include "Receipt.h"
#include <vector>

class Report {
public:
    void generateDailyReport();
    void showCompletedOrders(const std::vector<Order>& orders);
    double calculateDailyRevenue(const std::vector<Receipt>& receipts);
};