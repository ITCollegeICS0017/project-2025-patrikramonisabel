#include "ConsoleUI.h"
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
    std::string customerName, photos, orderType;
    char isExpressChoice;
    
    std::cout << "\n--- Create New Order ---\n";
    std::cout << "Customer Name: ";
    std::cin.ignore();
    std::getline(std::cin, customerName);
    
    std::cout << "Photos Description: ";
    std::getline(std::cin, photos);
    
    std::cout << "Order Type (e.g., Wedding, Portrait, Event): ";
    std::getline(std::cin, orderType);
    
    std::cout << "Express Order? (y/n): ";
    std::cin >> isExpressChoice;
    
    bool isExpress = (isExpressChoice == 'y' || isExpressChoice == 'Y');
    
    if (studioManager.createNewOrder(customerName, photos, orderType, isExpress)) {
        std::cout << "\n✓ Order created successfully for " << customerName;
        if (isExpress) {
            std::cout << " (EXPRESS)";
        }
        std::cout << std::endl;
    } else {
        std::cout << "\n✗ Failed to create order.\n";
    }
    
    pauseScreen();
}

void ConsoleUI::handleProcessOrder() {
    int orderIndex;
    
    std::cout << "\n--- Process Order ---\n";
    handleViewAllOrders();
    std::cout << "\nEnter order number to process: ";
    std::cin >> orderIndex;
    
    if (studioManager.processOrder(orderIndex)) {
        std::cout << "\n✓ Order #" << orderIndex << " is now being processed by photographer.\n";
    } else {
        std::cout << "\n✗ Failed to process order. Invalid order number.\n";
    }
    
    pauseScreen();
}

void ConsoleUI::handleCompleteOrder() {
    int orderIndex;
    
    std::cout << "\n--- Complete Order ---\n";
    handleViewAllOrders();
    std::cout << "\nEnter order number to complete: ";
    std::cin >> orderIndex;
    
    if (studioManager.completeOrder(orderIndex)) {
        std::cout << "\n✓ Order #" << orderIndex << " has been completed!\n";
    } else {
        std::cout << "\n✗ Failed to complete order. Invalid order number.\n";
    }
    
    pauseScreen();
}

void ConsoleUI::handleGenerateReceipt() {
    int orderIndex;
    
    std::cout << "\n--- Generate Receipt ---\n";
    handleViewAllOrders();
    std::cout << "\nEnter order number for receipt: ";
    std::cin >> orderIndex;
    
    std::cout << "\n";
    if (studioManager.generateReceipt(orderIndex)) {
        std::cout << "\n✓ Receipt generated successfully.\n";
    } else {
        std::cout << "\n✗ Failed to generate receipt. Invalid order number.\n";
    }
    
    pauseScreen();
}

void ConsoleUI::handleViewAllOrders() {
    std::vector<Order> orders = studioManager.getAllOrders();
    
    if (orders.empty()) {
        std::cout << "\nNo orders in the system.\n";
        return;
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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void ConsoleUI::run() {
    int choice;
    bool running = true;
    
    while (running) {
        clearScreen();
        displayMenu();
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid input. Please enter a number.\n";
            pauseScreen();
            continue;
        }
        
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
                handleViewAllOrders();
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
    }
}

