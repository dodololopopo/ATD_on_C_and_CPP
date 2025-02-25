#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include "prototypes.h"

//инициализация автора
void init_author(struct Author* author, int id, char* name, char* birthdate) {
	author->id = id;
	author->book_ids = (int*)calloc(1, sizeof(int));
	author->books_count = 0;
	author->name = (char*)malloc(strlen(name) + 1);
	strcpy(author->name, name);
	strcpy(author->birthdate, birthdate);
}


//инициализация книги
void init_book(struct Book* book, int id, int author_id, char* title, char* published_year) {
	book->id = id;
	book->is_available = 1;
	book->author_id = author_id;
	book->title = (char*)malloc(strlen(title) + 1);
	strcpy(book->title, title);
	strcpy(book->published_year, published_year);
}


//инициализация читателя
void init_reader(struct Reader* reader, int id, char* name, char* email) {
	reader->id = id;
	reader->borrowed_book_id = 0;
	reader->name = (char*)malloc(strlen(name) + 1);
	strcpy(reader->name, name);
	reader->email = (char*)malloc(strlen(email) + 1);
	strcpy(reader->email, email);
}


//инициализация запроса
void init_order(struct Order* order, int id, int reader_id, int book_id, char* orderdate) {
	order->id = id;
	order->reader_id = reader_id;
	order->book_id = book_id;
	strcpy(order->orderdate, orderdate);
	strcpy(order->returndate, "unreturned");
}


//инициализация штрафа
void init_fine(struct Fine* fine, int id, int reader_id, int amount, char* reason) {
	fine->id = id;
	fine->reader_id = reader_id;
	fine->amount = amount;
	fine->is_paid = 0;
	fine->reason = (char*)malloc(strlen(reason) + 1);
	strcpy(fine->reason, reason);
}


//ввод автора
void input_author(struct Author* author) {
	//вводим данные с последующей иницализацией с этими значениями
	char* name,
		birthdate[DDMMYYYY_LENTH];
	int id;
	puts("Добавление Автора");
	printf("Введите имя: ");
	name = (char*)malloc(25 * sizeof(char));
	fgets(name, 25, stdin);
	name[strlen(name) - 1] = '\0';

	printf("Введите дату рождения дд.мм.гггг: ");
	fgets(birthdate, DDMMYYYY_LENTH, stdin);
	birthdate[DDMMYYYY_LENTH - 1] = '\0';

	printf("Введите id автора: ");
	scanf("%d", &id);
	while (getchar() != '\n');
	puts("");

	init_author(author, id, name, birthdate);
}


//ввод книги
void input_book(struct Book* book, struct Author* creator) {
	//вводим данные с последующей иницализацией с этими значениями
	int id,
		* author_books_arr,
		i;
	char* title,
		published_year[5];
	puts("Добавление книги");
	printf("id автора: %06d\n", creator->id);

	printf("Введите название: ");
	title = (char*)malloc(25 * sizeof(char));
	fgets(title, 25, stdin);
	title[strlen(title) - 1] = '\0';

	printf("Введите год публикации: ");
	fgets(published_year, 5, stdin);
	published_year[4] = '\0';

	printf("Введите id книги: ");
	scanf("%d", &id);
	while (getchar() != '\n');

	//у книг всегда есть автор, значит новую созданную нужно добавить к автору
	creator->books_count += 1;
	author_books_arr = (int*)calloc(creator->books_count, sizeof(int));
	author_books_arr[0] = id;
	for (i = 1; i < creator->books_count; i++) {
		author_books_arr[i] = creator->book_ids[i - 1];
	}
	free(creator->book_ids);
	creator->book_ids = author_books_arr;
	puts("");

	init_book(book, id, creator->id, title, published_year);
}


//ввод читателя
void input_reader(struct Reader* reader) {
	//вводим данные с последующей иницализацией с этими значениями
	int id;
	char* name,
		* email;

	puts("Добавление Читателя");
	printf("Введите имя: ");
	name = (char*)malloc(25 * sizeof(char));
	fgets(name, 25, stdin);
	name[strlen(name) - 1] = '\0';

	printf("Введите email: ");
	email = (char*)malloc(35 * sizeof(char));
	fgets(email, 35, stdin);
	email[strlen(email) - 1] = '\0';

	printf("Введите id читателя: ");
	scanf("%d", &id);
	while (getchar() != '\n');
	puts("");

	init_reader(reader, id, name, email);
}


//ввод запроса
void input_order(struct Order* order, struct Book* taken, struct Reader* taker) {
	//вводим данные с последующей иницализацией с этими значениями
	int id;
	char orderdate[DDMMYYYY_LENTH];

	puts("Добавление Запроса");
	printf("id читателя: %06d\n", taker->id);

	printf("id книги: %06d\n", taken->id);

	printf("id запроса: ");
	scanf("%d", &id);
	while (getchar() != '\n');

	printf("дата запроса дд.мм.гггг: ");
	fgets(orderdate, DDMMYYYY_LENTH, stdin);
	orderdate[DDMMYYYY_LENTH - 1] = '\0';

	//с появлением запроса книга становится не доступной, это отмечается у читателя
	taken->is_available = 0;
	taker->borrowed_book_id = taken->id;
	puts("");

	init_order(order, id, taker->id, taken->id, orderdate);
}


//ввод штрафа
void input_fine(struct Fine* fine, struct Reader* fined) {
	//вводим данные с последующей иницализацией с этими значениями
	int id,
		amount;
	char* reason;

	puts("Добавление штрафа");
	printf("id читателя: %06d\n", fined->id);

	printf("объем штрафа: ");
	scanf("%d", &amount);

	printf("id штрафа: ");
	scanf("%d", &id);
	while (getchar() != '\n');

	printf("Причина штрафа: ");
	reason = (char*)malloc(sizeof(char) * 150);
	fgets(reason, 150, stdin);
	puts("");

	init_fine(fine, id, fined->id, amount, reason);
}