#pragma once
#include "Order.h"
#include <vector>

class Photographer {
private:
    std::vector<Order*> currentOrders;

public:
    void processOrders();
    void developPhotos();
    void markOrderAsCompleted();
    void addOrder(Order* order);
};