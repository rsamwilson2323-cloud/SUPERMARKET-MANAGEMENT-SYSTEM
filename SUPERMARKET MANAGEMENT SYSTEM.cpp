#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

class Product {
public:
    int id;
    string name;
    string category;
    int quantity;
    int purchased;
    int sold;
    int returned;
    double rate;

    Product() {
        id = 0;
        quantity = 0;
        purchased = 0;
        sold = 0;
        returned = 0;
        rate = 0;
    }

    void input() {
        cout << "Enter Product ID: ";
        cin >> id;
        cin.ignore(1000, '\n');

        cout << "Enter Product Name: ";
        getline(cin, name);

        cout << "Enter Category: ";
        getline(cin, category);

        cout << "Enter Quantity: ";
        cin >> quantity;

        cout << "Enter Rate: ";
        cin >> rate;

        purchased = quantity;
        sold = 0;
        returned = 0;
    }

    void display() {
        cout << "\n====================================";
        cout << "\nProduct ID : " << id;
        cout << "\nName       : " << name;
        cout << "\nCategory   : " << category;
        cout << "\nStock      : " << quantity;
        cout << "\nPurchased  : " << purchased;
        cout << "\nSold       : " << sold;
        cout << "\nReturned   : " << returned;
        cout << "\nRate       : Rs. " << fixed << setprecision(2) << rate;
        cout << "\n====================================\n";
    }

    string saveFormat() {
        stringstream ss;

        ss << id << "|"
           << name << "|"
           << category << "|"
           << quantity << "|"
           << purchased << "|"
           << sold << "|"
           << returned << "|"
           << rate;

        return ss.str();
    }

    static Product loadFormat(string line) {
        Product p;

        string temp;
        stringstream ss(line);

        getline(ss, temp, '|');
        p.id = atoi(temp.c_str());

        getline(ss, p.name, '|');
        getline(ss, p.category, '|');

        getline(ss, temp, '|');
        p.quantity = atoi(temp.c_str());

        getline(ss, temp, '|');
        p.purchased = atoi(temp.c_str());

        getline(ss, temp, '|');
        p.sold = atoi(temp.c_str());

        getline(ss, temp, '|');
        p.returned = atoi(temp.c_str());

        getline(ss, temp, '|');
        p.rate = atof(temp.c_str());

        return p;
    }
};

class Supermarket {
    vector<Product> products;

public:

    void load() {
        products.clear();

        ifstream file("data.txt");

        string line;

        while (getline(file, line)) {
            if (!line.empty()) {
                products.push_back(Product::loadFormat(line));
            }
        }

        file.close();
    }

    void save() {
        ofstream file("data.txt");

        for (int i = 0; i < products.size(); i++) {
            file << products[i].saveFormat() << endl;
        }

        file.close();
    }

    void addProduct() {
        Product p;

        p.input();

        for (int i = 0; i < products.size(); i++) {
            if (products[i].id == p.id) {
                cout << "\nProduct ID already exists!\n";
                return;
            }
        }

        products.push_back(p);

        save();

        cout << "\nProduct Added Successfully!\n";
    }

    void showProducts() {
        if (products.empty()) {
            cout << "\nNo Products Available!\n";
            return;
        }

        cout << "\n========== ALL PRODUCTS ==========\n";

        for (int i = 0; i < products.size(); i++) {
            products[i].display();
        }
    }

    int searchMenu() {
        cout << "\n========== SEARCH PRODUCT ==========\n";
        cout << "1. Search By ID\n";
        cout << "2. Search By Name\n";
        cout << "3. Search By Category\n";
        cout << "Enter Choice: ";

        int choice;

        cin >> choice;
        cin.ignore(1000, '\n');

        return choice;
    }

    int searchProduct() {
        int option = searchMenu();

        if (option == 1) {
            int id;

            cout << "Enter Product ID: ";
            cin >> id;

            for (int i = 0; i < products.size(); i++) {
                if (products[i].id == id) {
                    return i;
                }
            }
        }

        else if (option == 2) {
            string name;

            cout << "Enter Product Name: ";
            getline(cin, name);

            for (int i = 0; i < products.size(); i++) {
                if (products[i].name == name) {
                    return i;
                }
            }
        }

        else if (option == 3) {
            string category;

            cout << "Enter Category: ";
            getline(cin, category);

            for (int i = 0; i < products.size(); i++) {
                if (products[i].category == category) {
                    return i;
                }
            }
        }

        return -1;
    }

    void searchProductDisplay() {
        int index = searchProduct();

        if (index == -1) {
            cout << "\nProduct Not Found!\n";
        }
        else {
            products[index].display();
        }
    }

    void addStock() {
        int index = searchProduct();

        if (index == -1) {
            cout << "\nProduct Not Found!\n";
            return;
        }

        int qty;

        cout << "Enter Quantity to Add: ";
        cin >> qty;

        if (qty <= 0) {
            cout << "\nInvalid Quantity!\n";
            return;
        }

        products[index].quantity += qty;
        products[index].purchased += qty;

        save();

        cout << "\nStock Added Successfully!\n";
        cout << "Current Stock: "
             << products[index].quantity << endl;
    }

    void sales() {
        double total = 0;
        char choice;

        cout << "\n====================================\n";
        cout << "             SALES BILL\n";
        cout << "====================================\n";

        do {
            int index = searchProduct();

            if (index == -1) {
                cout << "\nProduct Not Found!\n";
            }
            else {
                int qty;

                cout << "Enter Quantity: ";
                cin >> qty;

                if (qty <= 0) {
                    cout << "\nInvalid Quantity!\n";
                }

                else if (qty > products[index].quantity) {
                    cout << "\nNot Enough Stock!\n";
                    cout << "Available Stock: "
                         << products[index].quantity << endl;
                }

                else {
                    products[index].quantity -= qty;
                    products[index].sold += qty;

                    double amount =
                        qty * products[index].rate;

                    total += amount;

                    cout << "\nProduct : "
                         << products[index].name;

                    cout << "\nQuantity: "
                         << qty;

                    cout << "\nRate    : Rs. "
                         << fixed << setprecision(2)
                         << products[index].rate;

                    cout << "\nAmount  : Rs. "
                         << fixed << setprecision(2)
                         << amount << endl;
                }
            }

            cout << "\nAdd More Products? (y/n): ";
            cin >> choice;

        } while (choice == 'y' || choice == 'Y');

        cout << "\n====================================";
        cout << "\nTOTAL BILL = Rs. "
             << fixed << setprecision(2)
             << total;
        cout << "\n====================================\n";

        save();
    }

    void returnProduct() {
        int index = searchProduct();

        if (index == -1) {
            cout << "\nProduct Not Found!\n";
            return;
        }

        int qty;

        cout << "Enter Quantity to Return: ";
        cin >> qty;

        if (qty <= 0) {
            cout << "\nInvalid Quantity!\n";
            return;
        }

        if (qty > products[index].sold) {
            cout << "\nCannot return more than sold quantity!\n";
            return;
        }

        products[index].quantity += qty;
        products[index].sold -= qty;
        products[index].returned += qty;

        save();

        cout << "\nProduct Returned Successfully!\n";

        cout << "Current Stock: "
             << products[index].quantity << endl;
    }

    void lowStock() {
        int limit;

        cout << "\nEnter Low Stock Limit: ";
        cin >> limit;

        bool found = false;

        cout << "\n========== LOW STOCK PRODUCTS ==========\n";

        for (int i = 0; i < products.size(); i++) {
            if (products[i].quantity <= limit) {
                products[i].display();
                found = true;
            }
        }

        if (!found) {
            cout << "\nNo Low Stock Products!\n";
        }
    }

    void salesReport() {
        if (products.empty()) {
            cout << "\nNo Products Available!\n";
            return;
        }

        int totalSold = 0;
        double totalRevenue = 0;

        cout << "\n====================================\n";
        cout << "           SALES REPORT\n";
        cout << "====================================\n";

        for (int i = 0; i < products.size(); i++) {
            int soldQty = products[i].sold;

            double revenue =
                soldQty * products[i].rate;

            totalSold += soldQty;
            totalRevenue += revenue;

            cout << "\nProduct : "
                 << products[i].name;

            cout << "\nSold    : "
                 << soldQty;

            cout << "\nRevenue : Rs. "
                 << fixed << setprecision(2)
                 << revenue;

            cout << "\n------------------------------------\n";
        }

        cout << "\nTotal Items Sold : "
             << totalSold;

        cout << "\nTotal Revenue    : Rs. "
             << fixed << setprecision(2)
             << totalRevenue;

        cout << "\n====================================\n";
    }

    void inventoryValue() {
        double totalValue = 0;

        for (int i = 0; i < products.size(); i++) {
            totalValue +=
                products[i].quantity *
                products[i].rate;
        }

        cout << "\n====================================\n";

        cout << "Current Inventory Value: Rs. "
             << fixed << setprecision(2)
             << totalValue;

        cout << "\n====================================\n";
    }

    void menu() {
        load();

        int choice;

        do {
            cout << "\n";
            cout << "========================================\n";
            cout << "      SUPERMARKET MANAGEMENT SYSTEM\n";
            cout << "========================================\n";
            cout << "1. Add Product\n";
            cout << "2. Show All Products\n";
            cout << "3. Search Product\n";
            cout << "4. Add Stock\n";
            cout << "5. Sales / Billing\n";
            cout << "6. Return Product\n";
            cout << "7. Low Stock Products\n";
            cout << "8. Sales Report\n";
            cout << "9. Inventory Value\n";
            cout << "10. Exit\n";
            cout << "========================================\n";
            cout << "Enter Choice: ";

            cin >> choice;

            switch (choice) {

                case 1:
                    addProduct();
                    break;

                case 2:
                    showProducts();
                    break;

                case 3:
                    searchProductDisplay();
                    break;

                case 4:
                    addStock();
                    break;

                case 5:
                    sales();
                    break;

                case 6:
                    returnProduct();
                    break;

                case 7:
                    lowStock();
                    break;

                case 8:
                    salesReport();
                    break;

                case 9:
                    inventoryValue();
                    break;

                case 10:
                    cout << "\nThank You!\n";
                    break;

                default:
                    cout << "\nInvalid Choice!\n";
            }

        } while (choice != 10);
    }
};

int main() {
    Supermarket market;

    market.menu();

    return 0;
}