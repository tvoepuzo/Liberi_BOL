#include <Windows.h> 
#pragma execution_character_set("utf-8")
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Book {
private:
    int id;
    string name;
    string author;
    bool vydana;

public:
    Book(int i, string n, string a) {
        id = i;
        name = n;
        author = a;
        vydana = false;
    }

    int getId() { return id; }
    string getName() { return name; }
    bool getVydana() { return vydana; }

    void setName(string n) { name = n; }
    void setAuthor(string a) { author = a; }
    void setVydana(bool v) { vydana = v; }

    void show() {
        cout << id << ". " << name << " - " << author;
        if (vydana) cout << " (выдана)";
        else cout << " (свободна)";
        cout << endl;
    }
};

class Reader {
private:
    int id;
    string name;

public:
    Reader(int i, string n) {
        id = i;
        name = n;
    }

    int getId() { return id; }
    string getName() { return name; }

    void setName(string n) { name = n; }

    void show() {
        cout << id << ". " << name << endl;
    }
};

class Library {
private:
    vector<shared_ptr<Book>> books;
    vector<unique_ptr<Reader>> readers;
    int bookId = 4;
    int readerId = 3;

public:
    Library() {
        books.push_back(make_shared<Book>(1, "Евгений Онегин", "Пушкин"));
        books.push_back(make_shared<Book>(2, "Мастер и Маргарита", "Булгаков"));
        books.push_back(make_shared<Book>(3, "Преступление и наказание", "Достоевский"));

        readers.push_back(make_unique<Reader>(1, "Иван"));
        readers.push_back(make_unique<Reader>(2, "Анна"));
    }

    void menu() {
        int v;

        do {
            cout << "\n--- БИБЛИОТЕКА ---\n 1. Книги\n 2. Добавить книгу\n 3. Изменить книгу\n 4. Удалить книгу\n 5. Читатели\n 6. Добавить читателя\n 7. Изменить читателя\n 8. Удалить читателя\n 9. Выдать книгу\n 10. Книги читателя\n 11. Статистика\n 0. Выход\n";
            cout << "Выбор: ";
            cin >> v;

            if (v == 1) {
                for (auto b : books) b->show();
            }

            if (v == 2) {
                string n, a;
                cin.ignore();
                cout << "Название: ";
                getline(cin, n);
                cout << "Автор: ";
                getline(cin, a);
                books.push_back(make_shared<Book>(bookId++, n, a));
            }

            if (v == 3) {
                int id;
                cout << "ID книги: ";
                cin >> id;

                for (auto b : books) {
                    if (b->getId() == id) {
                        string n, a;
                        cin.ignore();
                        cout << "Новое название: ";
                        getline(cin, n);
                        cout << "Новый автор: ";
                        getline(cin, a);
                        b->setName(n);
                        b->setAuthor(a);
                    }
                }
            }

            if (v == 4) {
                int id;
                cout << "ID книги: ";
                cin >> id;

                for (int i = 0; i < books.size(); i++) {
                    if (books[i]->getId() == id && !books[i]->getVydana()) {
                        books.erase(books.begin() + i);
                        break;
                    }
                }
            }

            if (v == 5) {
                for (auto& r : readers) r->show();
            }

            if (v == 6) {
                string n;
                cin.ignore();
                cout << "Имя читателя: ";
                getline(cin, n);
                readers.push_back(make_unique<Reader>(readerId++, n));
            }

            if (v == 7) {
                int id;
                cout << "ID читателя: ";
                cin >> id;

                for (auto& r : readers) {
                    if (r->getId() == id) {
                        string n;
                        cin.ignore();
                        cout << "Новое имя: ";
                        getline(cin, n);
                        r->setName(n);
                    }
                }
            }

            if (v == 8) {
                int id;
                cout << "ID читателя: ";
                cin >> id;

                for (int i = 0; i < readers.size(); i++) {
                    if (readers[i]->getId() == id) {
                        readers.erase(readers.begin() + i);
                        break;
                    }
                }
            }

            if (v == 9) {
                int b, r;
                cout << "ID книги: ";
                cin >> b;
                cout << "ID читателя: ";
                cin >> r;

                for (auto book : books) {
                    if (book->getId() == b && !book->getVydana()) {
                        for (auto& reader : readers) {
                            if (reader->getId() == r) {
                                book->setVydana(true);
                                cout << "Книга выдана!\n";
                            }
                        }
                    }
                }
            }

            if (v == 10) {
                int id;
                cout << "ID читателя: ";
                cin >> id;
                cout << "Книги читателя:\n";

                for (auto b : books) {
                    if (b->getVydana())
                        b->show();
                }
            }

            if (v == 11) {
                int free = 0, issued = 0;

                for (auto b : books) {
                    if (b->getVydana()) issued++;
                    else free++;
                }

                cout << "Всего книг: " << books.size() << endl;
                cout << "Свободно: " << free << endl;
                cout << "Выдано: " << issued << endl;
                cout << "Читателей: " << readers.size() << endl;
            }

        } while (v != 0);
    }
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Library lib;
    lib.menu();

    return 0;
}