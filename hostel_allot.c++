#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h> // For sleep()
using namespace std;

// Hostel class definition
class Hostel {
private:
    string hostel_name; // Name of the hostel
    int price;          // Price per bed
    int bed;            // Number of available beds

public:
    // Constructor to initialize the hostel object
    Hostel(string name, int Price, int Bed) {
        hostel_name = name;
        price = Price;
        bed = Bed;
    }

    // Getter for hostel name
    string getHostelName() {
        return hostel_name;
    }

    // Getter for price
    int getPrice() {
        return price;
    }

    // Getter for available beds
    int getBeds() {
        return bed;
    }

    // Method to update the bed count and write changes to the file
    void updateBedCount() {
        if (bed > 0) {
            bed--; // Decrement the bed count as one is reserved
            // Open the file in truncate mode to overwrite existing data
            ofstream ofs("hostel.txt", ios::trunc);
            if (ofs.is_open()) {
                ofs << "Hostel Name: " << hostel_name << endl;
                ofs << "Price: " << price << endl;
                ofs << "Beds: " << bed << endl;
                ofs.close(); // Close the file after writing
                cout << "\nHostel data updated successfully.\n";
            } else {
                cout << "\nError: Unable to update hostel.txt.\n";
            }
        } else {
            cout << "\nNo beds available in the hostel.\n";
        }
    }
};

// Student class definition
class Student {
private:
    string st_name; // Student's name
    string address; // Student's address
    int reg_no;     // Student's registration number

public:
    // Setter for student's name
    void setStudentName(string s) {
        st_name = s;
    }

    // Setter for student's address
    void setAddress(string a) {
        address = a;
    }

    // Setter for student's registration number
    void setRegNo(int r) {
        reg_no = r;
    }

    // Getter for student's name
    string getStudentName() {
        return st_name;
    }

    // Getter for student's address
    string getAddress() {
        return address;
    }

    // Getter for student's registration number
    int getRegNo() {
        return reg_no;
    }
};

// Function to reserve a bed for a student
void reserveBed(Student &s, Hostel &h) {
    string name, address;
    int reg_no;

    // Get student details
    cout << "\nEnter the student's name: ";
    cin >> name;
    cout << "Enter the student's address: ";
    cin >> address;
    cout << "Enter the student's registration number: ";
    cin >> reg_no;

    // Set student details in the Student object
    s.setStudentName(name);
    s.setAddress(address);
    s.setRegNo(reg_no);

    // Append the student details to the student file
    ofstream ofs("student.txt", ios::app);
    if (ofs.is_open()) {
        ofs << "Student Name: " << s.getStudentName() << ", Address: " << s.getAddress()
            << ", Reg No: " << s.getRegNo() << endl;
        ofs.close();
        cout << "\nStudent registered successfully.\n";
    } else {
        cout << "\nError: Unable to save student data.\n";
    }

    // Check bed availability and update the hostel file if a bed is reserved
    cout << "\nChecking bed availability...\n";
    sleep(2);
    if (h.getBeds() > 0) {
        h.updateBedCount();
    } else {
        cout << "\nNo beds available in the hostel.\n";
    }
}

// Main function
int main() {
    // Initialize a hostel with a name, price, and number of beds
    Hostel h("H1", 1200, 2);

    // Write the initial hostel data to the hostel.txt file
    ofstream out("hostel.txt");
    if (out.is_open()) {
        out << "Hostel Name: " << h.getHostelName() << endl;
        out << "Price: " << h.getPrice() << endl;
        out << "Beds: " << h.getBeds() << endl;
        out.close();
    } else {
        cout << "Error: Unable to write initial hostel data to hostel.txt" << endl;
    }

    Student s;  // Create a Student object
    bool running = true; // Flag to keep the menu running

    // Main menu loop
    while (running) {
        cout << "\n** Welcome to Hostel Accommodation System **\n";
        cout << "********************************************\n";
        cout << "1. Reserve a Bed\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: // Option to reserve a bed
                if (h.getBeds() > 0) {
                    reserveBed(s, h);
                    cout << "Bed reserved successfully.\n";
                } else {
                    cout << "Not enough beds available.\n";
                }
                break;
            case 2: // Option to exit
                running = false;
                break;
            default: // Handle invalid input
                cout << "\nInvalid choice. Please try again.\n";
                sleep(2);
                break;
        }
    }

    return 0;
}