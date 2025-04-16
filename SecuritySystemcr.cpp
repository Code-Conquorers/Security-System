#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <cctype>

using namespace std;

class SecuritySystem {
private:
    struct User {
        string username;
        string password;
        string age;
        string securityQuestion;
        string securityAnswer;
    };

    unordered_map<string, User> users;
    const string dataFile = "users.csv";

    void loadUsers();
    void saveUsers();
    bool userExists(const string& username);
    bool isStrongPassword(const string& password);  // New helper function

public:
    void registerUser();
    void loginUser();
    void changePassword();
    void recoverPassword();
    void showMenu();
};

// Helper function to check valid email
bool isValidEmail(const string& email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);

    return atPos != string::npos &&
           dotPos != string::npos &&
           atPos < dotPos &&
           atPos > 0 &&
           dotPos < email.length() - 1;
}

// Helper function to check if password is strong
bool SecuritySystem::isStrongPassword(const string& password) {
    if (password.length() < 8) return false;  // Check if length is less than 8 characters

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

    for (char ch : password) {
        if (isupper(ch)) hasUpper = true;
        if (islower(ch)) hasLower = true;
        if (isdigit(ch)) hasDigit = true;
        if (ispunct(ch)) hasSpecial = true;
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

// Load users from file
void SecuritySystem::loadUsers() {
    users.clear();
    ifstream file(dataFile);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        User user;
        getline(ss, user.username, ',');
        getline(ss, user.password, ',');
        getline(ss, user.age, ',');
        getline(ss, user.securityQuestion, ',');
        getline(ss, user.securityAnswer, ',');

        users[user.username] = user;
    }
    file.close();
}

// Save users to file
void SecuritySystem::saveUsers() {
    ofstream file(dataFile);
    for (const auto& pair : users) {
        const User& user = pair.second;
        file << user.username << ","
             << user.password << ","
             << user.age << ","
             << user.securityQuestion << ","
             << user.securityAnswer << "\n";
    }
    file.close();
}

// Check if username exists
bool SecuritySystem::userExists(const string& username) {
    return users.find(username) != users.end();
}

// Register new user
void SecuritySystem::registerUser() {
    loadUsers();
    User newUser;

    cout << "\n--- Register ---\n";
    cout << "Enter email (username): ";
    cin >> newUser.username;

    if (!isValidEmail(newUser.username)) {
        cout << "❌ Invalid email format. Please use something like user@gmail.com\n";
        return;
    }

    if (userExists(newUser.username)) {
        cout << "❌ Username already exists. Please choose another.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> newUser.password;

    // Check if the password is strong
    while (!isStrongPassword(newUser.password)) {
        cout << "❌ Password is too weak. Please use a password with at least:\n";
        cout << "- 8 characters\n";
        cout << "- At least one uppercase letter\n";
        cout << "- At least one lowercase letter\n";
        cout << "- At least one digit\n";
        cout << "- At least one special character\n";
        cout << "Enter a strong password: ";
        cin >> newUser.password;
    }

    cout << "Enter age: ";
    cin >> newUser.age;
    cin.ignore();

    cout << "Set a security question (e.g., What is your pet's name?): ";
    getline(cin, newUser.securityQuestion);
    cout << "Enter your answer: ";
    getline(cin, newUser.securityAnswer);

    users[newUser.username] = newUser;
    saveUsers();

    cout << "✅ Registration successful!\n";
}

// Login user
void SecuritySystem::loginUser() {
    loadUsers();
    string uname, pass;
    cout << "\n--- Login ---\n";
    cout << "Enter email: ";
    cin >> uname;
    cout << "Enter password: ";
    cin >> pass;

    if (userExists(uname) && users[uname].password == pass) {
        cout << "✅ Login successful!\n";
        cout << "User Details:\nUsername: " << users[uname].username
             << "\nAge: " << users[uname].age << "\n";
    } else {
        cout << "❌ Incorrect credentials.\n";
    }
}

// Change password
void SecuritySystem::changePassword() {
    loadUsers();
    string uname, oldPass;
    cout << "\n--- Change Password ---\n";
    cout << "Enter email: ";
    cin >> uname;

    if (!userExists(uname)) {
        cout << "❌ User not found.\n";
        return;
    }

    cout << "Enter old password: ";
    cin >> oldPass;

    if (users[uname].password != oldPass) {
        cout << "❌ Incorrect old password.\n";
        return;
    }

    string newPass1, newPass2;
    cout << "Enter new password: ";
    cin >> newPass1;
    cout << "Confirm new password: ";
    cin >> newPass2;

    // Check if the new password is strong
    while (!isStrongPassword(newPass1)) {
        cout << "❌ Password is too weak. Please use a password with at least:\n";
        cout << "- 8 characters\n";
        cout << "- At least one uppercase letter\n";
        cout << "- At least one lowercase letter\n";
        cout << "- At least one digit\n";
        cout << "- At least one special character\n";
        cout << "Enter a strong new password: ";
        cin >> newPass1;
    }

    if (newPass1 == newPass2) {
        users[uname].password = newPass1;
        saveUsers();
        cout << "✅ Password changed successfully!\n";
    } else {
        cout << "❌ Passwords do not match.\n";
    }
}

// Recover password
void SecuritySystem::recoverPassword() {
    loadUsers();
    string uname;
    cout << "\n--- Recover Password ---\n";
    cout << "Enter email: ";
    cin >> uname;

    if (!userExists(uname)) {
        cout << "❌ User not found.\n";
        return;
    }

    cin.ignore();
    string answer;
    cout << "Security Question: " << users[uname].securityQuestion << "\n";
    cout << "Your Answer: ";
    getline(cin, answer);

    if (answer != users[uname].securityAnswer) {
        cout << "❌ Incorrect answer.\n";
        return;
    }

    string newPass1, newPass2;
    cout << "Enter new password: ";
    getline(cin, newPass1);
    cout << "Confirm new password: ";
    getline(cin, newPass2);

    // Check if the new password is strong
    while (!isStrongPassword(newPass1)) {
        cout << "❌ Password is too weak. Please use a password with at least:\n";
        cout << "- 8 characters\n";
        cout << "- At least one uppercase letter\n";
        cout << "- At least one lowercase letter\n";
        cout << "- At least one digit\n";
        cout << "- At least one special character\n";
        cout << "Enter a strong new password: ";
        getline(cin, newPass1);
    }

    if (newPass1 == newPass2) {
        users[uname].password = newPass1;
        saveUsers();
        cout << "✅ Password reset successfully.\n";
    } else {
        cout << "❌ Passwords do not match.\n";
    }
}

// Show main menu
void SecuritySystem::showMenu() {
    int choice;
    do {
        cout << "\n========= Security System =========\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Change Password\n";
        cout << "4. Forgot Password (Recover)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: changePassword(); break;
            case 4: recoverPassword(); break;
            case 5: cout << "👋 Exiting. Thank you!\n"; break;
            default: cout << "❌ Invalid option.\n"; break;
        }
    } while (choice != 5);
}

int main() {
    SecuritySystem system;
    system.showMenu();
    return 0;
}
