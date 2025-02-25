#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <locale>
#define DDMMYYYY_LENTH 11

class Author {
private:
    int id;                         //id автора
    int* book_ids;                  //id книг
    int books_count;                //счетчик книг
    char* name;                     //имя автора
    char birthdate[DDMMYYYY_LENTH]; //дата рождения

public:
    Author() : book_ids(nullptr), books_count(0) {}

    ~Author() {
        free(book_ids);
        free(name);
    }

    //ввод автора
    void input() {
        char temp_name[25];
        std::cout << "[  Автор  ]\n" << "Введите имя: ";
        std::cin.getline(temp_name, 25);
        name = (char*)malloc(strlen(temp_name) + 1);
        strcpy(name, temp_name);

        std::cout << "Введите дату рождения дд.мм.гггг: ";
        std::cin.getline(birthdate, DDMMYYYY_LENTH);

        std::cout << "Введите id автора: ";
        std::cin >> id;
        std::cin.ignore();
    }

    //вывод автора
    void output() const {
        std::cout << "Автор:\n";
        std::cout << "  Имя - " << name << "\n";
        std::cout << "  Дата рождения - " << birthdate << "\n";
        std::cout << "  ID автора - " << id << "\n";
        if (books_count) {
            std::cout << "  ID книг:\n";
            for (int i = 0; i < books_count; i++) {
                std::cout << "    - " << book_ids[i] << "\n";
            }
        }
        else {
            std::cout << "  Нет книг от данного автора\n";
        }
        std::cout << "\n";
    }

    //добавление книги
    void addBook(int book_id) {
        books_count++;
        book_ids = (int*)realloc(book_ids, books_count * sizeof(int));
        book_ids[books_count - 1] = book_id;
    }

    //выдача id автора
    int getId() const {
        return id;
    }
};

class Book {
private:
    int id;                 //id книги
    bool is_available;      //статус доступности книги
    int author_id;          //id фвтора
    char* title;            //название книги
    char published_year[5]; //год публикации

public:
    Book() : title(nullptr), is_available(true) {}

    ~Book() {
        free(title);
    }

    //ввод книги
    void input(int author_id) {
        this->author_id = author_id;

        char temp_title[25];
        std::cout << "[  Книга  ]\n" << "Введите название: ";
        std::cin.getline(temp_title, 25);
        title = (char*)malloc(strlen(temp_title) + 1);
        strcpy(title, temp_title);

        std::cout << "Введите год публикации: ";
        std::cin.getline(published_year, 5);

        std::cout << "Введите id книги: ";
        std::cin >> id;
        std::cin.ignore();
    }

    //вывод книги
    void output() const {
        std::cout << "Книга:\n";
        std::cout << "  Название - " << title << "\n";
        std::cout << "  Год публикации - " << published_year << "\n";
        std::cout << "  ID книги - " << id << "\n";
        std::cout << "  ID автора - " << author_id << "\n";
        std::cout << "  Статус - " << (is_available ? "Доступна" : "Не доступна") << "\n\n";
    }

    //управление доступонстью книги
    void setAvailability(bool status) {
        is_available = status;
    }

    //выдача id книги
    int getId() const {
        return id;
    }

};

class Reader {
private:
    int id;                 //id читателя
    int borrowed_book_id;   //id занятой книги
    char* name;             //имя
    char* email;            //эл. почта

public:
    Reader() : name(nullptr), email(nullptr), borrowed_book_id(0) {}

    ~Reader() {
        free(name);
        free(email);
    }

    //ввод читателя
    void input() {
        char temp_name[25];
        char temp_email[35];
        std::cout << "[  Читатель  ]\n" << "Введите имя: ";
        std::cin.getline(temp_name, 25);
        name = (char*)malloc(strlen(temp_name) + 1);
        strcpy(name, temp_name);

        std::cout << "Введите email: ";
        std::cin.getline(temp_email, 35);
        email = (char*)malloc(strlen(temp_email) + 1);
        strcpy(email, temp_email);

        std::cout << "Введите id читателя: ";
        std::cin >> id;
        std::cin.ignore();
    }

    //вывод читателя
    void output() const {
        std::cout << "Читатель:\n";
        std::cout << "  Имя - " << name << "\n";
        std::cout << "  Почта - " << email << "\n";
        std::cout << "  ID читателя - " << id << "\n";
        std::cout << "  ID занятой книги - ";
        if (borrowed_book_id == 0) std::cout << "Книг не занято" << "\n\n";
        else std::cout << borrowed_book_id << "\n\n";
    }

    //выдача id читателя
    int getId() const {
        return id;
    }
};

class Order {
private:
    int id;                             //id запроса
    int reader_id;                      //id читателя
    int book_id;                        //id запрашиваемой
    char orderdate[DDMMYYYY_LENTH];     //дата запроса
    char returndate[DDMMYYYY_LENTH];    //дата возврата

public:
    Order() {
        strcpy(returndate, "unreturned");
    }

    //ввод запроса
    void input(int reader_id, int book_id) {
        this->reader_id = reader_id;
        this->book_id = book_id;

        std::cout << "[  Запрос  ]\n" << "Введите id запроса: ";
        std::cin >> id;
        std::cin.ignore();

        std::cout << "дата запроса дд.мм.гггг: ";
        std::cin.getline(orderdate, DDMMYYYY_LENTH);
    }

    //вывод запроса
    void output() const {
        std::cout << "Запрос:\n";
        std::cout << "  ID запроса - " << id << "\n";
        std::cout << "  ID книги - " << book_id << "\n";
        std::cout << "  ID читателя - " << reader_id << "\n";
        std::cout << "  Дата запроса - " << orderdate << "\n";
        std::cout << "  Дата возврата - " << returndate << "\n\n";
    }

    //добавление даты возврата
    void edit(const char* return_date) {
        strcpy(returndate, return_date);
    }
};

class Fine {
private:
    int id;         //id штрафа
    int reader_id;  //id читателя
    int amount;     //размер штрафа
    bool is_paid;   //оплачен ли штраф
    char* reason;   //причина штрафа

public:
    Fine() : reason(nullptr), is_paid(false) {}

    ~Fine() {
        free(reason);
    }

    //ввод штрафа
    void input(int reader_id) {
        this->reader_id = reader_id;

        std::cout << "[  Штраф  ]\n" << "Введите объем штрафа: ";
        std::cin >> amount;

        std::cout << "Введите id штрафа: ";
        std::cin >> id;
        std::cin.ignore();

        char temp_reason[150];
        std::cout << "Причина штрафа: ";
        std::cin.getline(temp_reason, 150);
        reason = (char*)malloc(strlen(temp_reason) + 1);
        strcpy(reason, temp_reason);
    }

    //вывод штрафа
    void output() const {
        std::cout << "Штраф:\n";
        std::cout << "  ID штрафа - " << id << "\n";
        std::cout << "  ID читателя - " << reader_id << "\n";
        std::cout << "  Объем штрафа - " << amount << " $\n";
        std::cout << "  Статус  - " << (is_paid ? "Оплачен" : "Не оплачен") << "\n";
        std::cout << "  Причина - " << reason << "\n\n";
    }

    //присвоение статуса "оплачен"
    void edit() {
        is_paid = true;
    }
};

int main() {
    int hwmnybooks;
    setlocale(LC_ALL, "Rus");

    Author Lary;
    Lary.input();
    Lary.output();

    std::cout << "Солько добавить книг?: ";
    std::cin >> hwmnybooks;
    std::cin.ignore();

    Book* Gary = new Book[hwmnybooks];
    for (int i = 0; i < hwmnybooks; ++i) {
        std::cout << "N" << (i + 1) << ": ";
        Gary[i].input(Lary.getId());
        Lary.addBook(Gary[i].getId()); // Добавление книги к автору
    }

    // Вывод данных всех книг
    for (int i = 0; i < hwmnybooks; ++i) {
        Gary[i].output();
    }
    Lary.output();

    Reader Mary;
    Mary.input();
    Mary.output();

    Order Pery;
    Pery.input(Mary.getId(), Gary->getId());
    Pery.output();

    // Пример редактирования заказа
    Pery.edit("21.11.2121");
    Pery.output();

    Fine Jery;
    Jery.input(Mary.getId());
    Jery.output();

    // Пример редактирования штрафа
    Jery.edit();
    Jery.output();

    // Освобождение памяти
    delete[] Gary;

    return 0;
}
