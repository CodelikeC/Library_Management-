#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
protected:
    string id;
    string title;
    string author;
    int publisherYear;

public:
    Book() {}
    Book(string id, string title, string author, int publisherYear)
        : id(id), title(title), author(author), publisherYear(publisherYear) {}

    string getId() const { return id; }
    void setId(string id) { this->id = id; }

    string getTitle() const { return title; }
    void setTitle(string title) { this->title = title; }

    string getAuthor() const { return author; }
    void setAuthor(string author) { this->author = author; }

    int getPublisherYear() const { return publisherYear; }
    void setPublisherYear(int year) { this->publisherYear = year; }

    virtual void toString() const = 0;
};

class Novel : public Book {
private:
    string genre;
    int pages;

public:
    Novel() {}
    Novel(string id, string title, string author, int publisherYear, string genre, int pages)
        : Book(id, title, author, publisherYear), genre(genre), pages(pages) {}

    string getGenre() const { return genre; }
    void setGenre(string genre) { this->genre = genre; }

    int getPages() const { return pages; }
    void setPages(int pages) { this->pages = pages; }

    void toString() const override {
        cout << "ID: " << id << "\nTitle: " << title << "\nAuthor: " << author << "\nPublisher Year: "
             << publisherYear << "\nGenre: " << genre << "\nPages: " << pages << endl;
    }
};

class Magazine : public Book 
{
private:
    string category;
    int issueNumber;

public:
    Magazine() {}
    Magazine(string id, string title, string author, int publisherYear, string category, int issueNumber)
        : Book(id, title, author, publisherYear), category(category), issueNumber(issueNumber) {}

    string getCategory() const { return category; }
    void setCategory(string category) { this->category = category; }

    int getIssueNumber() const { return issueNumber; }
    void setIssueNumber(int issueNumber) { this->issueNumber = issueNumber; }

    void toString() const override {
        cout << "ID: " << id << "\nTitle: " << title << "\nAuthor: " << author << "\nPublisher Year: "
             << publisherYear << "\nCategory: " << category << "\nIssue Number: " << issueNumber << endl;
    }
};

class Textbook : public Book {
private:
    string subject;
    string isbn;

public:
    Textbook() {}
    Textbook(string id, string title, string author, int publisherYear, string subject, string isbn)
        : Book(id, title, author, publisherYear), subject(subject), isbn(isbn) {}

    string getSubject() const { return subject; }
    void setSubject(string subject) { this->subject = subject; }

    string getIsbn() const { return isbn; }
    void setIsbn(string isbn) { this->isbn = isbn; }

    void toString() const override {
        cout << "ID: " << id << "\nTitle: " << title << "\nAuthor: " << author << "\nPublisher Year: "
             << publisherYear << "\nSubject: " << subject << "\nISBN: " << isbn << endl;
    }
};

int main() {
    vector<Book*> books;
    char choice;

    do {
        cout << "\nBookstore Management System\n";
        cout << "1. Add a new book\n";
        cout << "2. Display all books\n";
        cout << "3. Search for a book by title\n";
        cout << "4. Remove a book by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1': {
                char type;
                cout << "Select book type (N for Novel, M for Magazine, T for Textbook): ";
                cin >> type;

                string id, title, author;
                int year;
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter publisher year: ";
                cin >> year;

                if (type == 'N') {
                    string genre;
                    int pages;
                    cout << "Enter genre: ";
                    cin >> genre;
                    cout << "Enter pages: ";
                    cin >> pages;
                    books.push_back(new Novel(id, title, author, year, genre, pages));
                } else if (type == 'M') {
                    string category;
                    int issueNumber;
                    cout << "Enter category: ";
                    cin >> category;
                    cout << "Enter issue number: ";
                    cin >> issueNumber;
                    books.push_back(new Magazine(id, title, author, year, category, issueNumber));
                } else if (type == 'T') {
                    string subject, isbn;
                    cout << "Enter subject: ";
                    cin >> subject;
                    cout << "Enter ISBN: ";
                    cin >> isbn;
                    books.push_back(new Textbook(id, title, author, year, subject, isbn));
                } else {
                    cout << "Invalid choice.\n";
                }

                cout << "Book added successfully.\n";
                break;
            }
            case '2':
                if (books.empty()) {
                    cout << "No books available.\n";
                } else {
                    cout << "\nAll Books Information:\n";
                    for (const auto& book : books) {
                        book->toString();
                        cout << endl;
                    }
                }
                break;
            case '3': {
                string searchTitle;
                cout << "Enter title to search: ";
                cin.ignore();
                getline(cin, searchTitle);
                bool found = false;
                for (const auto& book : books) {
                    if (book->getTitle() == searchTitle) {
                        book->toString();
                        found = true;
                        break;
                    }
                }
                if (!found)
                    cout << "Book not found.\n";
                break;
            }
            case '4': {
                string removeId;
                cout << "Enter ID of book to remove: ";
                cin >> removeId;
                bool removed = false;
                for (auto it = books.begin(); it != books.end(); ++it) {
                    if ((*it)->getId() == removeId) {
                        delete *it;
                        books.erase(it);
                        removed = true;
                        cout << "Book removed successfully.\n";
                        break;
                    }
                }
                if (!removed)
                    cout << "Book with ID " << removeId << " not found.\n";
                break;
            }
            case '5':
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != '5');

    // Free memory
    for (auto book : books)
        delete book;

    return 0;
}
