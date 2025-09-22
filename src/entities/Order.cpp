#include "Order.h"

void Order::storeOrderDetails(const std::string& customer, const std::string& photos, const std::string& type) {
    customerName = customer;
    this->photos = photos;
    orderType = type;
    status = "Pending";
    isExpress = false;
}

double Order::calculatePrice() {
    double basePrice = 50.0;
    if (isExpress) {
        basePrice *= 1.25;
    }
    return basePrice;
}

void Order::trackOrderStatus(const std::string& newStatus) {
    status = newStatus;
}

void Order::trackMaterialsUsed(const std::string& materials) {
    materialsUsed = materials;
}

std::string Order::getCustomerName() const {
    return customerName;
}

std::string Order::getStatus() const {
    return status;
}

bool Order::getIsExpress() const {
    return isExpress;
}

void Order::setExpress(bool express) {
    isExpress = express;
}