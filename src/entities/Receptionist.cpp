#include "Receptionist.h"

Receptionist::Receptionist() : currentOrder(nullptr) {}

Receptionist::~Receptionist() {
    delete currentOrder;
}

bool Receptionist::createOrderRecord(const std::string& customerName, const std::string& photos, const std::string& orderType) {
    clearCurrentOrder();
    currentOrder = new Order();
    currentOrder->storeOrderDetails(customerName, photos, orderType);
    return currentOrder != nullptr;
}

bool Receptionist::setExpressOrderFlag(bool isExpress) {
    if (currentOrder) {
        currentOrder->setExpress(isExpress);
        return true;
    }
    return false;
}

Order* Receptionist::getCurrentOrder() const {
    return currentOrder;
}

void Receptionist::clearCurrentOrder() {
    if (currentOrder) {
        delete currentOrder;
        currentOrder = nullptr;
    }
}