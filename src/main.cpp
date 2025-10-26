#include <iostream>
#include "entities/StudioManager.h"
#include "ConsoleUI.h"

int main() {
    std::cout << "Initializing Photo Studio Management System...\n";
    
    // Create the business logic layer
    StudioManager studioManager;
    
    // Create the presentation layer
    ConsoleUI ui(studioManager);
    
    // Run the application
    ui.run();
    
    return 0;
}