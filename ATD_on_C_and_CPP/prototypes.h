#pragma once
#define DDMMYYYY_LENTH 10

struct Author {
    int id, *book_ids;
    char name, birthdate[DDMMYYYY_LENTH];
};

struct Book {
    int id, is_available;
    char title, author_id, published_year[4];
};

struct Reader {
    int id, *borrowed_books_ids;
    char name, email;
};

struct Order {
    int id, reader_id, book_id;
    char orderdate[DDMMYYYY_LENTH], returndate[DDMMYYYY_LENTH];
};

struct Fine {
    int id, reader_id, amount, is_paid;
    char *reason;
};