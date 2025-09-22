#include "Photographer.h"
#include <iostream>

void Photographer::processOrders() {
    for (auto order : currentOrders) {
        if (order->getStatus() == "Pending") {
            order->trackOrderStatus("In Progress");
        }
    }
}

void Photographer::developPhotos() {
    std::cout << "Developing photos..." << std::endl;
}

void Photographer::markOrderAsCompleted() {
    for (auto order : currentOrders) {
        if (order->getStatus() == "In Progress") {
            order->trackOrderStatus("Completed");
        }
    }
}

void Photographer::addOrder(Order* order) {
    currentOrders.push_back(order);
}