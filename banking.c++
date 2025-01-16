/*Banking Management System

A C++ application to manage customer accounts and perform essential banking operations.

Features
	•	Create, update, and delete customer accounts.
	•	Deposit and withdraw funds.
	•	Check account balance.
	•	Store account data using file handling for persistent storage.*/

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

// Account class to represent individual bank accounts
class Account {
private:
    long accountNumber; // Unique account number
    string firstName;   // First name of the account holder
    string lastName;    // Last name of the account holder
    float balance;      // Account balance
    static long NextAccountNumber; // Static variable to track the next account number

public:
    Account() {} // Default constructor
    Account(string fname, string lname, float balance); // Parameterized constructor

    // Getters for account details
    long getAccNo() { return accountNumber; }
    string getFirstName() { return firstName; }
    string getLastName() { return lastName; }
    float getBalance() { return balance; }

    // Functions to deposit and withdraw money
    void Deposit(float amount);
    void Withdraw(float amount);

    // Static functions to manage account numbering
    static void setLastAccountNumber(long accountNumber);
    static long getLastAccountNumber();

    // Overloaded operators for file and console I/O
    friend ofstream &operator<<(ofstream &ofs, Account &a);
    friend ifstream &operator>>(ifstream &ifs, Account &a);
    friend ostream &operator<<(ostream &os, Account &a);
};

// Bank class to manage multiple accounts
class bank {
private:
    map<long, Account> accounts; // Map to store accounts with account number as the key

public:
    bank(); // Constructor to load accounts from file
    Account newaccount(string fname, string lname, float balance); // Create a new account
    Account checkbalance(long account_number); // Check balance of an account
    Account amountdepo(long account_number, float amount); // Deposit amount to an account
    Account amountwithd(long account_number, float amount); // Withdraw amount from an account
    void CloseAccount(long accountNumber); // Close an account
    void showallaccount(); // Display all accounts
    ~bank(); // Destructor to save accounts to file
};

// Initialize static member
long Account::NextAccountNumber = 0;

// Account class constructor to initialize account details
Account::Account(string fname, string lname, float balance) {
    NextAccountNumber++;
    firstName = fname;
    lastName = lname;
    this->balance = balance;
    accountNumber = NextAccountNumber;
}

// Deposit function to add money to balance
void Account::Deposit(float amount) {
    balance += amount;
}

// Withdraw function to deduct money from balance
void Account::Withdraw(float amount) {
    if (balance >= amount) 
        balance -= amount;
    else 
        cout << "Insufficient funds!" << endl;
}

// Static function to set the last account number
void Account::setLastAccountNumber(long accountNumber) {
    NextAccountNumber = accountNumber;
}

// Static function to get the last account number
long Account::getLastAccountNumber() {
    return NextAccountNumber;
}

// Overload << operator to write account details to a file
ofstream &operator<<(ofstream &ofs, Account &a) {
    ofs << a.accountNumber << endl;
    ofs << a.firstName << endl;
    ofs << a.lastName << endl;
    ofs << a.balance << endl;
    return ofs;
}

// Overload >> operator to read account details from a file
ifstream &operator>>(ifstream &ifs, Account &a) {
    ifs >> a.accountNumber;
    ifs >> a.firstName;
    ifs >> a.lastName;
    ifs >> a.balance;
    return ifs;
}

// Overload << operator to display account details on the console
ostream &operator<<(ostream &os, Account &a) {
    os << "First Name: " << a.getFirstName() << endl;
    os << "Last Name: " << a.getLastName() << endl;
    os << "Account Number: " << a.getAccNo() << endl;
    os << "Balance: " << a.getBalance() << endl;
    return os;
}

// Bank class constructor to load accounts from file
bank::bank() {
    Account account;
    ifstream ifs;
    ifs.open("bank.data");
    if (!ifs) {
        cout << "Error in Opening! File Not Found!" << endl;
        return;
    }
    while (!ifs.eof()) {
        ifs >> account;
        accounts.insert(pair<long, Account>(account.getAccNo(), account));
    }
    Account::setLastAccountNumber(account.getAccNo());
    ifs.close();
}

// Create a new account and save it to the file
Account bank::newaccount(string fname, string lname, float balance) {
    ofstream ofs;
    Account account(fname, lname, balance);
    accounts.insert(pair<long, Account>(account.getAccNo(), account));
    ofs.open("bank.data", ios::trunc);
    for (map<long, Account>::iterator itr = accounts.begin(); itr != accounts.end(); itr++) {
        ofs << itr->second;
    }
    ofs.close();
    return account;
}

// Retrieve account details for balance enquiry
Account bank::checkbalance(long account_number) {
    return accounts[account_number];
}

// Deposit amount to a specific account
Account bank::amountdepo(long account_number, float amount) {
    accounts[account_number].Deposit(amount);
    return accounts[account_number];
}

// Withdraw amount from a specific account
Account bank::amountwithd(long account_number, float amount) {
    accounts[account_number].Withdraw(amount);
    return accounts[account_number];
}

// Close an account and remove it from the map
void bank::CloseAccount(long accountNumber) {
    cout << "Account Deleted: " << accounts[accountNumber];
    accounts.erase(accountNumber);
}

// Display details of all accounts
void bank::showallaccount() {
    for (map<long, Account>::iterator itr = accounts.begin(); itr != accounts.end(); itr++) {
        cout << "Account " << itr->first << endl << itr->second << endl;
    }
}

// Destructor to save all accounts to the file on program exit
bank::~bank() {
    ofstream ofs;
    ofs.open("bank.data", ios::trunc);
    for (map<long, Account>::iterator itr = accounts.begin(); itr != accounts.end(); itr++) {
        ofs << itr->second;
    }
    ofs.close();
}

// Main function to drive the Banking System
int main() {
    bank b; // Create a bank object
    Account acc; // Account object to hold temporary data
    string fname, lname;
    int choice;
    float balance, amount;
    long acc_number;

    cout << " *BANKING SYSTEM" << endl;

    do {
        // Menu display
        cout << "\n1. Open an Account";
        cout << "\n2. Balance Enquiry";
        cout << "\n3. Deposit";
        cout << "\n4. Withdrawal";
        cout << "\n5. Close an A/C";
        cout << "\n6. Show All A/C";
        cout << "\n7. Quit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            // Open a new account
            cout << "Enter First Name: ";
            cin >> fname;
            cout << "Enter Last Name: ";
            cin >> lname;
            cout << "Enter Opening Balance: ";
            cin >> balance;
            acc = b.newaccount(fname, lname, balance);
            cout << "\nCongratulations! Account Created!" << endl;
            cout << acc;
            break;

        case 2:
            // Balance enquiry
            cout << "Enter Account Number: ";
            cin >> acc_number;
            acc = b.checkbalance(acc_number);
            cout << "\nAccount Details:\n" << acc;
            break;

        case 3:
            // Deposit amount
            cout << "Enter Account Number: ";
            cin >> acc_number;
            cout << "Enter Deposit Amount: ";
            cin >> amount;
            acc = b.amountdepo(acc_number, amount);
            cout << "\nAmount Deposited!" << endl;
            cout << acc;
            break;

        case 4:
            // Withdraw amount
            cout << "Enter Account Number: ";
            cin >> acc_number;
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;
            acc = b.amountwithd(acc_number, amount);
            cout << "\nAmount Withdrawn!" << endl;
            cout << acc;
            break;

        case 5:
            // Close an account
            cout << "Enter Account Number to Close: ";
            cin >> acc_number;
            b.CloseAccount(acc_number);
            break;

        case 6:
            // Show all accounts
            b.showallaccount();
            break;

        case 7:
            // Exit the program
            cout << "Thank you for using the Banking System!" << endl;
            break;

        default:
            // Invalid choice
            cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 7);

    return 0;
}
