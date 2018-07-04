#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

#define SIZE 5

#define _CRT_SECURE_NO_WARNINGS

typedef struct{
	char date[30];
	int temperature;
	float inaccuracy;
}block;

typedef struct list{
	int number;
	block data[SIZE];
	struct list* prev;
	struct list* next;
}list;

int menu(){
	int i;
	char *s[12] = {
		"1. Добавление новой записи в начало списка.",
		"2. Добавление новой записи в конец списка.",
		"3. Вставка новой записи на заданную позицию.",
		"4. Удаление записи, находящейся на заданной позиции.",
		"5. Изменение записи, находящейся на заданной позиции.",
		"6. Поиск.",
		"7. Очиска.",
		"8. Вывод на экран.",
		"9. Вывод служебных данных и текущей структуры используемой структуры хранения.",
		"10. Чтение данных из файла.",
		"11. Запись данных в файл.",
		"12. Завершить работу."
	};
	for (i = 0; i < 12; i++){
		printf("%s\n", s[i]);
	}
	printf("----------------\n");
	return 0;
}

int display(list* a){
	int i;
	int count = 1;
	if (a == NULL) {
		fprintf(stderr, "Ошибка. Элементы отсутствуют.\n");
		return 0;
	}
	do{
		for (i = 0; i < a->number; i++){
			if (count >= 10) printf("%d. ", count);
			else if (count<10) printf("%d.  ", count);
			printf("Дата измерения:");
			printf("%s    ", a->data[i].date);
			printf("Погрешность:");
			printf("%.2f   ", a->data[i].inaccuracy);
			printf("Температура:");
			printf("%d\n", a->data[i].temperature);
			count++;
		}
		a = a->next;
	} while (a != NULL);
	putchar('\n');
	return 0;
}

int creation_node(list** a){
	(*a) = (list*)malloc(sizeof(list));
	(*a)->next = NULL;
	(*a)->prev = NULL;
	(*a)->number = 0;
	return 0;
}

int fill(list* a, int pos){
	char string[30];
	printf("Дата измерения:");
	fgets(a->data[pos].date, 30, stdin);
	a->data[pos].date[strlen(a->data[pos].date) - 1] = '\0';
	printf("Погрешность:");
	fgets(string, 30, stdin);
	sscanf_s(string, "%f", &a->data[pos].inaccuracy);
	printf("Температура:");
	fgets(string, 30, stdin);
	a->data[pos].temperature = atoi(string);
	a->number = a->number + 1;
	printf("-----------------\n");
	return 0;
}

int offset_elem_in_node(list** a){
	int i;
	for (i = (*a)->number; i>0; i--){
		strncpy((*a)->data[i].date, (*a)->data[i - 1].date, sizeof((*a)->data[i].date) - 1);
		(*a)->data[i].date[sizeof((*a)->data[i].date) - 1] = '\0';
		(*a)->data[i].inaccuracy = (*a)->data[i - 1].inaccuracy;
		(*a)->data[i].temperature = (*a)->data[i - 1].temperature;
	}
	return 0;
}

int partial_offset_in_node(list* a, int start){
	int i;
	for (i = a->number; i >= start; i--){
		strncpy(a->data[i].date, a->data[i - 1].date, sizeof(a->data[i].date) - 1);
		a->data[i].date[sizeof(a->data[i].date) - 1] = '\0';
		a->data[i].inaccuracy = a->data[i - 1].inaccuracy;
		a->data[i].temperature = a->data[i - 1].temperature;
	}
	return 0;
}

int reverse_partial_offset_in_node(list* a, int start){
	int i;
	for (i = start; i < a->number - 1; i++){
		strncpy(a->data[i].date, a->data[i + 1].date, sizeof(a->data[i].date) - 1);
		a->data[i].date[sizeof(a->data[i].date) - 1] = '\0';
		a->data[i].inaccuracy = a->data[i + 1].inaccuracy;
		a->data[i].temperature = a->data[i + 1].temperature;
	}
	a->number--;
	return 0;
}

int transfer_elem(list* a, list* b){
	strncpy(a->data[0].date, b->data[4].date, sizeof(a->data[0].date) - 1);
	a->data[0].date[sizeof(a->data[0].date) - 1] = '\0';
	a->data[0].inaccuracy = b->data[4].inaccuracy;
	a->data[0].temperature = b->data[4].temperature;
	a->number++;
	b->number--;
	return 0;
}

int go_to_end(list** a){
	int count = 1;
	while ((*a)->next != NULL){
		(*a) = (*a)->next;
		count++;
	}
	return count;
}

int go_to_start(list** a){
	int count = 1;
	while ((*a)->prev != NULL){
		(*a) = (*a)->prev;
		count++;
	}
	return count;
}

int num_node_in_list(list** a){
	int count = 1;
	list* b = (*a);
	while (b->next != NULL){
		b = b->next;
		count++;
	}
	return count;
}

int num_elem_in_list(list** a){
	list* b = (*a);
	int count = 0;
	do{
		count = count + b->number;
		b = b->next;
	} while (b != NULL);
	return count;
}

int change_elem_in_node(list* a, int position){
	char string[30];
	printf("Новая дата измерения:");
	fgets(a->data[position].date, 30, stdin);
	a->data[position].date[strlen(a->data[position].date) - 1] = '\0';
	printf("Новая погрешность:");
	fgets(string, 30, stdin);
	sscanf_s(string, "%f", &a->data[position].inaccuracy);
	printf("Новая температура:");
	fgets(string, 30, stdin);
	a->data[position].temperature = atoi(string);
	printf("-----------------\n");
	return 0;
}

int add_new_elem_in_start(list** a){
	int num_elem = 0;
	list* b = NULL;
	list* a2 = NULL;
	if ((*a) == NULL){
		creation_node(a);
	}
	if ((*a)->number < 5){
		offset_elem_in_node(a);
		fill((*a), 0);
		return 0;
	}
	if ((*a)->number == 5){
		if ((*a)->next){
			if ((*a)->next->number < 5){
				offset_elem_in_node(&(*a)->next);
				transfer_elem((*a)->next, (*a));
				offset_elem_in_node(a);
				fill((*a), 0);
				return 0;
			}
			if ((*a)->next->number == 5){
				creation_node(&b);
				b->next = ((*a)->next);
				(*a)->next = b;
				b->prev = (*a);
				transfer_elem(b, (*a));
				offset_elem_in_node(a);
			}
		}
		if ((*a)->next == NULL){
			creation_node(&b);
			(*a)->next = b;
			b->prev = (*a);
			transfer_elem(b, (*a));
			offset_elem_in_node(a);
		}
	}
	fill((*a), 0);
	return 0;
}

int add_new_elem_in_end(list** a){
	list* b = NULL;
	if ((*a) == NULL){
		creation_node(a);
	}
	go_to_end(a);
	if ((*a)->number < 5) {
		fill((*a), (*a)->number);
		go_to_start(a);
	}
	else if ((*a)->number == 5){
		creation_node(&b);
		(*a)->next = b;
		b->prev = (*a);
		(*a) = (*a)->next;
		fill((*a), 0);
		go_to_start(a);
	}
	return 0;
}

int add_new_elem_number(list** a){
	int number = 0, count = 0;
	char s[5];
	list* b = (*a);
	list* c = NULL;
	printf("Введите номер записи:");
	fgets(s, 5, stdin);
	number = atoi(s);
	count = num_elem_in_list(a);
	printf("-----------------\n");
	if (number <= 0 || number > count + 1){
		fprintf(stderr, "Недопустимое значение.\n");
		return 0;
	}
	if (number == 1) add_new_elem_in_start(a);
	if (number == count + 1) add_new_elem_in_end(a);
	if (number>1 && number <= count){
		while (number > b->number){
			number = number - b->number;
			b = b->next;
		}
		if (b->number < 5){
			partial_offset_in_node(b, number - 1);
			fill(b, number - 1);
			return 0;
		}
		if (b->number == 5){
			if (b->next->number == 5){
				creation_node(&c);
				c->next = b->next;
				c->prev = b;
				b->next = c;
				transfer_elem(c, b);
				partial_offset_in_node(b, number - 1);
				fill(b, number - 1);
				return 0;
			}
			if (b->next->number < 5){
				offset_elem_in_node(&b->next);
				transfer_elem(b->next, b);
				partial_offset_in_node(b, number - 1);
				fill(b, number - 1);
			}
		}
	}
	return 0;
}

int del_elem(list** a){
	int  count = 0, number, count_b = 1, number_node;
	char s[5];
	list* b = (*a);
	if ((*a) == NULL){
		fprintf(stderr, "Нет элементов для удаления.\n");
		return 0;
	}
	printf("Введите номер записи:");
	fgets(s, 5, stdin);
	count = atoi(s);
	number = num_elem_in_list(a);
	number_node = num_node_in_list(a);
	if (count <= 0 || count > number){
		fprintf(stderr, "Недопустимое значение.\n");
		return 0;
	}
	while (count > b->number){
		count = count - b->number;
		b = b->next;
	}
	reverse_partial_offset_in_node(b, count - 1);
	if (b->number == 0) {
		if (b->prev == NULL && b->next == NULL){
			(*a) = NULL;
			return 0;
		}
		if (b->prev != NULL && b->next != NULL) {
			b->prev->next = b->next;
			b->next->prev = b->prev;
		}
		if (b->prev == NULL && b->next != NULL){
			(*a) = b->next;
			(*a)->prev = NULL;
		}
		if (b->prev != NULL && b->next == NULL){
			b->prev->next = NULL;
		}
		b->prev = NULL;
		free(b);
		return 0;
	}
	return 0;
}

int change_elem(list* a){
	char s[5];
	int  count;
	int number_elem;
	list* b = a;
	if (a == NULL){
		fprintf(stderr, "Нет элементов для изменения.\n");
		return 0;
	}
	printf("Введите номер записи:");
	fgets(s, 5, stdin);
	count = atoi(s);
	number_elem = num_elem_in_list(&a);
	if (count <= 0 || count > number_elem){
		fprintf(stderr, "Недопустимое значение.\n");
		return 0;
	}
	while (count > b->number){
		count = count - b->number;
		b = b->next;
	}
	change_elem_in_node(b, count - 1);
	return 0;
}

list* list_free(list* a){
	if (a){
		list_free(a->next);
		free(a);
	}
	return NULL;
}

int display_elem(list* a, int index, int number){
	printf("%d. ", number);
	printf("Дата измерения:");
	printf("%s   ", a->data[index].date);
	printf("Погрешность:");
	printf("%.2f    ", a->data[index].inaccuracy);
	printf("Температура:");
	printf("%d\n", a->data[index].temperature);
	return 0;
}

int search(list* a, int value, int number){
	int i;
	int num_elem = 0;
	if (a){
		for (i = 0; i < a->number; i++){
			if (value == a->data[i].temperature) {
				num_elem++;
				display_elem(a, i, number + i + 1);
			}
		}
		number = number + a->number;
		num_elem = num_elem + search(a->next, value, number);
	}
	return num_elem;
}

int search_elem(list* a){
	char s[5];
	int count = 0, number_elem = 0;
	if (a == NULL){
		fprintf(stderr, "Нет элементов для изменения.\n");
		return 0;
	}
	printf("Введите искомое значение температуры:");
	fgets(s, 5, stdin);
	count = atoi(s);
	number_elem = search(a, count, 0);
	printf("-----------------\n");
	printf("Всего найдено элементов:%d\n", number_elem);
	printf("-----------------\n");
	return 0;
}

int create_several_node(list** a, int num_node){
	int i;
	list* b = NULL;
	if ((*a) != NULL) list_free((*a));
	creation_node(a);
	for (i = 1; i < num_node; i++){
		creation_node(&b);
		(*a)->next = b;
		b->prev = (*a);
		(*a) = (*a)->next;
	}
	go_to_start(a);
	return 0;
}

int service_data(list** a){
	int num_node = 0, num_elems = 0,i;
	float count = 0;
	list* b = (*a);
	if ((*a) == NULL){
		fprintf(stderr, "Нет данных для обработки.\n");
		printf("-----------------------\n");
		return 0;
	}
	num_node = num_node_in_list(a);
	num_elems = num_elem_in_list(a);
	printf("№ блока:\tКоличество элементов:\tПроцент заполненности:\n");
	for (i = 0; i < num_node; i++){
		count = ((float)b->number / 5) * 100;
		printf("  %d\t\t\t%d\t\t\t%.2f\n", i + 1, b->number, count);
		b = b->next;
	}
	putchar('\n');
	count = (num_elems / (float)(5 * num_node)) * 100;
	printf("В списке %d блока(ов), в которых находятся %d элементов\n", num_node, num_elems);
	printf("Общий процент заполненность: %.2f%\n", count);
	printf("Всего занято места в памяти:%d байт\n", num_node*sizeof(list));
	printf("Каждый узел занимает места в памяти:%d байт\n", sizeof(list));
	printf("Каждый блок занимает места в памяти:%d байт\n", 5*sizeof(block));
	printf("-----------------------\n");
	return 0;
}

int read_file(list** a){
	int i = 0, i1;
	char name_file[50];
	int num_node;
	int count = 5;

	printf("Введите путь к файлу:");
	fgets(name_file, 50, stdin);
	name_file[strlen(name_file) - 1] = '\0';
	FILE* file = fopen(name_file, "rb");
	if (name_file == NULL){
		fprintf(stderr, "Ошибка! Не удалось открыть файл.\n");
		printf("-----------------------\n");
		return 0;
	}
	fread(&num_node, sizeof(int), 1, file);
	create_several_node(a, num_node);
	list* b = (*a);
	for (i = 1; i <= num_node; i++){
		fread(&b->number, sizeof(int), 1, file);
		for (i1 = 0; i1 < b->number; i1++){
			fread(&b->data[i1].date, 1, 30, file);
			fread(&b->data[i1].temperature, sizeof(int), 1, file);
			fread(&b->data[i1].inaccuracy, sizeof(float), 1, file);
		}
		b = b->next;
	}
	fclose(file);
	return 0;
}

int write_file(list** a){
	int i = 0, i1;
	char name_file[50];
	int num_node = 0, num_elems = 0;
	list* b = (*a);
	if ((*a) == NULL){
		fprintf(stderr, "Нет данных для обработки.\n");
		printf("-----------------------\n");
		return 0;
	}
	printf("Введите путь к файлу:");
	fgets(name_file, 50, stdin);
	name_file[strlen(name_file) - 1] = '\0';
	FILE* file = fopen(name_file, "wb");
	if (name_file == NULL){
		fprintf(stderr, "Ошибка! Не удалось открыть файл.\n");
		printf("-----------------------\n");
		return 0;
	}
	num_node = num_node_in_list(a);
	num_elems = num_elem_in_list(a);
	fwrite(&num_node, sizeof(int), 1, file);
	for (i = 1; i <= num_node; i++){
		fwrite(&b->number, sizeof(int), 1, file);
		for (i1 = 0; i1 < b->number; i1++){
			fwrite(&b->data[i1].date, 1, 30, file);
			fwrite(&b->data[i1].temperature, sizeof(int), 1, file);
			fwrite(&b->data[i1].inaccuracy, sizeof(float), 1, file);
		}
		b = b->next;
	}
	fclose(file);
	return 0;
}

int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int count = 0;
	char s[5];
	list* start = NULL;
	menu();
	while (count != 12){
		printf("Введите команду:");
		fgets(s, 5, stdin);
		printf("-----------------\n");
		count = atoi(s);
		switch (count){
		case 1:
		{
				  add_new_elem_in_start(&start);
				  break;
		}
		case 2:
		{
				  add_new_elem_in_end(&start);
				  break;
		}
		case 3:
		{
				  add_new_elem_number(&start);
				  break;
		}
		case 4:
		{
				  del_elem(&start);
				  break;
		}
		case 5:
		{
				  change_elem(start);
				  break;
		}
		case 6:
		{
				  search_elem(start);
				  break;
		}
		case 7:
		{
				  start = list_free(start);
				  break;
		}
		case 8:
		{
				  display(start);
				  break;
		}
		case 9:
		{
				  service_data(&start);
				  break;
		}
		case 10:
		{
				   read_file(&start);
				   break;
		}
		case 11:
		{
				   write_file(&start);
				   break;
		}
		case 12:
		{
				   start = list_free(start);
				   break;
		}
		default:
			fprintf(stderr, "Нет такой команды.\n");
			break;
		}
	}
	system("pause");
	return 0;
}

