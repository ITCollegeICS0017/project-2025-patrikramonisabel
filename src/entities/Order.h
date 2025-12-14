#pragma once
#include <string>

enum class OrderStatus {
    PENDING,
    PROCESSING,
    IN_PROGRESS,
    COMPLETED
};

class Order {
private:
    std::string customerName;
    std::string photos;
    std::string orderType;
    OrderStatus status;
    std::string materialsUsed;
    bool isExpress;

    // Pricing constants
    static constexpr double BASE_PRICE = 50.0;
    static constexpr double EXPRESS_MULTIPLIER = 1.25;

public:
    void storeOrderDetails(const std::string& customer, const std::string& photos, const std::string& type);
    double calculatePrice() const;
    void trackOrderStatus(OrderStatus newStatus);
    void trackMaterialsUsed(const std::string& materials);
    std::string getCustomerName() const;
    std::string getPhotosDescription() const;
    std::string getOrderType() const;
    OrderStatus getStatus() const;
    std::string getStatusString() const;
    bool getIsExpress() const;
    std::string getMaterialsUsed() const;
    void setExpress(bool express);
};