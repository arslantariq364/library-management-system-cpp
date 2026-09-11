# 📚 Object-Oriented Library Management System in C++

[![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C.svg?logo=c%2B%2B&logoColor=white)](#)
[![Paradigm](https://img.shields.io/badge/Paradigm-Object--Oriented%20Programming-purple.svg)](#)
[![Polymorphism](https://img.shields.io/badge/OOP-Virtual%20Functions%20%7C%20Dynamic%20Dispatch-blue.svg)](#)
[![Memory](https://img.shields.io/badge/Memory-RAII%20%26%20Heap%20Management-brightgreen.svg)](#)
[![FAST NUCES](https://img.shields.io/badge/Academic-FAST%20NUCES-red.svg)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

> A modular, console-based Library Management System engineered in modern C++ demonstrating the core pillars of Object-Oriented Programming (OOP): Inheritance, Runtime Polymorphism, Dynamic Dispatch, Encapsulation, and Heap Lifecycle Management.

---

## 🏛️ Object-Oriented Architecture & Class Hierarchy

```mermaid
classDiagram
    class Book {
        +string book_id
        +string title
        +string author
        +int copies
        +int available
        +static int total_books
        +virtual display() void
        +virtual get_type() string
        +borrow() bool
        +return_book() bool
        +virtual ~Book()
    }

    class EBook {
        +float file_size_mb
        +display() void
        +get_type() string
    }

    class AudioBook {
        +float duration_hours
        +display() void
        +get_type() string
    }

    class Member {
        +string member_id
        +string name
        +string email
        +Book* borrowed_books[5]
        +int borrowed_count
        +static int total_members
        +virtual display() void
        +virtual get_type() string
        +borrow_book(Book* b) void
        +return_book(Book* b) void
        +virtual ~Member()
    }

    class PremiumMember {
        +int discount_percent
        +display() void
        +get_type() string
    }

    class Library {
        +string library_name
        +Book* books[100]
        +Member* members[50]
        +int book_count
        +int member_count
        +add_book(Book* b) void
        +delete_book(string id) void
        +search_book(string keyword) void
        +add_member(Member* m) void
        +borrow(string mid, string bid) void
        +return_book(string mid, string bid) void
        +stats() void
        +~Library()
    }

    Book <|-- EBook : Inherits
    Book <|-- AudioBook : Inherits
    Member <|-- PremiumMember : Inherits
    Library o-- Book : Aggregates
    Library o-- Member : Aggregates
```

---

## 🌟 Core OOP Concepts Implemented

1. **Inheritance & Specialization:** Base entity `Book` is extended into specialized media types `EBook` (with digital file size attributes) and `AudioBook` (with listening duration). Similarly, `Member` is specialized into `PremiumMember` with membership perks.
2. **Runtime Polymorphism & Virtual Functions:** Methods `display()` and `get_type()` are declared `virtual`, enabling late binding via virtual method tables (vtable) when iterating through heterogeneous object arrays (`Book*[]` and `Member*[]`).
3. **Encapsulation & Data Invariant Protection:** Critical counters (`total_books`, `total_members`) and borrowing thresholds are protected against illegal state transitions.
4. **Dynamic Memory Safety:** Custom destructor `~Library()` traverses object arrays to explicitly deallocate allocated heap memory, preventing memory leaks.
5. **Role-Based Authentication:** Protected administrative portal requiring pin credentials before permitting catalog modification.

---

## 🖥️ Interactive Console Workflow

```text
  ================================
     LIBRARY MANAGEMENT SYSTEM   
  ================================
         ADMIN SIGN IN           
  ================================
  Enter Password: ****
  Access Granted! Welcome Admin

  ================================
     LIBRARY MANAGEMENT SYSTEM   
  ================================
  [1] Book Management (Normal, EBook, AudioBook)
  [2] Member Management (Standard & Premium)
  [3] Borrow / Return Operations
  [4] Real-time Library Telemetry & Stats
  [0] Exit System
```

---

## 🛠️ Build & Run

### Prerequisites
Any standard C++ compiler supporting C++11 or newer (`g++`, `clang++`, or MSVC).

```bash
# Clone the repository
git clone https://github.com/arslantariq364/Library-Maanagement-System-OOP-Project.git
cd Library-Maanagement-System-OOP-Project

# Compile with optimization and compiler warnings
g++ -std=c++17 -Wall -Wextra -O2 Library_Management_System.cpp -o library_system

# Execute
./library_system
```

> **Default Admin Credential:** `1234`

---

## 👨‍💻 Author

**Arslan Tariq**  
*Computer Science Undergraduate @ FAST NUCES*  
*Applied Physics Teaching Assistant*  
[GitHub Profile](https://github.com/arslantariq364)

---

## 📜 License

Distributed under the MIT License. See [LICENSE](LICENSE) for details.
