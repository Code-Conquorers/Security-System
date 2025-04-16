# 🔐 Security System - C++ Console Application

## 📌 Project Overview
This is a C++-based console application for a **Security System** that manages user authentication with functionalities such as registration, login, password change, and password recovery using security questions.

Although the project is not based on an existing open source repository, it simulates the flow of a real-world authentication system, providing an educational glimpse into how login systems are built and managed.

---

## 🎯 Objectives
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
- `void loadUsers()`: Loads user data from a CSV file into memory.
- `void saveUsers()`: Saves all users from memory into a CSV file.
- `bool userExists(const string& username)`: Checks if a user already exists.
- `bool isStrongPassword(const string& password)`: Verifies password strength by ensuring it includes at least 8 characters, one uppercase letter, one lowercase letter, one digit, and one special character.
- `void registerUser()`: Handles user registration by collecting input, validating email and password, then storing user data.
- `void loginUser()`: Manages user login by verifying credentials against stored data.
- `void changePassword()`: Allows a user to change their password after verifying their old password.
- `void recoverPassword()`: Handles password recovery by asking the user’s predefined security question.
- `void showMenu()`: Displays the main menu and handles user choices in a loop until the user chooses to exit.
- `bool isValidEmail(const string& email)`: Helper function to validate email format (basic check for '@' and '.' positions).

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
Your Name / Group Members

