#pragma once
#include "Order.h"

class Receptionist {
private:
    Order* currentOrder;

public:
    void takeCustomerOrder();
    void createOrderRecord();
    void setExpressOrderFlag();
    Order* getCurrentOrder();
};