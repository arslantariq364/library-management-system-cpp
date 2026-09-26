# Object-Oriented Library Management in C++

An in-memory console coursework project demonstrating inheritance, polymorphism and catalog/borrowing operations.

The source defines Book, EBook and AudioBook, member types, and Library operations for adding, searching, borrowing and returning items. Virtual methods and destructors demonstrate OOP concepts.

## Run

```bash
git clone https://github.com/arslantariq364/library-management-system-cpp.git
cd library-management-system-cpp
g++ -std=c++17 -Wall -Wextra Library_Management_System.cpp -o library
./library
```

There is no database, persistent binary index, file serialization, overdue tracking or fine calculation. State is lost on exit. Boundary validation and automated test coverage need further work.
