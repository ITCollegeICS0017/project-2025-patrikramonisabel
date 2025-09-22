#include "Report.h"
#include <iostream>

void Report::generateDailyReport() {
    std::cout << "Daily Report Generated" << std::endl;
}

void Report::showCompletedOrders(const std::vector<Order>& orders) {
    std::cout << "Completed Orders:" << std::endl;
    for (const auto& order : orders) {
        if (order.getStatus() == "Completed") {
            std::cout << "- " << order.getCustomerName() << std::endl;
        }
    }
}

double Report::calculateDailyRevenue(const std::vector<Receipt>& receipts) {
    double totalRevenue = 0.0;
    for (const auto& receipt : receipts) {
        totalRevenue += 50.0;
    }
    return totalRevenue;
}