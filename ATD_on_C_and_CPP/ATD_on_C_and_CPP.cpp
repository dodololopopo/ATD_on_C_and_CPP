#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstdlib>
#include <locale>
#include <vector>
#include <algorithm>
#define DDMMYYYY_LENTH 11


class Sortable {
public:
    virtual std::string get_published_year() const = 0;
    virtual std::string get_title() const = 0;
    virtual ~Sortable() = default;
};

template <typename T>
class Collection {
private:
    std::vector<std::shared_ptr<T>> items; // Вектор для хранения элементов коллекции

public:
    // Добавление элемента в коллекцию
    void add(std::shared_ptr<T> item) {
        items.push_back(item);
    }

    // Вывод всех элементов коллекции
    void output() const {
        for (const auto& item : items) {
            item->output();
        }
    }

    // Переопределение оператора <<
    friend std::ostream& operator<<(std::ostream& os, const Collection<T>& collection) {
        for (const auto& item : collection.items) {
            os << item; // Используем оператор << для каждого элемента
        }
        return os;
    }
    void sortByPublishedYear() {
        std::sort(items.begin(), items.end(), [](const std::shared_ptr<T>& a, const std::shared_ptr<T>& b) {
            return a->get_published_year() < b->get_published_year();
            });
    }

    std::shared_ptr<T> findByTitle(const std::string& title) {
        auto it = std::find_if(items.begin(), items.end(), [&title](const std::shared_ptr<T>& book) {
            return book->get_title() == title;
            });
        if (it != items.end()) {
            return *it;
        }
        return nullptr;
    }
};

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
        try {
            std::cout << "[  Автор  ]\n" << "Введите имя: ";
            std::cin >> name;

            std::cout << "Введите дату рождения дд.мм.гггг: ";
            std::cin >> birthdate;

            std::cout << "Введите id автора: ";
            std::cin >> id;
            if (std::cin.fail()) {
                throw std::runtime_error("Ошибка: ID должен быть числом. Повторите ввод: ");
            }
            else if (id < 1) {
                throw std::runtime_error("Ошибка: ID должен быть положительным числом. Повторите ввод: ");
            }
            std::cin.ignore();
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear(); // Сброс состояния потока
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            std::cin >> id;
        }
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
        if (book_id < 0) {
            throw std::runtime_error("Ошибка: ID книги не может быть отрицательным.");
        }
        books_count++;
        book_ids = (int*)realloc(book_ids, books_count * sizeof(int));
        if (!book_ids) {
            throw std::runtime_error("Ошибка: Не удалось выделить память для ID книг.");
        }
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

    // Переопределение оператора <<
    friend std::ostream& operator<<(std::ostream& os, const Author& author) {
        os << "Автор:\n";
        os << "  Имя - " << author.name << "\n";
        os << "  Дата рождения - " << author.birthdate << "\n";
        os << "  ID автора - " << author.id << "\n";
        if (author.books_count) {
            os << "  ID книг:\n";
            for (int i = 0; i < author.books_count; i++) {
                os << "    - " << author.book_ids[i] << "\n";
            }
        }
        else {
            os << "  Нет книг от данного автора\n";
        }
        return os;
    }
};


class Literature {
public:
    virtual void update_lib() const = 0;
};

class Book : public Literature, public Sortable{
protected:
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
        try {
            this->author_id = author_id;

            std::cout << "[  Книга  ]\n" << "Введите название: ";
            std::getline(std::cin, title);

            std::cout << "Введите год публикации: ";
            std::cin >> published_year;

            std::cout << "Введите id книги: ";
            std::cin >> id;
            if (std::cin.fail()) {
                throw std::runtime_error("Ошибка: ID должен быть числом. Повторите ввод: ");
            }
            else if (id < 1) {
                throw std::runtime_error("Ошибка: ID должен быть положительным числом. Повторите ввод: ");
            }
            std::cin.ignore();
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear(); // Сброс состояния потока
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
        }
    }

    //вывод книги
    virtual void output() const {
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

    std::string get_title() const override{
        return title;
    }
    
    std::string get_published_year() const override {
        return published_year;
    }

    bool get_avaliability() {
        return is_available;
    }

    int get_author_id() {
        return author_id;
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

    virtual void display() {
        std::cout << "Книга: " << title << "\n\n";
    }

    void update_lib() const override {
        std::cout << "== Библиотека обновлена ==\n";
        std::cout << "Причина: добавлена книга\n\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << "Книга:\n";
        os << "  Название - " << book.title << "\n";
        os << "  Год публикации - " << book.published_year << "\n";
        os << "  ID книги - " << book.id << "\n";
        os << "  ID автора - " << book.author_id << "\n";
        os << "  Статус - " << (book.is_available ? "Доступна" : "Не доступна") << "\n";
        return os;
    }
};

class EBook : public Book {
private:
    std::string file_format; // формат файла (например, PDF, EPUB)
    double file_size;        // размер файла в мегабайтах

public:
    EBook() : Book(), file_size(0.0), file_format("-") {}

    // Ввод данных для электронной книги
    void input(int author_id) {
        Book::input(author_id); // Вызов метода ввода из базового класса
        std::cout << "Введите формат файла (например, PDF, EPUB): ";
        std::cin >> file_format;

        std::cout << "Введите размер файла (в МБ): ";
        std::cin >> file_size;
    }

    //перегрузка функции вывода с методом базового класса и без
    void output() const override {
        Book::output(); // Вызов метода вывода из базового класса
        std::cout << "  Формат файла - " << file_format << "\n";
        std::cout << "  Размер файла - " << file_size << " МБ\n\n";
    }
    
    void output(std::string) {
        std::cout << "[ Книга ]\n";
        std::cout << "  Название - " << title << "\n";
        std::cout << "  Формат файла - " << file_format << "\n";
        std::cout << "  Размер файла - " << file_size << " МБ\n\n";
    }

    EBook& operator=(Book& other){
        id = other.getId();
        is_available = other.get_avaliability();
        author_id = other.get_author_id();
        title = other.get_title();
        published_year = other.get_published_year();
        return *this;
    }

    void display() override {
        std::cout << "Электронная книга: " << title << ", Формат: " << file_format << "\n\n";
    }


    // Переопределение оператора <<
    friend std::ostream& operator<<(std::ostream& os, const EBook& ebook) {
        os << static_cast<const Book&>(ebook); // Вызов оператора << для базового класса
        os << "  Формат файла - " << ebook.file_format << "\n";
        os << "  Размер файла - " << ebook.file_size << " МБ\n";
        return os;
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
        try {
            std::cout << "[  Читатель  ]\n" << "Введите имя: ";
            std::cin >> name;

            std::cout << "Введите email: ";
            std::cin >> email;

            std::cout << "Введите id читателя: ";
            std::cin >> id;
            if (std::cin.fail()) {
                throw std::runtime_error("Ошибка: ID должен быть числом. Повторите ввод: ");
            }
            else if (id < 1) {
                throw std::runtime_error("Ошибка: ID должен быть положительным числом. Повторите ввод: ");
            }
            std::cin.ignore();
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear(); // Сброс состояния потока
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            std::cin >> id;
        }
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

    // Переопределение оператора <<
    friend std::ostream& operator<<(std::ostream& os, const Reader& reader) {
        os << "Читатель:\n";
        os << "  Имя - " << reader.name << "\n";
        os << "  Почта - " << reader.email << "\n";
        os << "  ID читателя - " << reader.id << "\n";
        os << "  ID занятой книги - ";
        if (reader.borrowed_book_id == 0) os << "Книг не занято" << "\n";
        else os << reader.borrowed_book_id << "\n";
        return os;
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

        try {
            std::cout << "[  Запрос  ]\n" << "Введите id запроса: ";
            std::cin >> id;
            if (std::cin.fail()) {
                throw std::runtime_error("Ошибка: ID должен быть числом. Повторите ввод: ");
            }
            else if (id < 1) {
                throw std::runtime_error("Ошибка: ID должен быть положительным числом. Повторите ввод: ");
            }
            std::cin.ignore();

            std::cout << "Дата запроса дд.мм.гггг: ";
            std::cin >> orderdate;
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear(); // Сброс состояния потока
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            std::cin >> id;
        }
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

    // Переопределение оператора <<
    friend std::ostream& operator<<(std::ostream& os, const Order& order) {
        os << "Запрос:\n";
        os << "  ID запроса - " << order.id << "\n";
        os << "  ID книги - " << order.book_id << "\n";
        os << "  ID читателя - " << order.reader_id << "\n";
        os << "  Дата запроса - " << order.orderdate << "\n";
        os << "  Дата возврата - " << order.returndate << "\n";
        return os;
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

        try {
            std::cout << "[  Штраф  ]\n" << "Введите объем штрафа: ";
            std::cin >> amount;

            std::cout << "Введите id штрафа: ";
            std::cin >> id;
            if (std::cin.fail()) {
                throw std::runtime_error("Ошибка: ID должен быть числом. Повторите ввод: ");
            }
            else if (id < 1) {
                throw std::runtime_error("Ошибка: ID должен быть положительным числом. Повторите ввод: ");
            }
            std::cin.ignore();

            std::cout << "Причина штрафа: ";
            std::cin >> reason;
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear(); // Сброс состояния потока
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            std::cin >> id;
        }
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


    // Переопределение оператора <<
    friend std::ostream& operator<<(std::ostream& os, const Fine& fine) {
        os << "Штраф:\n";
        os << "  ID штрафа - " << fine.id << "\n";
        os << "  ID читателя - " << fine.reader_id << "\n";
        os << "  Объем штрафа - " << fine.amount << " $\n";
        os << "  Статус  - " << (fine.is_paid ? "Оплачен" : "Не оплачен") << "\n";
        os << "  Причина - " << fine.reason << "\n";
        return os;
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
    std::cout << Lary;

    std::cout << "\n\n" << "Число книг от данного автора: " << Lary.get_books_count() << "\n\n";

    show_id_to_bkcnt(Lary);

    //демонстрация дружественной функции
    Lary.increment();
    Author::show_amount_of_authors();


    //демонстрация работы с абстрактым классом
    Literature* liblib = new Book;
    liblib->update_lib();
    delete liblib;


    //демонстрация работы с шаблоном класса
    Collection<Book> CollectBooks;

    //демонстрация сортировки и поиска
    auto a = std::make_shared<Book>();
    auto b = std::make_shared<Book>();
    auto c = std::make_shared<EBook>();

    a->input(*Lary.getId());
    b->input(*Lary.getId());
    c->input(*Lary.getId());

    CollectBooks.add(a);
    CollectBooks.add(b);
    CollectBooks.add(c);

    CollectBooks.output();
    std::cout << "Сортируем список:\n";
    CollectBooks.sortByPublishedYear();
    CollectBooks.output();
    
    std::cout << "\nПоиск книги\nВведите название:";
    std::string searchtitle;
    std::cin.ignore();
    std::getline(std::cin, searchtitle);
    CollectBooks.findByTitle(searchtitle)->output();

    //демонстрация с производным классом
    auto Eb = std::make_shared<EBook>();
    Eb->input(*Lary.getId());
    CollectBooks.add(Eb);
    Lary.addBook(Eb->getId());
    Eb->output();
    Eb->output("shorter");


    //перегрузка опреатора "="
    auto Book_for_Eb = std::make_shared<EBook>();
    Book_for_Eb->input(*Lary.getId());
    CollectBooks.add(Book_for_Eb);
    Lary.addBook(Book_for_Eb->getId());
    std::cout << Eb;
    Eb = Book_for_Eb;
    std::cout << Eb;
    std::cout << "\n\nСписок книг:\n";
    std::cout << CollectBooks;


    //демонстрация с виртуальными функциями
    Book* book = new EBook();
    book->input(*Lary.getId());
    book->display();

    Book baseBook;
    EBook eBook;
    baseBook.input(*Lary.getId());
    eBook.input(*Lary.getId());
    baseBook = eBook;
    baseBook.display();



    std::cout << "Солько добавить книг?: ";
    std::cin >> hwmnybooks;
    std::cin.ignore();
    if (hwmnybooks < 2) hwmnybooks = 2;

    //работа с одномерным массивом
    Book* Gary = new Book[hwmnybooks];
    for (int i = 0; i < hwmnybooks; ++i) {
        std::cout << "N" << (i + 1) << ": ";
        Gary[i].input(*Lary.getId());
        Lary.addBook(Gary[i].getId()); // Добавление книги к автору
    }

    std::cout << "\n\n" << "Число книг от данного автора: " << Lary.get_books_count() << "\n\n";

    // Вывод данных всех книг
    for (int i = 0; i < hwmnybooks; ++i) {
        std::cout << Gary[i];
    }
    std::cout << Lary;

    Book DuoGary;
    DuoGary = Gary[0] + Gary[1];    //демонстрация перегрузки, создающей дилогию
    std::cout << DuoGary;
    DuoGary++;              //демонстрация перегрузки, преключающей статус доступности
    std::cout << DuoGary;

    Author Lary2;
    Lary2.input();
    std::cout << Lary2;

    //демонстрация дружественной функции
    Lary2.increment();
    Author::show_amount_of_authors();



    //работа с двумерным массивом
    Reader reader[2];
    Fine fine[2][2];
    for (int i = 0; i < 2; ++i) {
        reader[i].input();
        for (int j = 0; j < 2; ++j) {
            fine[i][j].input(reader[i].getId());
        }
    }

    for (int i = 0; i < 2; ++i) {
        std::cout << reader[i];
        for (int j = 0; j < 2; ++j) {
            std::cout << fine[i][j];
        }
    }

    // Пример редактирования штрафа
    fine[0][0].edit();
    std::cout << fine[0][0];

    ++fine[0][1];
    std::cout << fine[0][1];  //демонстрация перегрузки, переключающей статус "оплачено"

    Order Pery;
    Pery.input(reader[0].getId(), Gary->getId());
    std::cout << Pery;

    // Пример редактирования заказа
    Pery.edit("21.11.2121");
    std::cout << Pery;

    // Освобождение памяти
    delete[] Gary;

    return 0;
}