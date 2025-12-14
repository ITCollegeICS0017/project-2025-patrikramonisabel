#pragma once

#include "entities/Order.h"
#include <cstddef>
#include <string>
#include <vector>

class OrderRepository {
public:
    explicit OrderRepository(std::string storagePath);
    ~OrderRepository();

    OrderRepository(const OrderRepository&) = delete;
    OrderRepository& operator=(const OrderRepository&) = delete;

    void loadAll();
    void saveAll() const;

    void add(const Order& order);
    bool empty() const;
    std::size_t size() const;
    std::vector<Order> toVector() const;

    Order* tryGet(int index);
    const Order* tryGet(int index) const;

private:
    Order* data;
    std::size_t count;
    std::size_t capacity;
    std::string filePath;

    void ensureCapacity(std::size_t desiredCapacity = 0);
    bool parseLine(const std::string& line, Order& parsedOrder) const;
    std::string toLine(const Order& order) const;
};


