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
    void handleViewAllOrders();
    void handleGenerateDailyReport();
    void clearScreen();
    void pauseScreen();

public:
    explicit ConsoleUI(StudioManager& manager);
    void run();
};

