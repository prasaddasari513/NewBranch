#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Structure for Menu Item
struct MenuItem {
    string name;
    double price;
    MenuItem* next;

    MenuItem(string itemName, double itemPrice) : name(itemName), price(itemPrice), next(nullptr) {}
};

// Structure for Order
struct Order {
    int orderID;
    string customerName;
    vector<MenuItem*> items; // Vector of MenuItem pointers for items ordered
    Order* next;

    Order(int id, string custName) : orderID(id), customerName(custName), next(nullptr) {}
};

// Structure for Table
struct Table {
    int tableID;
    string status; // "Available" or "Occupied"

    Table(int id, string stat) : tableID(id), status(stat) {}
};

// Head of the linked list of menu items
MenuItem* menuHead = nullptr;

// Function to add a menu item
void addMenuItem(string name, double price) {
    MenuItem* newItem = new MenuItem(name, price);
    if (menuHead == nullptr) {
        menuHead = newItem;
    } else {
        MenuItem* temp = menuHead;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newItem;
    }
}

// Queue of orders (FIFO)
Order* orderHead = nullptr;
Order* orderTail = nullptr;
int orderCount = 1;

// Function to place an order
void placeOrder(string customerName, const vector<MenuItem*>& items) {
    Order* newOrder = new Order(orderCount++, customerName);
    newOrder->items = items;
    if (orderHead == nullptr) {
        orderHead = orderTail = newOrder;
    } else {
        orderTail->next = newOrder;
        orderTail = newOrder;
    }
}

// Function to serve orders
void serveOrders() {
    Order* currentOrder = orderHead;
    while (currentOrder != nullptr) {
        cout << "Serving order for " << currentOrder->customerName << endl;
        cout << "Order ID: " << currentOrder->orderID << endl;
        cout << "Items ordered:" << endl;
        double total = 0;
        for (MenuItem* item : currentOrder->items) {
            cout << "- " << item->name << " ($" << item->price << ")" << endl;
            total += item->price;
        }
        cout << "Total bill: $" << total << endl;
        cout << "Allocating a table for the customer." << endl;
        currentOrder = currentOrder->next;
    }
}
// Function to allocate a table
void allocateTable(Table& table) {
    if (table.status == "Available") {
        table.status = "Occupied";
        cout << "Table " << table.tableID << " allocated." << endl;
    } else {
        cout << "Table " << table.tableID << " is already occupied." << endl;
    }
}
// Main function to demonstrate usage
int main() {
    // Add some menu items
    addMenuItem("Burger", 10.99);
    addMenuItem("Fries", 4.99);
    addMenuItem("Salad", 7.99);

    // Place some orders
    vector<MenuItem*> items1 = {menuHead, menuHead->next}; // Burger, Fries
    vector<MenuItem*> items2 = {menuHead, menuHead->next->next}; // Burger, Salad
    vector<MenuItem*> items3 = {menuHead->next, menuHead->next->next}; // Fries, Salad
    placeOrder("John", items1);
    placeOrder("Jane", items2);
    placeOrder("Bob", items3);
    // Serve orders
    serveOrders();
    return 0;
}

