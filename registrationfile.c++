#include <iostream>
#include <fstream>
using namespace std;

class Login {
private:
    string login_id, password;

public:
    Login() : login_id(" "), password("") {}

    void setId(string id) {
        login_id = id;
    }

    void setPassword(string pw) {
        password = pw;
    }

    string getId() {
        return login_id;
    }

    string getPassword() {
        return password;
    }
};

int main() {
    Login person;
    int x;
    string lg, pw;
    string check_pw, check_id;

    do {
        cout << "\n\t** Welcome to the Registration and Login Form **" << endl;
        cout << "\t***********************************************\n";
        cout << "\t1. Register" << endl;
        cout << "\t2. Login" << endl;
        cout << "\t3. Exit" << endl;
        cout << "\tEnter your choice: ";
        cin >> x;

        if (x == 1) {
            cout << "\tEnter the ID name: ";
            cin >> lg;
            person.setId(lg);

            ofstream ofs("details.txt", ios::app);
            if (!ofs) {
                cout << "\tError: Could not open file for registration.\n";
                continue;
            }
            ofs << person.getId();

            do {
                cout << "\tEnter the password (minimum 8 characters): ";
                cin >> pw;
                if (pw.length() >= 8) {
                    person.setPassword(pw);
                    ofs << " " << person.getPassword() << endl;
                } else {
                    cout << "\tPassword must be at least 8 characters long. Try again.\n";
                }
            } while (pw.length() < 8);

            ofs.close();
            cout << "\tUser registered successfully!\n";

        } else if (x == 2) {
            cout << "\tEnter the login credentials.\n";
            cout << "\tID: ";
            cin >> check_id;
            cout << "\tPassword: ";
            cin >> check_pw;

            ifstream ifs("details.txt");
            if (!ifs) {
                cout << "\tError: Could not open file for login.\n";
                continue;
            }

            string if_id, if_pw;
            bool found = false;
            while (ifs >> if_id >> if_pw) {
                if (check_id == if_id && check_pw == if_pw) {
                    found = true;
                    break;
                }
            }
            ifs.close();

            if (found) {
                cout << "\tLogin successful! Welcome, " << check_id << "!\n";
            } else {
                cout << "\tNo match found. Login failed.\n";
            }

        } else if (x == 3) {
            cout << "\tExiting the program. Goodbye!\n";
        } else {
            cout << "\tInvalid choice. Please try again.\n";
        }

    } while (x != 3);

    return 0;
}