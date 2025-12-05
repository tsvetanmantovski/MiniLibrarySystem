#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <stdexcept>


using namespace std;


// -------------------------
// Author
// -------------------------
class Author {
private:
string name_;
int birthYear_;
public:
Author() : name_("Unknown"), birthYear_(1900) {}
Author(const string& name, int birthYear) : name_(name), birthYear_(birthYear) { setBirthYear(birthYear); }


string getName() const { return name_; }
int getBirthYear() const { return birthYear_; }


void setName(const string& name) { name_ = name; }
void setBirthYear(int y) {
if (y < 1850 || y > 2025) {
throw invalid_argument("birthYear out of range (1850-2025)");
}
birthYear_ = y;
}


string to_string() const {
ostringstream oss;
oss << name_ << " (" << birthYear_ << ")";
return oss.str();
}
};


// -------------------------
// Book
// -------------------------
class Book {
private:
string title_;
Author author_;
int year_{};
double price_{};
string isbn_;
// helper to validate
static bool validYear(int y) { return y >= 1450 && y <= 2025; }
public:
static int totalBooks;


// default
Book() : title_("Untitled"), author_(), year_(1900), price_(0.0), isbn_("") { ++totalBooks; }


// parameterized
Book(const string& title, const Author& author, int year, double price, const string& isbn)
: title_(title), author_(author), year_(year), price_(price), isbn_(isbn) {
if (!validYear(year_)) throw invalid_argument("year out of range");
if (price_ < 0.0) throw invalid_argument("price must be >= 0");
++totalBooks;
}


// copy constructor
Book(const Book& other)
: title_(other.title_), author_(other.author_), year_(other.year_), price_(other.price_), isbn_(other.isbn_) {
++totalBooks; // new live instance
}


// move constructor
Book(Book&& other) noexcept
: title_(move(other.title_)), author_(move(other.author_)), year_(other.year_), price_(other.price_), isbn_(move(other.isbn_)) {
++totalBooks; // moved-into instance is still a live object
// leave other in valid state
other.year_ = 0; other.price_ = 0.0;
}

