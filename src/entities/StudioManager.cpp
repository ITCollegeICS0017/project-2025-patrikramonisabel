#include "StudioManager.h"
#include "OrderRules.h"
#include "StudioExceptions.h"
#include <algorithm>
#include <cctype>
#include <iostream>

namespace {
    std::string trimCopy(const std::string& value) {
        const auto begin = std::find_if_not(
            value.begin(),
            value.end(),
            [](unsigned char ch) { return std::isspace(ch); }
        );

        if (begin == value.end()) {
            return "";
        }

        const auto end = std::find_if_not(
            value.rbegin(),
            value.rend(),
            [](unsigned char ch) { return std::isspace(ch); }
        ).base();

        return std::string(begin, end);
    }

    std::string toLowerCopy(std::string value) {
        std::transform(
            value.begin(),
            value.end(),
            value.begin(),
            [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); }
        );
        return value;
    }

    void ensureCustomerNameValid(const std::string& name) {
        if (name.size() < 2 || name.size() > 100) {
            throw BusinessRuleException("Customer name must contain 2-100 characters.");
        }

        const bool validCharacters = std::all_of(
            name.begin(),
            name.end(),
            [](unsigned char ch) {
                return std::isalpha(ch) || std::isspace(ch) || ch == '-' || ch == '\'';
            }
        );

        if (!validCharacters) {
            throw BusinessRuleException("Customer name may only include letters, spaces, hyphens, or apostrophes.");
        }
    }

    void ensurePhotosValid(const std::string& photos) {
        if (photos.size() < 10 || photos.size() > 500) {
            throw BusinessRuleException("Please describe the photos in 10-500 characters.");
        }
    }

    void ensureOrderTypeValid(const std::string& orderType) {
        const std::string lowered = toLowerCopy(orderType);
        const bool allowed = std::any_of(
            order_rules::kAllowedOrderTypes.begin(),
            order_rules::kAllowedOrderTypes.end(),
            [&](const std::string_view allowedType) {
                return lowered == toLowerCopy(std::string(allowedType));
            }
        );

        if (!allowed) {
            throw BusinessRuleException("Unsupported order type selected.");
        }
    }

    void ensureOrderIndexWithinBounds(const OrderRepository& repository, int index) {
        if (index < 0 || index >= static_cast<int>(repository.size())) {
            throw BusinessRuleException("Please select a valid order number from the list.");
        }
    }

    bool hasOpenOrderWithName(const OrderRepository& repository, const std::string& customerName) {
        for (int i = 0; i < static_cast<int>(repository.size()); ++i) {
            const Order* existing = repository.tryGet(i);
            if (!existing) {
                continue;
            }
            if (existing->getCustomerName() == customerName &&
                existing->getStatus() != OrderStatus::COMPLETED) {
                return true;
            }
        }
        return false;
    }

    bool receiptExistsForOrder(const std::vector<Receipt>& receipts, int orderIndex) {
        return std::any_of(
            receipts.begin(),
            receipts.end(),
            [&](const Receipt& receipt) {
                return receipt.getOrderId() == orderIndex;
            }
        );
    }
}

StudioManager::StudioManager(OrderRepository& repositoryRef)
    : repository(repositoryRef) {}

bool StudioManager::createNewOrder(const std::string& customerName, const std::string& photos, 
                                    const std::string& orderType, bool isExpress) {
    const std::string sanitizedName = trimCopy(customerName);
    const std::string sanitizedPhotos = trimCopy(photos);
    const std::string sanitizedOrderType = trimCopy(orderType);

    ensureCustomerNameValid(sanitizedName);
    ensurePhotosValid(sanitizedPhotos);
    ensureOrderTypeValid(sanitizedOrderType);

    if (hasOpenOrderWithName(repository, sanitizedName)) {
        throw BusinessRuleException("This customer already has an active order today.");
    }

    Order newOrder;
    newOrder.storeOrderDetails(sanitizedName, sanitizedPhotos, sanitizedOrderType);
    newOrder.setExpress(isExpress);
    repository.add(newOrder);
    
    return true;
}

bool StudioManager::processOrder(int orderIndex) {
    ensureOrderIndexWithinBounds(repository, orderIndex);

    Order* orderPtr = repository.tryGet(orderIndex);
    if (orderPtr == nullptr) {
        throw RepositoryException("Order storage unavailable.");
    }

    Order& order = *orderPtr;
    if (order.getStatus() != OrderStatus::PENDING) {
        throw BusinessRuleException("Only pending orders can be sent to the photographer.");
    }

    photographer.addOrder(&order);
    order.trackOrderStatus(OrderStatus::PROCESSING);
    return true;
}

bool StudioManager::completeOrder(int orderIndex) {
    ensureOrderIndexWithinBounds(repository, orderIndex);

    Order* orderPtr = repository.tryGet(orderIndex);
    if (orderPtr == nullptr) {
        throw RepositoryException("Order storage unavailable.");
    }

    Order& order = *orderPtr;
    if (order.getStatus() == OrderStatus::COMPLETED) {
        throw BusinessRuleException("This order is already completed.");
    }

    if (order.getStatus() == OrderStatus::PENDING) {
        throw BusinessRuleException("Process the order before marking it complete.");
    }

    order.trackOrderStatus(OrderStatus::COMPLETED);
    return true;
}

bool StudioManager::generateReceipt(int orderIndex) {
    ensureOrderIndexWithinBounds(repository, orderIndex);

    const Order* orderPtr = repository.tryGet(orderIndex);
    if (orderPtr == nullptr) {
        throw RepositoryException("Order storage unavailable.");
    }

    const Order& order = *orderPtr;
    if (order.getStatus() != OrderStatus::COMPLETED) {
        throw BusinessRuleException("Receipts are available only for completed orders.");
    }

    if (receiptExistsForOrder(receipts, orderIndex)) {
        throw RepositoryException("A receipt for this order already exists.");
    }

    Receipt receipt;
    receipt.generateReceipt(order, orderIndex);
    receipts.push_back(receipt);
    std::cout << receipt.getReceiptText();
    return true;
}

double StudioManager::generateDailyReport() {
    report.generateDailyReport();
    report.showCompletedOrders(repository.toVector());
    double revenue = report.calculateDailyRevenue(receipts);
    return revenue;
}

std::vector<Order> StudioManager::getAllOrders() const {
    return repository.toVector();
}

Order* StudioManager::getOrder(int index) {
    return repository.tryGet(index);
}

const Order* StudioManager::getOrder(int index) const {
    return repository.tryGet(index);
}

double StudioManager::calculateTotalRevenue() const {
    return report.calculateDailyRevenue(receipts);
}

