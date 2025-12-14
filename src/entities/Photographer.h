#pragma once
#include "Order.h"
#include <vector>

class Photographer {
private:
    std::vector<Order*> currentOrders;

public:
    int processOrders();
    bool developPhotos();
    int markOrderAsCompleted();
    void addOrder(Order* order);
    std::vector<Order*> getCurrentOrders() const;
    int getOrderCount() const;
};