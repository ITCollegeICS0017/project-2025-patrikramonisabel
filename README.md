# Project Variant 3 - Photo Studio Management System

**Team members**: 
- Patrik Tamm (@patam2)
- Ramon Egert ()
- Isabel Zimmermann (@iszimm)

## Project Description

A photo studio needs a system to manage customer orders for photo printing and film developing. Currently, orders are handled manually, which can lead to confusion and lost paperwork. This project creates a digital management system where:

- Receptionists take customer orders
- Photographers process and complete orders
- System tracks materials used and order status
- Express orders cost 25% more
- Daily reports show completed work and revenue
- All data managed in one centralized system

## Features (Release 2)

✅ **Order Management**
- Create new orders with customer details
- Mark orders as express (25% price increase)
- Track order status (Pending → Processing → Completed)

✅ **Workflow Processing**
- Assign orders to photographers
- Process and complete orders
- Material/consumables tracking

✅ **Receipt Generation**
- Professional formatted receipts
- Automatic price calculation
- Customer information display

✅ **Daily Reports**
- List of completed orders
- Total revenue calculation
- Business analytics

✅ **Three-Tier Architecture**
- Presentation Layer (ConsoleUI)
- Business Logic Layer (StudioManager & Entities)
- Data Layer (In-memory storage)

## Build & Run

### Build from fresh clone:
```bash
cmake -S . -B build && cmake --build build
```

### Run the application:
**Windows:** `build/Debug/photo_studio.exe`  
**Linux/Mac:** `build/photo_studio`

### Quick start:
```bash
cd /Users/patriktamm/dev/ics0017/project-2025-patrikramonisabel
mkdir -p build && cd build
cmake ..
make
./photo_studio
```

## Usage

The system provides an interactive menu:

1. **Create New Order** - Add a new customer order
2. **Process Order** - Assign order to photographer
3. **Complete Order** - Mark order as completed
4. **Generate Receipt** - Create and display receipt
5. **View All Orders** - List all orders with status
6. **Generate Daily Report** - View completed orders and revenue
0. **Exit** - Close application

## Architecture

See `docs/release-2/Release2-DLD.md` for detailed design documentation.

**Key Components:**
- `ConsoleUI` - User interface layer
- `StudioManager` - Business logic coordinator
- `Order` - Order entity with price calculation
- `Photographer` - Photo processing workflow
- `Receipt` - Receipt generation
- `Report` - Business reporting
- `Receptionist` - Order intake management

### Mark a release tag
###  end of Release 1:
git tag release-1
git push origin release-1

###  end of Release 2:
git tag release-2
git push origin release-2

### Folders for documents
docs/release-1/  # slides, SRS/SDP updates, test report

docs/release-2/

docs/release-3/
