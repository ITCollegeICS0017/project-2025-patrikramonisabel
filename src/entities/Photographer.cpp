#include "Photographer.h"

int Photographer::processOrders() {
    int processedCount = 0;
    for (auto order : currentOrders) {
        if (order->getStatus() == "Pending") {
            order->trackOrderStatus("In Progress");
            processedCount++;
        }
    }
    return processedCount;
}

bool Photographer::developPhotos() {
    // Logic for developing photos
    return !currentOrders.empty();
}

int Photographer::markOrderAsCompleted() {
    int completedCount = 0;
    for (auto order : currentOrders) {
        if (order->getStatus() == "In Progress") {
            order->trackOrderStatus("Completed");
            completedCount++;
        }
    }
    return completedCount;
}

void Photographer::addOrder(Order* order) {
    currentOrders.push_back(order);
}

std::vector<Order*> Photographer::getCurrentOrders() const {
    return currentOrders;
}

int Photographer::getOrderCount() const {
    return currentOrders.size();
}