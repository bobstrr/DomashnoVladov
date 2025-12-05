#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

class Author {
private:
    string name;
    int birthYear;
public:
    Author() : name("Unknown"), birthYear(1900) {}
    Author(const string& n, int by) : name(n), birthYear(by) {}

    string getName() const { return name; }
    int getBirthYear() const { return birthYear; }
    void setBirthYear(int by) {
        if (by >= 1850 && by <= 2025)
            birthYear = by;
    }

    string to_string() const {
        return name + " (" + std::to_string(birthYear) + ")";
    }
};

class Book {
private:
    string title;
    Author author;
    int year;
    double price;
    string isbn;
    static int totalBooks;
public:
    Book() : title("Unknown"), author(), year(1900), price(0.0), isbn("N/A") { totalBooks++; }
    Book(const string& t, const Author& a, int y, double p, const string& i)
        : title(t), author(a), year(y), price(p), isbn(i) { totalBooks++; }
    Book(const Book& other)
        : title(other.title), author(other.author), year(other.year), price(other.price), isbn(other.isbn) { totalBooks++; }
    Book(Book&& other) noexcept
        : title(move(other.title)), author(move(other.author)), year(other.year),
          price(other.price), isbn(move(other.isbn)) { totalBooks++; }
    Book& operator=(const Book& other) {
        if (this != &other) {
            title = other.title;
            author = other.author;
            year = other.year;
            price = other.price;
            isbn = other.isbn;
        }
        return *this;
    }
    Book& operator=(Book&& other) noexcept {
        if (this != &other) {
            title = move(other.title);
            author = move(other.author);
            year = other.year;
            price = other.price;
            isbn = move(other.isbn);
        }
        return *this;
    }
    ~Book() { totalBooks--; }

    string getTitle() const { return title; }
    Author getAuthor() const { return author; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    string getISBN() const { return isbn; }

    void setYear(int y) { if (y >= 1800 && y <= 2025) year = y; }
    void setPrice(double p) { if (p >= 0) price = p; }

    string to_string() const {
        ostringstream oss;
        oss << left << setw(20) << title
            << left << setw(22) << author.to_string()
            << right << setw(5) << year
            << "   " << fixed << setprecision(2) << setw(8) << price
            << "   " << setw(12) << isbn;
        return oss.str();
    }

    static int getTotalBooks() { return totalBooks; }
};
int Book::totalBooks = 0;

class Member {
private:
    string name;
    string memberId;
    int yearJoined;
public:
    Member() : name("Unknown"), memberId("N/A"), yearJoined(2025) {}
    Member(const string& n, const string& id, int y)
        : name(n), memberId(id), yearJoined(y) {}

    string getName() const { return name; }
    string getId() const { return memberId; }
    int getYearJoined() const { return yearJoined; }
    bool isValid() const { return !memberId.empty(); }

    string to_string() const {
        ostringstream oss;
        oss << left << setw(18) << name
            << left << setw(8) << memberId
            << "Joined: " << yearJoined;
        return oss.str();
    }
};

class Loan {
private:
    string isbn;
    string memberId;
    string startDate;
    string dueDate;
    bool returned;
public:
    Loan(const string& i, const string& mId, const string& start, const string& due)
        : isbn(i), memberId(mId), startDate(start), dueDate(due), returned(false) {
        if (dueDate < startDate) dueDate = startDate;
    }

    string getISBN() const { return isbn; }
    string getMemberId() const { return memberId; }
    bool isReturned() const { return returned; }
    string getDueDate() const { return dueDate; }
    string getStartDate() const { return startDate; }

    void markReturned() { returned = true; }
    bool isOverdue(const string& today) const {
        return (!returned && dueDate < today);
    }

    string to_string() const {
        ostringstream oss;
        oss << "ISBN: " << left << setw(11) << isbn
            << " | Member: " << left << setw(6) << memberId
            << " | " << startDate << " - " << dueDate
            << (returned ? " [returned]" : " [active]");
        return oss.str();
    }
};

class Library {
private:
    vector<Book> books;
    vector<Member> members;
    vector<Loan> loans;
public:
    void addBook(const Book& b) { books.push_back(b); }
    void addMember(const Member& m) {
        if (m.isValid())
            members.push_back(m);
    }
    bool hasBook(const string& isbn) const {
        return any_of(books.begin(), books.end(),
                      [&](const Book& b){ return b.getISBN() == isbn; });
    }
    bool isBookAvailable(const string& isbn) const {
        for(const Loan& l : loans) {
            if(l.getISBN() == isbn && !l.isReturned())
                return false;
        }
        return true;
    }
    bool loanBook(const string& isbn, const string& memberId,
                  const string& start, const string& due) {
        if (hasBook(isbn) && isBookAvailable(isbn)) {
            loans.push_back(Loan(isbn, memberId, start, due));
            return true;
        }
        return false;
    }
    bool returnBook(const string& isbn, const string& memberId) {
        for (Loan& l : loans) {
            if (l.getISBN() == isbn && l.getMemberId() == memberId && !l.isReturned()) {
                l.markReturned();
                return true;
            }
        }
        return false;
    }
    vector<Book> findByAuthor(const string& authorName) const {
        vector<Book> result;
        for(const Book& b : books) {
            if (b.getAuthor().getName().find(authorName) != string::npos)
                result.push_back(b);
        }
        return result;
    }
    vector<Member> getMembers() const { return members; }
    vector<Book> getBooks() const { return books; }
    vector<Loan> getLoans() const { return loans; }

    string to_string() const {
        int activeLoans = 0;
        for(const Loan& l : loans) {
            if (!l.isReturned()) activeLoans++;
        }
        ostringstream oss;
        oss << "Library Summary:\n";
        oss << "  Books:        " << books.size() << endl;
        oss << "  Members:      " << members.size() << endl;
        oss << "  Active loans: " << activeLoans << endl;
        return oss.str();
    }
};

int main() {
    Library lib;

    Author vazov("Ivan Vazov", 1850);
    lib.addBook(Book("Pod igoto", vazov, 1894, 25.50, "ISBN-001"));
    lib.addBook(Book("Nema zemya", vazov, 1900, 18.90, "ISBN-002"));
    lib.addMember(Member("Petar Petrov", "M001", 2023));

    cout << "===== Library =====\n";
    cout << lib.to_string() << "\n";

    cout << "Members:\n";
    for (const auto& m : lib.getMembers())
        cout << m.to_string() << "\n";
    cout << "\n";

    cout << "Books:\n";
    cout << left << setw(20) << "Title"
         << left << setw(22) << "Author"
         << setw(5)  << "Year"
         << "   " << setw(8) << "Price"
         << "   " << setw(12) << "ISBN" << "\n";

    for (const auto& b : lib.getBooks())
        cout << b.to_string() << "\n";

    cout << "\nCreating loan for ISBN-001...\n";
    if (lib.loanBook("ISBN-001", "M001", "2025-11-03", "2025-11-17"))
        cout << "Loan created.\n";
    else
        cout << "Loan failed.\n";

    cout << "\nActive loans:\n";
    for (const auto& l : lib.getLoans())
        if (!l.isReturned())
            cout << l.to_string() << "\n";

    cout << "\nAvailability check for ISBN-001:\n";
    cout << (lib.isBookAvailable("ISBN-001") ? "Available\n" : "Not available\n");

    cout << "\nReturning ISBN-001...\n";
    lib.returnBook("ISBN-001", "M001");
    cout << (lib.isBookAvailable("ISBN-001") ? "Returned successfully\n" : "Return failed\n");

    cout << "\nBooks by author containing 'Vazov':\n";
    for (const auto& bk : lib.findByAuthor("Vazov"))
        cout << bk.to_string() << "\n";
    
    return 0;
}

