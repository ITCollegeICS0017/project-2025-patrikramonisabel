#pragma once
#include "Order.h"
#include <string>

class Receptionist {
private:
    Order* currentOrder;

public:
    Receptionist();
    ~Receptionist();
    
    bool createOrderRecord(const std::string& customerName, const std::string& photos, const std::string& orderType);
    bool setExpressOrderFlag(bool isExpress);
    Order* getCurrentOrder() const;
    void clearCurrentOrder();
};