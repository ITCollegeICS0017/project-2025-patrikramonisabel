#pragma once
#include <string>

class Order {
private:
    std::string customerName;
    std::string photos;
    std::string orderType;
    std::string status;
    std::string materialsUsed;
    bool isExpress;

public:
    void storeOrderDetails(const std::string& customer, const std::string& photos, const std::string& type);
    double calculatePrice() const;
    void trackOrderStatus(const std::string& newStatus);
    void trackMaterialsUsed(const std::string& materials);
    std::string getCustomerName() const;
    std::string getStatus() const;
    bool getIsExpress() const;
    void setExpress(bool express);
};