# 🛒 Supermarket Management System

A simple and efficient **console-based Supermarket Management System** developed in **C++**. The application helps manage supermarket products, inventory, sales, returns, stock levels, billing, and sales reports through an easy-to-use menu-driven interface.

The system uses a local **`data.txt`** file for persistent data storage, so product information remains available even after the program is closed.

---

## 🚀 Features

* 🛍️ Add new products
* 📦 View all available products
* 🔎 Search products by:

  * Product ID
  * Product Name
  * Category
* ➕ Add additional stock
* 🧾 Generate sales bills
* 🔄 Process product returns
* ⚠️ Detect low-stock products
* 📊 Generate sales reports
* 💰 Calculate total inventory value
* 💾 Automatically save product data
* 🔁 Load saved data when the application starts
* 🖥️ Simple menu-driven console interface
* ⚡ Lightweight and requires no database

---

## 🛠️ Technologies Used

* **C++**
* **Object-Oriented Programming (OOP)**
* **STL Vector**
* **File Handling**
* **String Processing**
* **Console I/O**
* **Local Text File Storage**

---

## 📂 Project Structure

```text
SUPERMARKET-MANAGEMENT-SYSTEM/
│
├── SUPERMARKET MANAGEMENT SYSTEM.cpp
├── SUPERMARKET MANAGEMENT SYSTEM.exe
├── data.txt
└── README.md
```

> `data.txt` is automatically used by the application to store product information.

---

## ⚙️ Product Information

Each product maintains the following information:

| Field        | Description                    |
| ------------ | ------------------------------ |
| Product ID   | Unique identification number   |
| Product Name | Name of the product            |
| Category     | Product category               |
| Stock        | Current available quantity     |
| Purchased    | Total quantity purchased/added |
| Sold         | Total quantity sold            |
| Returned     | Total quantity returned        |
| Rate         | Price per unit                 |

The product structure and these fields are implemented in the `Product` class.

---

## 📋 Main Menu

When the program starts, the following menu is displayed:

```text
========================================
      SUPERMARKET MANAGEMENT SYSTEM
========================================
1. Add Product
2. Show All Products
3. Search Product
4. Add Stock
5. Sales / Billing
6. Return Product
7. Low Stock Products
8. Sales Report
9. Inventory Value
10. Exit
========================================
Enter Choice:
```

The complete menu and corresponding operations are implemented in the `Supermarket` class.

---

# 📦 Core Modules

## 1️⃣ Add Product

Allows the user to create a new product by entering:

* Product ID
* Product Name
* Category
* Quantity
* Rate

The system automatically initializes:

```text
Purchased = Initial Quantity
Sold      = 0
Returned  = 0
```

## It also checks whether the entered Product ID already exists before adding the product.

## 2️⃣ Show All Products

Displays all products currently stored in the supermarket inventory.

Example:

```text
====================================
Product ID : 101
Name       : Rice
Category   : Grocery
Stock      : 50
Purchased  : 50
Sold       : 10
Returned   : 0
Rate       : Rs. 60.00
====================================
```

The system displays product ID, name, category, stock, purchase quantity, sold quantity, returned quantity, and rate.

---

## 3️⃣ Search Product

Products can be searched using three different methods:

```text
========== SEARCH PRODUCT ==========
1. Search By ID
2. Search By Name
3. Search By Category
```

## The search system returns the matching product and displays its complete details.

## 4️⃣ Add Stock

Additional stock can be added to an existing product.

The application:

1. Searches for the product.
2. Requests the quantity to add.
3. Validates the quantity.
4. Updates the current stock.
5. Updates the total purchased quantity.
6. Saves the changes to `data.txt`.

```text
Current Stock = Current Stock + Added Quantity
Purchased     = Purchased + Added Quantity
```

---

## 5️⃣ Sales / Billing

The sales module provides a simple billing system.

During a sale, the application:

* Searches for a product.
* Requests the quantity.
* Checks available stock.
* Reduces inventory.
* Updates the sold quantity.
* Calculates the product amount.
* Adds the amount to the total bill.

Example:

```text
====================================
             SALES BILL
====================================

Product : Rice
Quantity: 2
Rate    : Rs. 60.00
Amount  : Rs. 120.00

====================================
TOTAL BILL = Rs. 120.00
====================================
```

The application also allows multiple products to be added to the same bill.

---

## 6️⃣ Return Product

The return module allows previously sold products to be returned.

The system validates that the returned quantity does not exceed the quantity sold.

When a product is returned:

```text
Stock    += Returned Quantity
Sold     -= Returned Quantity
Returned += Returned Quantity
```

---

## 7️⃣ Low Stock Products

The application can identify products whose stock is below a user-defined limit.

Example:

```text
Enter Low Stock Limit: 10

========== LOW STOCK PRODUCTS ==========
```

Every product with stock less than or equal to the specified limit is displayed.

---

## 8️⃣ Sales Report

The sales report provides information about:

* Product name
* Quantity sold
* Revenue generated
* Total items sold
* Total revenue

Example:

```text
====================================
           SALES REPORT
====================================

Product : Rice
Sold    : 25
Revenue : Rs. 1500.00

------------------------------------

Total Items Sold : 25
Total Revenue    : Rs. 1500.00
====================================
```

Revenue is calculated using:

```text
Revenue = Sold Quantity × Product Rate
```

---

## 9️⃣ Inventory Value

The system calculates the current monetary value of all available stock.

Formula:

```text
Inventory Value =
Σ (Current Stock × Product Rate)
```

The calculated value is displayed in Indian Rupees.

---

# 💾 Data Storage

The application uses a simple **`data.txt`** file instead of a database.

Each product is stored using the following format:

```text
ID|Name|Category|Quantity|Purchased|Sold|Returned|Rate
```

Example:

```text
101|Rice|Grocery|50|60|10|0|60
102|Milk|Dairy|20|30|10|2|45
```

The application automatically loads product information from `data.txt` when it starts and saves updated information after inventory changes.

---

# 🔄 Data Flow

```text
             ┌─────────────────┐
             │   Application   │
             └────────┬────────┘
                      │
              Load existing data
                      │
                      ▼
             ┌─────────────────┐
             │    data.txt     │
             └────────┬────────┘
                      │
                      ▼
             ┌─────────────────┐
             │ Product Vector  │
             └────────┬────────┘
                      │
          ┌───────────┼───────────┐
          ▼           ▼           ▼
       Products      Sales      Returns
          │           │           │
          └───────────┼───────────┘
                      ▼
                 Save Changes
                      │
                      ▼
                 data.txt
```

---

# 🧱 Object-Oriented Design

The project uses two main classes:

### `Product`

Responsible for storing and managing individual product information.

```cpp
class Product
```

It contains product properties such as:

```cpp
int id;
string name;
string category;
int quantity;
int purchased;
int sold;
int returned;
double rate;
```

It also provides functions for input, display, saving, and loading product data.

### `Supermarket`

Responsible for managing the complete inventory and supermarket operations.

```cpp
class Supermarket
```

It maintains a vector of products and provides functionality for:

* Loading data
* Saving data
* Adding products
* Searching
* Stock management
* Sales
* Returns
* Low-stock detection
* Sales reports
* Inventory valuation

---

# ▶️ How to Run

## Option 1 — Run the EXE

If you already have the compiled executable:

```text
SUPERMARKET MANAGEMENT SYSTEM.exe
```

Simply double-click the executable.

### Important

Keep `data.txt` in the same directory as the executable so that the application can load and save product information correctly.

---

## Option 2 — Compile from Source

Make sure a C++ compiler such as **g++ / MinGW** is installed.

Compile:

```bash
g++ "SUPERMARKET MANAGEMENT SYSTEM.cpp" -o "SUPERMARKET MANAGEMENT SYSTEM.exe"
```

Then run:

```bash
"SUPERMARKET MANAGEMENT SYSTEM.exe"
```

---

# 🖥️ System Requirements

* Windows / any system supporting a standard C++ compiler
* C++ compiler supporting modern standard C++
* Terminal / Command Prompt
* No database required
* No internet connection required

---

# 📊 Example Workflow

A typical supermarket workflow can be:

```text
1. Add Product
       ↓
2. Add Stock
       ↓
3. Search / View Products
       ↓
4. Sell Products
       ↓
5. Generate Sales Report
       ↓
6. Process Returns
       ↓
7. Check Low Stock
       ↓
8. Calculate Inventory Value
```

---

# 🔐 Data Persistence

The application automatically saves important inventory changes.

For example:

```text
Add Product      → Save
Add Stock        → Save
Sales            → Save
Return Product   → Save
```

This allows the inventory to persist between program executions.

---

# 🚀 Future Improvements

Possible future upgrades include:

* 🖥️ Graphical User Interface (GUI)
* 🔐 Admin login and authentication
* 👥 Multiple user roles
* 🧾 Printable invoices
* 📄 PDF bill generation
* 📊 Graphical sales analytics
* 📅 Date and time-based sales history
* 🔔 Automatic low-stock alerts
* 🗃️ Database integration with MySQL/SQLite
* 🧑‍💼 Customer management
* 💳 Payment management
* 🧾 GST/tax calculation
* 📦 Supplier management
* 📈 Profit and loss analysis
* 🔍 Advanced product filtering
* 📤 CSV/Excel export

---

# 🎯 Project Objectives

The main objectives of this project are:

* Automate basic supermarket inventory operations.
* Reduce manual stock management.
* Track product purchases, sales, and returns.
* Provide quick product searching.
* Generate basic sales and inventory reports.
* Demonstrate practical implementation of **C++ OOP and file handling**.

---

# 📚 Concepts Demonstrated

This project demonstrates several important C++ programming concepts:

* Classes and Objects
* Encapsulation
* Constructors
* Member Functions
* Static Functions
* STL `vector`
* File Input/Output
* String Streams
* String Manipulation
* Loops
* Conditional Statements
* Switch Statements
* Functions
* Searching
* Basic Inventory Algorithms
* Data Persistence

---

# 👨‍💻 Author

**Sam Wilson**

🔗 GitHub:
https://github.com/rsamwilson2323-cloud

💼 LinkedIn:
https://www.linkedin.com/in/sam-wilson-14b554385/

---

## ⭐ Support

If you found this project useful or interesting, consider giving the repository a ⭐ on GitHub!

---

## 📄 License

This project is available under the **MIT License**.

