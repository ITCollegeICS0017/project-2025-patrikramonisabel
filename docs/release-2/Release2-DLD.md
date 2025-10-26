# Release 2 - Detailed Level Design

## Overview
This Detailed Level Design document describes the structure developed for the second release of our project. The system automates invoice generation, price customization depending on the urgency. The system generates forms for both the client and photographer. Additionally, the system tracks consumables usage.

## System Overview

### Architecture - Three-Tier Design

**Presentation Layer (UI):**
* `ConsoleUI` - Main user interface for forms and input
  * Menu-driven interface
  * Handles user input and displays output
  * Delegates all business logic to StudioManager

**Logic Layer (Business):**
* `StudioManager` - Main business logic coordinator
  * `Order` - Stores order details, calculates prices
  * `Photographer` - Manages photo processing workflow
  * `Receipt` - Generates formatted receipts
  * `Report` - Generates daily reports and revenue calculations
  * `Receptionist` - Manages order intake process

**Data Layer (Storage):**
* In-memory storage for Release 2 (vectors in StudioManager)
* No direct database access

### Design Principles
* UI never accesses repositories directly
* Data layer never prints to console
* Business logic layer returns values instead of void
* Proper separation of concerns across all three layers

## Class Details

### StudioManager
**Purpose:** Coordinates all business operations and manages data storage

**Key Methods:**
* `createNewOrder()` - Creates and stores new orders
* `processOrder()` - Assigns orders to photographer
* `completeOrder()` - Marks orders as completed
* `generateReceipt()` - Creates receipts for orders
* `generateDailyReport()` - Generates revenue reports
* `getAllOrders()` - Returns all orders
* `calculateTotalRevenue()` - Calculates total revenue

### ConsoleUI
**Purpose:** Handles all user interaction

**Features:**
* Interactive menu system
* Input validation
* Display formatting
* Error handling

### Order
**Purpose:** Stores order information and calculates prices

**Features:**
* Customer details
* Order type and status tracking
* Express order flag (25% price increase)
* Material usage tracking

### Photographer
**Purpose:** Manages photo processing workflow

**Features:**
* Maintains queue of current orders
* Processes pending orders
* Marks orders as completed
* Returns operation counts

### Receipt
**Purpose:** Generates formatted receipts

**Features:**
* Professional receipt formatting
* Price calculation
* Customer information display
* Express order indication

### Report
**Purpose:** Generates business reports

**Features:**
* Daily report generation
* Completed orders listing
* Revenue calculation

## Workflow

1. User creates order through ConsoleUI
2. StudioManager stores order and creates Order object
3. Order can be processed (assigned to Photographer)
4. Photographer updates order status
5. Order can be completed
6. Receipt can be generated for completed orders
7. Daily report shows all completed orders and revenue

## Implementation Status
✅ All core functionality implemented
✅ Three-tier architecture complete
✅ Design principles followed
✅ No linter errors
✅ Ready for testing 