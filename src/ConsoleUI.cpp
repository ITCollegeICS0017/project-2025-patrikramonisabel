#include "ConsoleUI.h"
#include "OrderRules.h"
#include "StudioExceptions.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>

ConsoleUI::ConsoleUI(StudioManager& manager) : studioManager(manager) {}

void ConsoleUI::displayMenu() {
    std::cout << "\n========================================\n";
    std::cout << "   PHOTO STUDIO MANAGEMENT SYSTEM\n";
    std::cout << "========================================\n";
    std::cout << "1. Create New Order\n";
    std::cout << "2. Process Order\n";
    std::cout << "3. Complete Order\n";
    std::cout << "4. Generate Receipt\n";
    std::cout << "5. View All Orders\n";
    std::cout << "6. Generate Daily Report\n";
    std::cout << "0. Exit\n";
    std::cout << "========================================\n";
    std::cout << "Enter your choice: ";
}

void ConsoleUI::handleCreateOrder() {
    std::cout << "\n--- Create New Order ---\n";
    try {
        const std::string customerName = promptCustomerName();
        const std::string photos = promptPhotosDescription();
        const std::string orderType = promptOrderType();
        const bool isExpress = promptYesNo("Express Order? (y/n): ");

        if (studioManager.createNewOrder(customerName, photos, orderType, isExpress)) {
            std::cout << "\n✓ Order created successfully for " << customerName;
            if (isExpress) {
                std::cout << " (EXPRESS)";
            }
            std::cout << std::endl;
        } else {
            std::cout << "\n✗ Failed to create order.\n";
        }
    } catch (const StudioException& ex) {
        std::cout << "\n✗ " << ex.what() << "\n";
    }

    pauseScreen();
}

void ConsoleUI::handleProcessOrder() {
    std::cout << "\n--- Process Order ---\n";
    if (!handleViewAllOrders()) {
        pauseScreen();
        return;
    }

    try {
        const int orderIndex = promptOrderIndex("Enter order number to process: ");
        if (studioManager.processOrder(orderIndex)) {
            std::cout << "\n✓ Order #" << orderIndex << " is now being processed by photographer.\n";
        } else {
            std::cout << "\n✗ Unable to process the selected order.\n";
        }
    } catch (const StudioException& ex) {
        std::cout << "\n✗ " << ex.what() << "\n";
    }

    pauseScreen();
}

void ConsoleUI::handleCompleteOrder() {
    std::cout << "\n--- Complete Order ---\n";
    if (!handleViewAllOrders()) {
        pauseScreen();
        return;
    }

    try {
        const int orderIndex = promptOrderIndex("Enter order number to complete: ");
        if (studioManager.completeOrder(orderIndex)) {
            std::cout << "\n✓ Order #" << orderIndex << " has been completed!\n";
        } else {
            std::cout << "\n✗ Unable to complete the selected order.\n";
        }
    } catch (const StudioException& ex) {
        std::cout << "\n✗ " << ex.what() << "\n";
    }

    pauseScreen();
}

void ConsoleUI::handleGenerateReceipt() {
    std::cout << "\n--- Generate Receipt ---\n";
    if (!handleViewAllOrders()) {
        pauseScreen();
        return;
    }

    try {
        const int orderIndex = promptOrderIndex("Enter order number for receipt: ");
        std::cout << "\n";
        if (studioManager.generateReceipt(orderIndex)) {
            std::cout << "\n✓ Receipt generated successfully.\n";
        } else {
            std::cout << "\n✗ Unable to generate receipt for the selected order.\n";
        }
    } catch (const StudioException& ex) {
        std::cout << "\n✗ " << ex.what() << "\n";
    }

    pauseScreen();
}

bool ConsoleUI::handleViewAllOrders() {
    std::vector<Order> orders = studioManager.getAllOrders();
    
    if (orders.empty()) {
        std::cout << "\nNo orders in the system.\n";
        return false;
    }
    
    std::cout << "\n--- All Orders ---\n";
    std::cout << "ID | Customer Name          | Status      | Express\n";
    std::cout << "---+------------------------+-------------+---------\n";
    
    for (size_t i = 0; i < orders.size(); ++i) {
        std::cout << i << "  | ";
        std::cout.width(22);
        std::cout << std::left << orders[i].getCustomerName() << " | ";
        std::cout.width(11);
        std::cout << std::left << orders[i].getStatusString() << " | ";
        std::cout << (orders[i].getIsExpress() ? "Yes" : "No") << "\n";
    }

    return true;
}

std::string ConsoleUI::readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    if (!std::getline(std::cin, input)) {
        std::cin.clear();
        throw InputValidationException("Unable to read input. Please try again.");
    }
    return input;
}

std::string ConsoleUI::promptCustomerName() {
    const std::string value = trim(readLine("Customer Name (2-100 letters): "));
    if (value.size() < 2 || value.size() > 100) {
        throw InputValidationException("Customer name must be between 2 and 100 letters.");
    }

    const bool hasOnlyLetters = std::all_of(
        value.begin(),
        value.end(),
        [](unsigned char ch) {
            return std::isalpha(ch) || std::isspace(ch) || ch == '-' || ch == '\'';
        }
    );

    if (!hasOnlyLetters) {
        throw InputValidationException("Customer name may contain letters, spaces, hyphens, or apostrophes.");
    }

    return value;
}

std::string ConsoleUI::promptPhotosDescription() {
    const std::string description = trim(readLine("Photos Description (10-500 chars): "));
    if (description.size() < 10 || description.size() > 500) {
        throw InputValidationException("Description must be between 10 and 500 characters.");
    }
    return description;
}

std::string ConsoleUI::promptOrderType() {
    const std::string rawType = trim(readLine("Order Type (Wedding, Portrait, Event, Product, Studio): "));
    const std::string lowered = toLower(rawType);

    for (const auto& allowed : order_rules::kAllowedOrderTypes) {
        if (lowered == toLower(std::string(allowed))) {
            return std::string(allowed);
        }
    }

    throw InputValidationException("Invalid order type. Choose from Wedding, Portrait, Event, Product, or Studio.");
}

bool ConsoleUI::promptYesNo(const std::string& question) {
    const std::string response = toLower(trim(readLine(question)));
    if (response == "y" || response == "yes") {
        return true;
    }
    if (response == "n" || response == "no") {
        return false;
    }

    throw InputValidationException("Please enter 'y' for yes or 'n' for no.");
}

int ConsoleUI::promptOrderIndex(const std::string& promptText) {
    const std::string rawInput = trim(readLine(promptText));
    if (rawInput.empty()) {
        throw InputValidationException("Order number is required.");
    }

    const bool numeric = std::all_of(
        rawInput.begin(),
        rawInput.end(),
        [](unsigned char ch) {
            return std::isdigit(ch);
        }
    );

    if (!numeric) {
        throw InputValidationException("Please enter a numeric order number.");
    }

    long long index = 0;
    try {
        index = std::stoll(rawInput);
    } catch (const std::exception&) {
        throw InputValidationException("Order number is too large.");
    }

    if (index < 0 || index > std::numeric_limits<int>::max()) {
        throw InputValidationException("Order number must be positive and within range.");
    }

    return static_cast<int>(index);
}

std::string ConsoleUI::trim(const std::string& value) {
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

std::string ConsoleUI::toLower(std::string value) {
    std::transform(
        value.begin(),
        value.end(),
        value.begin(),
        [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); }
    );
    return value;
}

void ConsoleUI::handleGenerateDailyReport() {
    std::cout << "\n--- Daily Report ---\n";
    double totalRevenue = studioManager.generateDailyReport();
    std::cout << "\nTotal Daily Revenue: $" << totalRevenue << "\n";
    
    pauseScreen();
}

void ConsoleUI::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void ConsoleUI::pauseScreen() {
    std::cout << "\nPress Enter to continue...";
    std::string placeholder;
    if (!std::getline(std::cin, placeholder)) {
        std::cin.clear();
    }
}

void ConsoleUI::run() {
    bool running = true;
    
    while (running) {
        clearScreen();
        displayMenu();
        std::string choiceInput;
        if (!std::getline(std::cin, choiceInput)) {
            std::cin.clear();
            continue;
        }

        choiceInput = trim(choiceInput);
        if (choiceInput.empty()) {
            std::cout << "\nPlease enter a menu option.\n";
            pauseScreen();
            continue;
        }

        try {
            const int choice = std::stoi(choiceInput);
            switch (choice) {
                case 1:
                    handleCreateOrder();
                    break;
                case 2:
                    handleProcessOrder();
                    break;
                case 3:
                    handleCompleteOrder();
                    break;
                case 4:
                    handleGenerateReceipt();
                    break;
                case 5:
                    clearScreen();
                    (void)handleViewAllOrders();
                    pauseScreen();
                    break;
                case 6:
                    handleGenerateDailyReport();
                    break;
                case 0:
                    std::cout << "\nThank you for using Photo Studio Management System!\n";
                    running = false;
                    break;
                default:
                    std::cout << "\nInvalid choice. Please try again.\n";
                    pauseScreen();
            }
        } catch (const std::exception&) {
            std::cout << "\nInvalid input. Please enter a number.\n";
            pauseScreen();
        }
    }
}

