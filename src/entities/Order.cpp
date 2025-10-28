#include "Order.h"

void Order::storeOrderDetails(const std::string& customer, const std::string& photos, const std::string& type) {
    customerName = customer;
    this->photos = photos;
    orderType = type;
    status = OrderStatus::PENDING;
    isExpress = false;
}

double Order::calculatePrice() const {
    double price = BASE_PRICE;
    if (isExpress) {
        price *= EXPRESS_MULTIPLIER;
    }
    return price;
}

void Order::trackOrderStatus(OrderStatus newStatus) {
    status = newStatus;
}

void Order::trackMaterialsUsed(const std::string& materials) {
    materialsUsed = materials;
}

std::string Order::getCustomerName() const {
    return customerName;
}

OrderStatus Order::getStatus() const {
    return status;
}

std::string Order::getStatusString() const {
    switch (status) {
        case OrderStatus::PENDING:
            return "Pending";
        case OrderStatus::PROCESSING:
            return "Processing";
        case OrderStatus::IN_PROGRESS:
            return "In Progress";
        case OrderStatus::COMPLETED:
            return "Completed";
        default:
            return "Unknown";
    }
}

bool Order::getIsExpress() const {
    return isExpress;
}

void Order::setExpress(bool express) {
    isExpress = express;
}