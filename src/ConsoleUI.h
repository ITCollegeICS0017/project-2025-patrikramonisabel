#pragma once
#include "entities/StudioManager.h"
#include <string>

class ConsoleUI {
private:
    StudioManager& studioManager;
    
    void displayMenu();
    void handleCreateOrder();
    void handleProcessOrder();
    void handleCompleteOrder();
    void handleGenerateReceipt();
    bool handleViewAllOrders();
    void handleGenerateDailyReport();
    void clearScreen();
    void pauseScreen();
    
    std::string readLine(const std::string& prompt);
    std::string promptCustomerName();
    std::string promptPhotosDescription();
    std::string promptOrderType();
    bool promptYesNo(const std::string& question);
    int promptOrderIndex(const std::string& actionLabel);
    
    static std::string trim(const std::string& value);
    static std::string toLower(std::string value);

public:
    explicit ConsoleUI(StudioManager& manager);
    void run();
};

