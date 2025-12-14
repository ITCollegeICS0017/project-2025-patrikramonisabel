#include "repository/OrderRepository.h"

#include "StudioExceptions.h"
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace {
    constexpr char kDelimiter = ';';

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

    std::vector<std::string> split(const std::string& line, char delimiter) {
        std::vector<std::string> parts;
        std::string current;
        std::istringstream stream(line);
        while (std::getline(stream, current, delimiter)) {
            parts.push_back(current);
        }
        return parts;
    }

    OrderStatus statusFromString(const std::string& value, bool& ok) {
        const std::string lowered = [&]() {
            std::string tmp = value;
            std::transform(
                tmp.begin(),
                tmp.end(),
                tmp.begin(),
                [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); }
            );
            return tmp;
        }();

        if (lowered == "pending") {
            ok = true;
            return OrderStatus::PENDING;
        }
        if (lowered == "processing") {
            ok = true;
            return OrderStatus::PROCESSING;
        }
        if (lowered == "in_progress" || lowered == "in progress" || lowered == "inprogress") {
            ok = true;
            return OrderStatus::IN_PROGRESS;
        }
        if (lowered == "completed") {
            ok = true;
            return OrderStatus::COMPLETED;
        }

        ok = false;
        return OrderStatus::PENDING;
    }

    std::string statusToString(OrderStatus status) {
        switch (status) {
            case OrderStatus::PENDING:
                return "PENDING";
            case OrderStatus::PROCESSING:
                return "PROCESSING";
            case OrderStatus::IN_PROGRESS:
                return "IN_PROGRESS";
            case OrderStatus::COMPLETED:
                return "COMPLETED";
            default:
                return "UNKNOWN";
        }
    }

    bool expressFromString(const std::string& value, bool& ok) {
        const std::string lowered = [&]() {
            std::string tmp = value;
            std::transform(
                tmp.begin(),
                tmp.end(),
                tmp.begin(),
                [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); }
            );
            return tmp;
        }();

        if (lowered == "y" || lowered == "yes" || lowered == "true" || lowered == "1") {
            ok = true;
            return true;
        }
        if (lowered == "n" || lowered == "no" || lowered == "false" || lowered == "0") {
            ok = true;
            return false;
        }

        ok = false;
        return false;
    }

    std::string boolToString(bool value) {
        return value ? "Y" : "N";
    }
}

OrderRepository::OrderRepository(std::string storagePath)
    : data(nullptr),
      count(0),
      capacity(0),
      filePath(std::move(storagePath)) {
    ensureCapacity(4);
}

OrderRepository::~OrderRepository() {
    delete[] data;
}

void OrderRepository::loadAll() {
    count = 0;

    std::ifstream input(filePath);
    if (!input.is_open()) {
        // Missing file is acceptable; repository remains empty.
        return;
    }

    std::string line;
    while (std::getline(input, line)) {
        line = trimCopy(line);
        if (line.empty()) {
            continue;
        }

        Order parsedOrder;
        if (!parseLine(line, parsedOrder)) {
            continue;
        }

        add(parsedOrder);
    }
}

void OrderRepository::saveAll() const {
    const std::filesystem::path targetPath(filePath);
    try {
        if (!targetPath.parent_path().empty()) {
            std::filesystem::create_directories(targetPath.parent_path());
        }
    } catch (const std::filesystem::filesystem_error& err) {
        throw RepositoryException("Unable to prepare storage directory: " + std::string(err.what()));
    }

    std::ofstream output(filePath, std::ios::trunc);
    if (!output.is_open()) {
        throw RepositoryException("Unable to open storage file for writing.");
    }

    for (std::size_t i = 0; i < count; ++i) {
        output << toLine(data[i]) << '\n';
    }
}

void OrderRepository::add(const Order& order) {
    ensureCapacity(count + 1);
    data[count] = order;
    ++count;
}

bool OrderRepository::empty() const {
    return count == 0;
}

std::size_t OrderRepository::size() const {
    return count;
}

std::vector<Order> OrderRepository::toVector() const {
    std::vector<Order> snapshot;
    snapshot.reserve(count);
    for (std::size_t i = 0; i < count; ++i) {
        snapshot.push_back(data[i]);
    }
    return snapshot;
}

Order* OrderRepository::tryGet(int index) {
    if (index < 0 || index >= static_cast<int>(count)) {
        return nullptr;
    }
    return &data[index];
}

const Order* OrderRepository::tryGet(int index) const {
    if (index < 0 || index >= static_cast<int>(count)) {
        return nullptr;
    }
    return &data[index];
}

void OrderRepository::ensureCapacity(std::size_t desiredCapacity) {
    if (desiredCapacity == 0) {
        desiredCapacity = capacity == 0 ? 4 : capacity;
    }

    if (desiredCapacity <= capacity) {
        return;
    }

    std::size_t newCapacity = std::max(desiredCapacity, capacity == 0 ? std::size_t(4) : capacity * 2);
    Order* newData = new Order[newCapacity];
    for (std::size_t i = 0; i < count; ++i) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

bool OrderRepository::parseLine(const std::string& line, Order& parsedOrder) const {
    auto segments = split(line, kDelimiter);
    if (segments.size() != 5) {
        return false;
    }

    for (auto& segment : segments) {
        segment = trimCopy(segment);
    }

    bool statusOk = false;
    const OrderStatus status = statusFromString(segments[3], statusOk);
    if (!statusOk) {
        return false;
    }

    bool expressOk = false;
    const bool isExpress = expressFromString(segments[4], expressOk);
    if (!expressOk) {
        return false;
    }

    parsedOrder.storeOrderDetails(segments[0], segments[1], segments[2]);
    parsedOrder.setExpress(isExpress);
    parsedOrder.trackOrderStatus(status);

    return true;
}

std::string OrderRepository::toLine(const Order& order) const {
    std::ostringstream builder;
    builder << order.getCustomerName() << kDelimiter
            << order.getPhotosDescription() << kDelimiter
            << order.getOrderType() << kDelimiter
            << statusToString(order.getStatus()) << kDelimiter
            << boolToString(order.getIsExpress());
    return builder.str();
}

