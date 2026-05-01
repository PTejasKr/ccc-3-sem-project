# 💳 AlgoBank ATM System (C-Based Terminal Banking Simulator)

## 📌 Overview

AlgoBank ATM System is a **secure, terminal-based banking simulation** built in C. It demonstrates core banking operations such as account management, authentication, transactions, and logging, while integrating concepts like **file persistence, structured data handling, and algorithmic cash dispensing**.

This project is designed for:

* Systems programming practice
* DBMS + OS concept integration
* Algorithm demonstration (Greedy vs Dynamic Programming)
* Academic and portfolio use

---

## 🚀 Features

### 🔐 Authentication & Security

* PIN-based login system
* Duplicate account prevention
* Admin-restricted access
* Masked account display (partial visibility)
* Input validation and error handling

### 👤 Account Management

* Create new accounts via CLI
* Persistent storage using binary files (`accounts.dat`)
* Unique account ID enforcement
* Scalable structure (supports up to 100 users by default)

### 💰 Banking Operations

* Balance inquiry
* Deposit funds
* Withdraw funds with validation
* Transaction logging

### 📜 Logging System

* All transactions recorded in `transactions.log`
* Timestamp-based logging
* Useful for auditing and debugging

### 🛠 Admin Panel

* Protected with password (`9999` by default)
* View all user accounts and balances
* Acts as a monitoring system

### 💡 Algorithmic Component

* Demonstrates:

  * Greedy Algorithm (fast, not always optimal)
  * Dynamic Programming (optimal note distribution)
* Helps visualize real-world optimization problems

---

## 🏗 Project Structure

```
AlgoBank/
│
├── atm.c                 # Main source code
├── accounts.dat          # Binary file storing account data (auto-generated)
├── transactions.log      # Transaction logs (auto-generated)
└── README.md             # Project documentation
```

---

## ⚙️ Installation & Setup

### 1. Prerequisites

Ensure you have a C compiler installed:

| Platform | Installation Command     |
| -------- | ------------------------ |
| Linux    | `sudo apt install gcc`   |
| Mac      | `brew install gcc`       |
| Windows  | Install MinGW or use WSL |

---

### 2. Clone Repository

```
git clone https://github.com/PTejasKr/algobank-atm.git
cd algobank-atm
```

---

### 3. Compile the Program

```
gcc atm.c -o atm
```

---

### 4. Run the Application

```
./atm
```

---

## 🧑‍💻 Usage Guide

### 🔑 Login

* Enter account ID and PIN
* Access dashboard upon successful authentication

### 🆕 Create Account

1. Select **Create Account**
2. Enter:

   * Unique Account ID
   * Name
   * PIN
3. Account is stored in `accounts.dat`

---

### 💳 Dashboard Options

* Check balance
* Deposit funds
* Withdraw funds
* Logout

---

### 🛡 Admin Access

* Select **Admin Panel**
* Enter password: `9999`

Capabilities:

* View all users
* Monitor balances

---

## 📂 Data Storage

### `accounts.dat`

* Binary file storing:

  * Account ID
  * Name
  * Balance
  * PIN

### `transactions.log`

* Plain text log file
* Format:

```
Timestamp : Transaction Description
```

---

## 🔒 Security Considerations

| Feature                | Status            |
| ---------------------- | ----------------- |
| PIN Authentication     | ✅ Implemented     |
| Data Persistence       | ✅ Implemented     |
| Encryption             | ❌ Not implemented |
| Brute-force Protection | ⚠ Basic           |
| Multi-user Isolation   | ❌ Not implemented |

⚠ **Important:**
This is a simulation project and **not suitable for real-world banking systems**.

---

## ⚠ Limitations

* No encryption for sensitive data
* No concurrency support
* CLI-based UI only
* Fixed admin password
* No transaction rollback

---

## 🔮 Future Enhancements

### 🔐 Security

* Hashing (SHA-256 / bcrypt for PINs)
* OTP-based authentication
* Role-based access control

### 🗄 Database Integration

* MySQL / PostgreSQL backend
* ORM-like abstraction

### 🖥 UI/UX

* GUI using GTK or Qt
* Web version (React + Node.js)

### ⚡ Performance

* Multi-threading
* Memory optimization

---

## 🧪 Testing Recommendations

* Test invalid login attempts
* Test duplicate account creation
* Test large transactions
* Verify file persistence after restart

---

## 📊 Sample Workflow

```
User → Login → Dashboard
     → Deposit → Logged
     → Withdraw → Logged
     → Logout
```

---

## 🧾 Example Accounts (Optional Setup)

You may manually add accounts in code or create them via UI.

Example:

```
ID: 1001 | Name: Aarav | PIN: 1234 | Balance: ₹15000
```

---

## 🤝 Contribution Guidelines

1. Fork the repository
2. Create a feature branch
3. Commit changes
4. Submit pull request

---

## 📜 License

This project is for educational purposes.
You may modify and distribute with attribution.

---

## 👨‍💻 Author

Developed as a systems + algorithm integration project in C.

---

## ⭐ Final Note

This project bridges:

* **System Programming (C)**
* **Data Persistence**
* **Algorithm Design**
* **Software Engineering Practices**

It is ideal for demonstrating **low-level engineering + applied logic design** in a real-world inspired scenario.
