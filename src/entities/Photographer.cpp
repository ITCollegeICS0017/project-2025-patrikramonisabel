#include "Photographer.h"

int Photographer::processOrders() {
    int processedCount = 0;
    for (auto order : currentOrders) {
        if (order->getStatus() == OrderStatus::PENDING) {
            order->trackOrderStatus(OrderStatus::IN_PROGRESS);
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
        if (order->getStatus() == OrderStatus::IN_PROGRESS) {
            order->trackOrderStatus(OrderStatus::COMPLETED);
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