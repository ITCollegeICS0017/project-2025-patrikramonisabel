# CRC Cards – Project Variant 3 - Photo Studio

## Class: Receptionist
**Responsibilities:**
- Take customer orders
- Create Order records  
- Set express order flag  
  **Collaborators:**
- Order

## Class: Photographer
**Responsibilities:**
- Process orders
- Develop photos/film  
- Mark orders as completed  
  **Collaborators:**
- Order

## Class: Order
**Responsibilities:**
- Store order details (customer name, photos, type of order)
- Calculate price (base price + 25% if express)    
- Track order status (pending, completed)  
- Track materials used  
  **Collaborators:**
- Receptionist  
- Photographer  
- Receipt  
- Report

## Class: Receipt
**Responsibilities:**
- Generate and print receipts for completed orders  
  **Collaborators:**
- Order

## Class: Report
**Responsibilities:**
- Generate daily reports  
- Show completed orders  
- Calculate daily revenue  
  **Collaborators:**
- Order  
- Receipt
