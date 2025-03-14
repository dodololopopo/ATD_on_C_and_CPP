#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <locale>
#define DDMMYYYY_LENTH 11

class Author {
    friend void show_id_to_bkcnt(const Author&);
private:
    int id;                         //id автора
    int* book_ids;                  //id книг
    int books_count;                //счетчик книг
    std::string name;                     //имя автора
    std::string birthdate; //дата рождения

public:
    static int amount_of_authors;   //общее число авторов
    
    Author() : book_ids(nullptr), books_count(0) {}

    ~Author() {
        free(book_ids);
    }

    //ввод автора
    void input() {
        std::cout << "[  Автор  ]\n" << "Введите имя: ";
        std::cin >> name;

        std::cout << "Введите дату рождения дд.мм.гггг: ";
        std::cin >> birthdate;

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
    int* getId() {
        return &id;
    }

    int& get_books_count(){
        return books_count;
    }

    //при добавлении автора их общее число растет
    void increment() {
        amount_of_authors++;
    }

    //при удалении автора их общее число уменьшается
    void decrement() {
        amount_of_authors--;
    }

    //отображение общего числа авторов
    static void show_amount_of_authors() {
        std::cout << "\n\n" << "Всего авторов: " << amount_of_authors << "\n\n";
    }
};

class Book {
private:
    int id;                 //id книги
    bool is_available;      //статус доступности книги
    int author_id;          //id фвтора
    std::string title;            //название книги
    std::string published_year; //год публикации

public:
    Book() : is_available(true) {}

    ~Book() {}

    //ввод книги
    void input(int author_id) {
        this->author_id = author_id;

        std::cout << "[  Книга  ]\n" << "Введите название: ";
        std::cin >> title;

        std::cout << "Введите год публикации: ";
        std::cin >> published_year;

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
    
    //перегрузка "+" для создания дилогии книг
    Book operator+(const Book& other) const {
        Book duology;
        duology.author_id = this->author_id;
        std::cout << "\n\nСоставляем дилогию" << "\nВведите id: ";
        std::cin >> duology.id;
        duology.is_available = true;
        duology.title = "Дилогия " + this->title + other.title;
        std::cout << "Год публикации: ";
        std::cin >> duology.published_year;
        return duology;
    }
    
    //перегрузка "++" постфиксно для переключения доступности
    Book operator++(int) {
        Book temp = *this;
        if (is_available == true) is_available = false;
        else is_available = true;
        return *this;
     }
};

class Reader {
private:
    int id;                 //id читателя
    int borrowed_book_id;   //id занятой книги
    std::string name;             //имя
    std::string email;            //эл. почта

public:
    Reader() : borrowed_book_id(0) {}

    ~Reader() {}

    //ввод читателя
    void input() {
        std::cout << "[  Читатель  ]\n" << "Введите имя: ";
        std::cin >> name;

        std::cout << "Введите email: ";
        std::cin >> email;

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
    std::string orderdate;     //дата запроса
    std::string returndate;    //дата возврата

public:
    Order() {}

    //ввод запроса
    void input(int reader_id, int book_id) {
        this->reader_id = reader_id;
        this->book_id = book_id;

        std::cout << "[  Запрос  ]\n" << "Введите id запроса: ";
        std::cin >> id;
        std::cin.ignore();

        std::cout << "дата запроса дд.мм.гггг: ";
        std::cin >> orderdate;
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
    void edit(std::string return_date) {
        this->returndate = return_date;
    }
};

class Fine {
private:
    int id;         //id штрафа
    int reader_id;  //id читателя
    int amount;     //размер штрафа
    bool is_paid;   //оплачен ли штраф
    std::string reason;   //причина штрафа

public:
    Fine() : is_paid(false) {}

    ~Fine() {}

    //ввод штрафа
    void input(int reader_id) {
        this->reader_id = reader_id;

        std::cout << "[  Штраф  ]\n" << "Введите объем штрафа: ";
        std::cin >> amount;

        std::cout << "Введите id штрафа: ";
        std::cin >> id;
        std::cin.ignore();

        std::cout << "Причина штрафа: ";
        std::cin >> reason;
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

    //перегрузка "++" префиксно для переключения статуса оплаты
    Fine& operator++(){
        if (is_paid == true) is_paid = false;
        else is_paid = true;
        return *this;
    }

};

int Author::amount_of_authors = 0;

void show_id_to_bkcnt(const Author& smb) {
    std::cout << "Автор: " << smb.name << ";    id: " << smb.id << ";    Книг: " << smb.books_count << "\n";
}

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
        Gary[i].input(*Lary.getId());
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
