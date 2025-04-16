# 🔐 Security System - C++ Console Application

## 📌 Project Overview
This is a C++-based console application for a **Security System** that manages user authentication with functionalities such as registration, login, password change, and password recovery using security questions.

Although the project is not based on an existing open source repository, it simulates the flow of a real-world authentication system, providing an educational glimpse into how login systems are built and managed.

---

## 🌟 Objectives
- Learn about file handling and user management in C++.
- Understand how basic authentication mechanisms work.
- Simulate a real-world use case of password policies and security questions.
- Explore the use of data structures like maps (`unordered_map`) and how data persistence can be handled via CSV files.

---

## 🧠 Breadth-wise Understanding
The project covers various aspects of a typical user management system:
- User registration with input validation
- Login authentication
- Password strength enforcement
- Password recovery using security questions
- File handling for persistent storage

---

## 🔍 Depth-wise Analysis
### ✅ Approaches Taken
- CSV-based file storage is used to mimic database functionality.
- Input validation ensures only strong passwords and valid emails are accepted.
- Simple CLI-based interaction mimics real-world user flows.

### 🧱 Data Structures Used
- `unordered_map<string, User>`: Stores all user data in-memory using username as the key.
- `struct User`: Represents the user model with fields like email, password, age, security question and answer.

### ⚖️ Trade-offs Made
- **CSV file** is used instead of a real database for simplicity.
- No encryption is used for passwords due to the basic nature of the app.
- The interface is kept simple to prioritize backend logic.

---

## 🧠 Functions Used in Code

### `void loadUsers()`
Clears existing users and loads data from the CSV file:
```cpp
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
```

### `void saveUsers()`
Writes all users to CSV file:
```cpp
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
```

### `bool userExists(const string& username)`
Checks if the username exists:
```cpp
return users.find(username) != users.end();
```

### `bool isStrongPassword(const string& password)`
Checks password complexity:
```cpp
if (password.length() < 8) return false;
bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
for (char ch : password) {
    if (isupper(ch)) hasUpper = true;
    if (islower(ch)) hasLower = true;
    if (isdigit(ch)) hasDigit = true;
    if (ispunct(ch)) hasSpecial = true;
}
return hasUpper && hasLower && hasDigit && hasSpecial;
```

### `void registerUser()`
Handles new user registration:
```cpp
loadUsers();
User newUser;
cout << "Enter email: ";
cin >> newUser.username;
// validate email & check existence
cout << "Enter password: ";
cin >> newUser.password;
// check strength
cout << "Enter age: ";
cin >> newUser.age;
cin.ignore();
cout << "Security question: ";
getline(cin, newUser.securityQuestion);
cout << "Answer: ";
getline(cin, newUser.securityAnswer);
users[newUser.username] = newUser;
saveUsers();
```

### `void loginUser()`
Authenticates user:
```cpp
loadUsers();
string uname, pass;
cout << "Enter email: "; cin >> uname;
cout << "Enter password: "; cin >> pass;
if (userExists(uname) && users[uname].password == pass) {
    cout << "Login successful!";
} else {
    cout << "Incorrect credentials.";
}
```

### `void changePassword()`
Changes existing user's password:
```cpp
loadUsers();
string uname, oldPass;
cout << "Enter email: "; cin >> uname;
cout << "Enter old password: "; cin >> oldPass;
if (users[uname].password == oldPass) {
    string newPass1, newPass2;
    cout << "Enter new password: "; cin >> newPass1;
    cout << "Confirm password: "; cin >> newPass2;
    if (newPass1 == newPass2 && isStrongPassword(newPass1)) {
        users[uname].password = newPass1;
        saveUsers();
        cout << "Password changed.";
    } else {
        cout << "Passwords don’t match or weak.";
    }
} else {
    cout << "Wrong old password.";
}
```

### `void recoverPassword()`
Resets password via security question:
```cpp
loadUsers();
string uname;
cout << "Enter email: "; cin >> uname;
cin.ignore();
cout << "Security Question: " << users[uname].securityQuestion << "\n";
string answer; getline(cin, answer);
if (answer == users[uname].securityAnswer) {
    string newPass1, newPass2;
    cout << "Enter new password: "; getline(cin, newPass1);
    cout << "Confirm new password: "; getline(cin, newPass2);
    if (newPass1 == newPass2 && isStrongPassword(newPass1)) {
        users[uname].password = newPass1;
        saveUsers();
        cout << "Password reset successful.";
    } else {
        cout << "Passwords don’t match or weak.";
    }
} else {
    cout << "Incorrect answer.";
}
```

### `void showMenu()`
Displays the user menu:
```cpp
int choice;
do {
    cout << "1. Register\n2. Login\n3. Change Password\n4. Recover Password\n5. Exit\n";
    cin >> choice;
    switch (choice) {
        case 1: registerUser(); break;
        case 2: loginUser(); break;
        case 3: changePassword(); break;
        case 4: recoverPassword(); break;
        case 5: cout << "Exiting..."; break;
        default: cout << "Invalid choice."; break;
    }
} while (choice != 5);
```

### `bool isValidEmail(const string& email)`
Validates format of email:
```cpp
size_t atPos = email.find('@');
size_t dotPos = email.find('.', atPos);
return atPos != string::npos && dotPos != string::npos && atPos < dotPos;
```

---

## 🚀 How to Run
1. Clone/download the repository.
2. Compile using a C++ compiler (e.g., `g++ security_system.cpp -o security_system`)
3. Run the program (`./security_system` or `security_system.exe`)
4. `users.csv` will be created in the working directory to store user data.

---

## 💬 Feedback & Contributions
Feel free to fork, improve, or suggest new features! For learning purposes only.

---

## 📁 Files
- `security_system.cpp` - Main source code
- `users.csv` - Stores user data
- `README.md` - This presentation document

---

## 🧑‍💻 Author
Codeconqurors
## Output
![image alt](https://github.com/Code-Conquorers/Security-System/blob/7b7a35dd294f0917bdcddaf1b7dbdf597fdca6d2/security%20system.jpg)
![image alt](https://github.com/Code-Conquorers/Security-System/blob/2acbfd10f37ca56d344dca9e830254ef9d11e4f4/login.jpg)
