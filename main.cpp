#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

struct Book {
    int id;
    string title, author;
    int total, available;
};

struct Member {
    int id;
    string name, department;
};

struct Issue {
    int bookId, memberId;
};

const string BOOKS_FILE = "books.txt";
const string MEMBERS_FILE = "members.txt";
const string ISSUES_FILE = "issues.txt";

vector<Book> books;
vector<Member> members;
vector<Issue> issues;

string cleanInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

Book* findBook(int id) {
    for (auto& book : books)
        if (book.id == id) return &book;
    return nullptr;
}

Member* findMember(int id) {
    for (auto& member : members)
        if (member.id == id) return &member;
    return nullptr;
}

void saveData() {
    ofstream bookFile(BOOKS_FILE);
    for (const auto& b : books)
        bookFile << b.id << '|' << b.title << '|' << b.author << '|'
                 << b.total << '|' << b.available << '\n';

    ofstream memberFile(MEMBERS_FILE);
    for (const auto& m : members)
        memberFile << m.id << '|' << m.name << '|' << m.department << '\n';

    ofstream issueFile(ISSUES_FILE);
    for (const auto& i : issues)
        issueFile << i.bookId << '|' << i.memberId << '\n';
}

void loadData() {
    string line;
    {
        ifstream file(BOOKS_FILE);
        while (getline(file, line)) {
            if (line.empty()) continue;
            Book b{};
            size_t p1 = line.find('|'), p2 = line.find('|', p1 + 1);
            size_t p3 = line.find('|', p2 + 1), p4 = line.find('|', p3 + 1);
            if (p1 == string::npos || p2 == string::npos ||
                p3 == string::npos || p4 == string::npos) continue;
            try {
                b.id = stoi(line.substr(0, p1));
                b.title = line.substr(p1 + 1, p2 - p1 - 1);
                b.author = line.substr(p2 + 1, p3 - p2 - 1);
                b.total = stoi(line.substr(p3 + 1, p4 - p3 - 1));
                b.available = stoi(line.substr(p4 + 1));
                books.push_back(b);
            } catch (...) { /* Skip damaged records. */ }
        }
    }
    {
        ifstream file(MEMBERS_FILE);
        while (getline(file, line)) {
            if (line.empty()) continue;
            size_t p1 = line.find('|'), p2 = line.find('|', p1 + 1);
            if (p1 == string::npos || p2 == string::npos) continue;
            try {
                Member m;
                m.id = stoi(line.substr(0, p1));
                m.name = line.substr(p1 + 1, p2 - p1 - 1);
                m.department = line.substr(p2 + 1);
                members.push_back(m);
            } catch (...) { /* Skip damaged records. */ }
        }
    }
    {
        ifstream file(ISSUES_FILE);
        while (getline(file, line)) {
            if (line.empty()) continue;
            size_t p = line.find('|');
            if (p == string::npos) continue;
            try {
                issues.push_back({stoi(line.substr(0, p)), stoi(line.substr(p + 1))});
            } catch (...) { /* Skip damaged records. */ }
        }
    }
}

void addBook() {
    int id = readInt("Enter book ID: ");
    if (findBook(id)) {
        cout << "A book with this ID already exists.\n";
        return;
    }
    Book b;
    b.id = id;
    b.title = cleanInput("Enter book title: ");
    b.author = cleanInput("Enter author name: ");
    b.total = readInt("Enter total quantity: ");
    if (b.total <= 0) {
        cout << "Quantity must be greater than zero.\n";
        return;
    }
    b.available = b.total;
    books.push_back(b);
    saveData();
    cout << "Book added successfully.\n";
}

void displayBooks() {
    if (books.empty()) {
        cout << "No books found.\n";
        return;
    }
    cout << "\n---------------- BOOK LIST ----------------\n";
    cout << "ID\tTitle\t\tAuthor\t\tAvailable/Total\n";
    for (const auto& b : books)
        cout << b.id << "\t" << b.title << "\t\t" << b.author
             << "\t\t" << b.available << "/" << b.total << '\n';
}

void searchBook() {
    string keyword = cleanInput("Enter title or author to search: ");
    transform(keyword.begin(), keyword.end(), keyword.begin(),
              [](unsigned char c) { return static_cast<char>(tolower(c)); });
    bool found = false;
    for (const auto& b : books) {
        string title = b.title, author = b.author;
        transform(title.begin(), title.end(), title.begin(),
                  [](unsigned char c) { return static_cast<char>(tolower(c)); });
        transform(author.begin(), author.end(), author.begin(),
                  [](unsigned char c) { return static_cast<char>(tolower(c)); });
        if (title.find(keyword) != string::npos || author.find(keyword) != string::npos) {
            cout << "ID: " << b.id << " | " << b.title << " | " << b.author
                 << " | Available: " << b.available << '\n';
            found = true;
        }
    }
    if (!found) cout << "No matching book found.\n";
}

void addMember() {
    int id = readInt("Enter member/student ID: ");
    if (findMember(id)) {
        cout << "A member with this ID already exists.\n";
        return;
    }
    Member m;
    m.id = id;
    m.name = cleanInput("Enter member name: ");
    m.department = cleanInput("Enter department/course: ");
    members.push_back(m);
    saveData();
    cout << "Member registered successfully.\n";
}

void displayMembers() {
    if (members.empty()) {
        cout << "No members registered.\n";
        return;
    }
    cout << "\n-------------- MEMBER LIST --------------\n";
    cout << "ID\tName\t\tDepartment/Course\n";
    for (const auto& m : members)
        cout << m.id << "\t" << m.name << "\t\t" << m.department << '\n';
}

void issueBook() {
    int bookId = readInt("Enter book ID to issue: ");
    int memberId = readInt("Enter member/student ID: ");
    Book* book = findBook(bookId);
    Member* member = findMember(memberId);

    if (!book) {
        cout << "Book ID not found.\n";
        return;
    }
    if (!member) {
        cout << "Member ID not found. Register the member first.\n";
        return;
    }
    if (book->available <= 0) {
        cout << "This book is currently not available.\n";
        return;
    }
    for (const auto& issue : issues) {
        if (issue.bookId == bookId && issue.memberId == memberId) {
            cout << "This member has already issued this book.\n";
            return;
        }
    }

    issues.push_back({bookId, memberId});
    --book->available;
    saveData();
    cout << "Book issued successfully to " << member->name << ".\n";
}

void returnBook() {
    int bookId = readInt("Enter book ID to return: ");
    int memberId = readInt("Enter member/student ID: ");

    auto it = find_if(issues.begin(), issues.end(), [&](const Issue& i) {
        return i.bookId == bookId && i.memberId == memberId;
    });

    if (it == issues.end()) {
        cout << "No matching issue record found.\n";
        return;
    }

    issues.erase(it);
    Book* book = findBook(bookId);
    if (book) ++book->available;
    saveData();
    cout << "Book returned successfully.\n";
}

void viewIssuedBooks() {
    if (issues.empty()) {
        cout << "There are no currently issued books.\n";
        return;
    }
    cout << "\n------------ CURRENTLY ISSUED BOOKS ------------\n";
    cout << "Book ID\tBook Title\tMember ID\tMember Name\n";
    for (const auto& i : issues) {
        Book* b = findBook(i.bookId);
        Member* m = findMember(i.memberId);
        cout << i.bookId << "\t" << (b ? b->title : "Unknown")
             << "\t" << i.memberId << "\t\t"
             << (m ? m->name : "Unknown") << '\n';
    }
}

void showMenu() {
    cout << "\n============================================\n";
    cout << "       COLLEGE LIBRARY MANAGEMENT SYSTEM\n";
    cout << "============================================\n";
    cout << "1. Add Book\n";
    cout << "2. Display All Books\n";
    cout << "3. Search Book\n";
    cout << "4. Register Student/Member\n";
    cout << "5. Display All Members\n";
    cout << "6. Issue Book\n";
    cout << "7. Return Book\n";
    cout << "8. View Currently Issued Books\n";
    cout << "0. Exit\n";
    cout << "--------------------------------------------\n";
}

int main() {
    loadData();
    cout << "Welcome to the College Library Management System!\n";

    while (true) {
        showMenu();
        int choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: addMember(); break;
            case 5: displayMembers(); break;
            case 6: issueBook(); break;
            case 7: returnBook(); break;
            case 8: viewIssuedBooks(); break;
            case 0:
                saveData();
                cout << "Data saved. Thank you for using the system!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
