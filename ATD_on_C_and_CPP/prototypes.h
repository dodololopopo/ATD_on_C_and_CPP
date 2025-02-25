#pragma once
#define DDMMYYYY_LENTH 11

struct Author {
    int id;
    int *book_ids;  //<-
    int books_count;
    char* name;
    char birthdate[DDMMYYYY_LENTH];
};

struct Book {
    int id;
    int is_available;   //<-
    int author_id;
    char *title;
    char published_year[5];
};

struct Reader {
    int id;
    int borrowed_book_id;  //<-
    char* name;
    char *email;
};

struct Order {
    int id;
    int reader_id;
    int book_id;
    char orderdate[DDMMYYYY_LENTH];
    char returndate[DDMMYYYY_LENTH];    //<-
};

struct Fine {
    int id;
    int reader_id;
    int amount;
    int is_paid;    //<-
    char *reason;
};


void init_author(struct Author* author, int id, char* name, char* birthdate);

void init_book(struct Book* book, int id, int author_id, char* title, char* published_year);

void init_reader(struct Reader* reader, int id, char* name, char* email);

void init_order(struct Order* order, int id, int reader_id, int book_id, char* orderdate);

void init_fine(struct Fine* fine, int id, int reader_id, int amount, char* reason);

void input_author(struct Author* author);

void input_book(struct Book *book, struct Author* creator);

void input_reader(struct Reader *reader);

void input_order(struct Order *order, struct Book* taken, struct Reader* taker);

void input_fine(struct Fine *fine, struct Reader* fined);

void output_author(struct Author *toprint);

void output_book(struct Book *toprint);

void output_reader(struct Reader *toprint);

void output_order(struct Order *toprint);

void output_fine(struct Fine *toprint);

void edit_book(struct Book *editable, int status);

void edit_order(struct Order* editable, const char* date_of_return, struct Reader* reader, struct Book* book);

void edit_fine(struct Fine *editable);
