# College Library Management System

A simple, menu-driven **C++17** project for managing a college library. It helps a librarian maintain book records, register students/members, issue books, and record book returns.

## Objectives

- Maintain book details and available quantities.
- Register and display student/member records.
- Search books by title or author.
- Issue available books to registered members.
- Record returns and update book availability.
- Save data in local text files so records are available after restarting the program.

## Features

1. Add a new book with a unique book ID.
2. Display all books and their available/total quantities.
3. Search books by title or author (case-insensitive).
4. Register students/members with a unique ID.
5. Display all registered members.
6. Issue a book to a registered member.
7. Return an issued book.
8. View currently issued books.
9. Automatically save data in `books.txt`, `members.txt`, and `issues.txt`.

## Technology Used

- Language: C++
- Standard: C++17
- Concepts: structures, vectors, functions, loops, file handling, searching, and basic validation
- Interface: console/menu-based

## Project Structure

```text
college-library-management-system/
├── main.cpp
├── README.md
├── .gitignore
├── books.txt       # created automatically when data is saved
├── members.txt     # created automatically when data is saved
└── issues.txt      # created automatically when data is saved
```

## Requirements

- A C++ compiler that supports C++17 (GCC, MinGW, or Clang).
- Windows, Linux, or macOS terminal.

## How to Compile and Run

### Linux / macOS

```bash
g++ -std=c++17 -Wall -Wextra -o library main.cpp
./library
```

### Windows (MinGW)

```bash
g++ -std=c++17 -Wall -Wextra -o library.exe main.cpp
library.exe
```

### Visual Studio Code

1. Install a C++ compiler such as MinGW-w64.
2. Install the C/C++ extension.
3. Open this project folder in VS Code.
4. Open the terminal and run the compile command for your operating system.
5. Run the generated executable.

## How to Use

1. Select **1** to add books. Enter a unique ID, title, author, and quantity.
2. Select **4** to register a student/member.
3. Select **6** to issue a book using the book ID and member ID.
4. Select **8** to see all current issue records.
5. Select **7** to return a book using the same book ID and member ID.
6. Select **2** or **3** to view or search the catalogue.
7. Select **0** to save and exit.

## Data Storage

The program stores records in three pipe-separated text files in the same folder as the executable:

- `books.txt`: book ID, title, author, total quantity, available quantity
- `members.txt`: member ID, name, department/course
- `issues.txt`: book ID, member ID

These files are created automatically when the program saves data. Keep them with the executable if you want to retain your library records.

## Limitations / Future Enhancements

This is an academic starter project, not a production library system. Possible improvements:

- Add login and librarian/admin roles.
- Add issue date, due date, and overdue fine calculation.
- Add edit/delete options for books and members.
- Add a graphical interface or web interface.
- Replace text files with SQLite or MySQL.
- Add stronger input validation and backup/restore features.

## Author

Add your name, course, college, and academic year here.

## License

This project is available for learning and academic use. Add a license file if you want to publish it under a specific open-source license.
