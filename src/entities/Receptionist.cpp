#include "Receptionist.h"
#include <iostream>

void Receptionist::takeCustomerOrder() {
    std::cout << "Taking customer order..." << std::endl;
}

void Receptionist::createOrderRecord() {
    currentOrder = new Order();
    currentOrder->storeOrderDetails("Customer", "Photos", "Standard");
}

void Receptionist::setExpressOrderFlag() {
    if (currentOrder) {
        currentOrder->setExpress(true);
    }
}

Order* Receptionist::getCurrentOrder() {
    return currentOrder;
}