#include <iostream>
#include <fstream>
using namespace std;

class bill {
private:
    string product_name;
    int product_price, product_qty;

public:
    // Constructor initializes the object with default values
    bill() : product_name(""), product_price(0), product_qty(0) {}

    // Setters for product details
    void setproduct_name(string n) {
        product_name = n;
    }
    void setproduct_price(int p) {
        product_price = p;
    }
    void setproduct_qty(int q) {
        product_qty = q;
    }

    // Getters for product details
    string getproduct_name() {
        return product_name;
    }
    int getproduct_price() {
        return product_price;
    }
    int getproduct_qty() {
        return product_qty;
    }
};

// Function to add items to the inventory
void addinventoary(bill b) {
    bool close = false; // Loop control variable
    while (!close) {
        int val;
        cout << "\n1. Add item to inventory\n";
        cout << "2. Back to main menu\n";
        cout << "Enter your choice: ";
        cin >> val;

        if (val == 1) {
            string it;
            int pr, qty;
            cout << "Enter the name of the item: ";
            cin >> it;
            cout << "Enter the price of the item: ";
            cin >> pr;
            cout << "Enter the quantity of the item: ";
            cin >> qty;

            // Setting product details
            b.setproduct_name(it);
            b.setproduct_price(pr);
            b.setproduct_qty(qty);

            // Writing the item to the inventory file
            ofstream ofs("newbill.txt", ios::app);
            if (!ofs) {
                cout << "Error: Could not open the file.\n";
            } else {
                ofs << b.getproduct_name() << endl;
                ofs << b.getproduct_price() << endl;
                ofs << b.getproduct_qty() << endl;
                ofs.close();
                cout << "Item added to inventory successfully.\n";
            }
        } else if (val == 2) {
            close = true; // Exit the loop
            cout << "Returning to main menu...\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Function to calculate and display the bill
void addbill() {
    int count = 0; // To keep track of the total bill amount
    bool control = false; // Loop control variable

    while (!control) {
        int num;
        cout << "\n1. Add items to your cart\n";
        cout << "2. Calculate the total bill and exit\n";
        cout << "Enter your choice: ";
        cin >> num;

        if (num == 1) {
            string item_n;
            int item_q;
            cout << "Enter the name of the item: ";
            cin >> item_n;
            cout << "Requested quantity: ";
            cin >> item_q;

            ifstream ifs("newbill.txt");
            ofstream out("tempbill.txt");
            
            string item_name;
            int price, availableQuantity;
            bool statement = false; // To track if the item was found

            // Read inventory and update it based on the requested item
            while (ifs >> item_name >> price >> availableQuantity) {
                if (item_n == item_name) {
                    statement = true;
                    if (item_q <= availableQuantity) {
                        int amount = item_q * price;
                        cout << "\nItem Name | Item Quantity | Total Amount\n";
                        cout << item_name << " | " << item_q << " | " << amount << endl;
                        availableQuantity -= item_q; // Deduct the purchased quantity
                        count += amount; // Add to the total bill
                    } else {
                        cout << "Insufficient stock for item: " << item_name << endl;
                    }
                }
                // Write the updated inventory back to the temporary file
                out << item_name << endl << price << endl << availableQuantity << endl;
            }

            if (!statement) {
                cout << "Item not found in inventory.\n";
            }

            ifs.close();
            out.close();

            // Replace the old inventory file with the updated one
            remove("newbill.txt");
            rename("tempbill.txt", "newbill.txt");

        } else if (num == 2) {
            control = true; // Exit the loop
            cout << "\nYour total bill is: " << count << endl;
            cout << "Exiting bill calculation...\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Main menu
int main() {
    bill b; // Bill object to manage inventory
    bool choose = false; // Loop control variable

    while (!choose) {
        int choise;
        cout << "*** Welcome to Supermarket Billing System ***\n";
        cout << "1. Add items to inventory\n";
        cout << "2. Add bill\n";
        cout << "3. Exit the menu\n";
        cout << "Enter your choice: ";
        cin >> choise;

        switch (choise) {
            case 1:
                addinventoary(b);
                break;
            case 2:
                addbill();
                break;
            case 3:
                choose = true; // Exit the loop
                cout << "Thank you for shopping with us!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}