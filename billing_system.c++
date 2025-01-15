#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Class definition for the bill
class Bill {
private:
    string item;    // Item name
    int price;      // Item price
    int quantity;   // Item quantity
public:
    // Default constructor
    Bill() : item(""), price(0), quantity(0) {}

    // Setters
    void setItem(const string& it) { item = it; }
    void setPrice(int pri) { price = pri; }
    void setQuantity(int qty) { quantity = qty; }

    // Getters
    string getItem() const { return item; }
    int getPrice() const { return price; }
    int getQuantity() const { return quantity; }
};

// Function to add items to the inventory
void addItem(Bill& b) {
    bool close = false;

    while (!close) {
        cout << "\n1. Add item to inventory\n";
        cout << "2. Back to main menu\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string itemName;
            int price, quantity;

            cout << "\nEnter the item name: ";
            cin >> ws; // Ignore leading whitespace
            getline(cin, itemName);
            cout << "Enter the price: ";
            cin >> price;
            cout << "Enter the quantity: ";
            cin >> quantity;

            b.setItem(itemName);
            b.setPrice(price);
            b.setQuantity(quantity);

            // Write the item details to the file
            ofstream ofs("bill.txt", ios::app);
            if (!ofs) {
                cout << "Error: Could not open the file.\n";
            } else {
                ofs << b.getItem() << ": " << b.getPrice() << ": " << b.getQuantity() << "\n";
                cout << "Item added successfully!\n";
            }
            ofs.close();
        } else if (choice == 2) {
            close = true;
            cout << "\nReturning to the main menu...\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Function to generate and print the bill
void printBill() {
    int total = 0;
    bool close = false;

    while (!close) {
        cout << "\n1. Add items to the bill\n";
        cout << "2. Calculate total and exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string itemName;
            int requestedQuantity;

            cout << "\nEnter the item name: ";
            cin >> ws;
            getline(cin, itemName);
            cout << "Enter the quantity: ";
            cin >> requestedQuantity;

            ifstream ifs("bill.txt");
            ofstream tempFile("bill_temp.txt", ios::app);
           // if (!ifs || !tempFile) {
             //   cout << "Error: Unable to open the file.\n";
          //      return;
         //   }

            string line;
            bool itemFound = false;

            while (getline(ifs, line)) {
                stringstream ss(line);
                string storedItemName;
                int price, availableQuantity;
                char delimiter;

                // Parse the line to extract item details
                getline(ss, storedItemName, ':');
                ss >> price >> delimiter >> availableQuantity;


                if (itemName == storedItemName) {
                    itemFound = true;

                    if (requestedQuantity <= availableQuantity) {
                        int amount = requestedQuantity * price;
                        cout << "\n\tItem\t| Quantity\t| Rate\t| Amount\n";
                        cout << "\t" << storedItemName << "\t| " << requestedQuantity
                             << "\t\t| " << price << "\t| " << amount << "\n";

                        // Deduct the requested quantity from the available stock
                        availableQuantity -= requestedQuantity;
                        total += amount;
                    } else {
                        cout << "Sorry! Not enough stock available for " << storedItemName << ".\n";
                    }

                    tempFile << storedItemName << ": " << price << ": " << availableQuantity << "\n";
                } else {
                    tempFile << line << "\n";
                }
            }

            if (!itemFound) {
                cout << "Item not found in inventory.\n";
            }

            ifs.close();
            tempFile.close();

            // Replace the original file with the updated file
            remove("bill.txt");
            rename("bill_temp.txt", "bill.txt");

        } else if (choice == 2) {
            cout << "\nCalculating your total bill...\n";
            cout << "Your total bill is: " << total << "\n";
            close = true;
            cout << "Thanks for shopping with us!\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Main function for the supermarket billing system
int main() {
    Bill b;
    bool exitProgram = false;

    while (!exitProgram) {
        cout << "\n** Welcome to the Supermarket Billing System **\n";
        cout << "1. Add items to inventory\n";
        cout << "2. Generate bill\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addItem(b);
                break;
            case 2:
                printBill();
                break;
            case 3:
                exitProgram = true;
                cout << "Goodbye! Have a great day!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}