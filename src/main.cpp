#include <iostream>
#include "entities/Order.h"
#include "entities/Receipt.h"
#include "entities/Photographer.h"
#include "entities/Receptionist.h"
#include "entities/Report.h"

int main() {
    std::cout << "Photo Studio Management System" << std::endl;
    Order order;
    order.storeOrderDetails("Alice", "wedding_photos.zip", "Wedding");
    order.setExpress(true);
    std::cout << "Order for " << order.getCustomerName() << " with status: " << order.getStatus() << std::endl;
    return 0;
}