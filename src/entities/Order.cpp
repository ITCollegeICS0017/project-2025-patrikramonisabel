#include "Order.h"

void Order::storeOrderDetails(const std::string& customer, const std::string& photos, const std::string& type) {
    // Placeholder implementation
}

double Order::calculatePrice() {
    // Placeholder implementation - base price + 25% if express
    return 0.0;
}

void Order::trackOrderStatus(const std::string& newStatus) {
    // Placeholder implementation
}

void Order::trackMaterialsUsed(const std::string& materials) {
    // Placeholder implementation
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