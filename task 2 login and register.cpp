#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to register a user
void registerUser() {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    file.close();

    cout << "Registration successful!\n";
}

// Function to check if the username and password are correct
bool loginUser() {
    string username, password, u, p;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    while (file >> u >> p) {
        if (u == username && p == password) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// Function to reset the password
void resetPassword() {
    string username, newPassword, u, p;
    cout << "Enter your username: ";
    cin >> username;
    
    ifstream file("users.txt");
    ofstream temp("temp.txt");

    bool found = false;
    while (file >> u >> p) {
        if (u == username) {
            cout << "Enter new password: ";
            cin >> newPassword;
            temp << u << " " << newPassword << endl;
            found = true;
        } else {
            temp << u << " " << p << endl;
        }
    }

    file.close();
    temp.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (found)
        cout << "Password reset successfully!\n";
    else
        cout << "Username not found!\n";
}

int main() {
    int choice;
    while (true) {
        cout << "\n1. Register\n2. Login\n3. Reset Password\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser())
                    cout << "Login successful!\n";
                else
                    cout << "Invalid username or password!\n";
                break;
            case 3:
                resetPassword();
                break;
            case 4:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }
}
