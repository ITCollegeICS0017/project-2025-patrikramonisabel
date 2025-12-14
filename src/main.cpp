#include <iostream>
#include "ConsoleUI.h"
#include "entities/StudioManager.h"
#include "repository/OrderRepository.h"
#include "StudioExceptions.h"

int main() {
    std::cout << "Initializing Photo Studio Management System...\n";

    OrderRepository repository("data/orders.csv");
    repository.loadAll();
    
    // Create the business logic layer
    StudioManager studioManager(repository);
    
    // Create the presentation layer
    ConsoleUI ui(studioManager);
    
    // Run the application
    ui.run();

    try {
        repository.saveAll();
    } catch (const StudioException& ex) {
        std::cerr << "Warning: Unable to save data to disk: " << ex.what() << '\n';
    }

    return 0;
}