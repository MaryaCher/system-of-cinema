// курсовая.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <io.h>
#include <string.h>

using namespace std;

struct Cinema {
	int date;
	char name[20];
	double time_nach;
	int duration;
	int freeplac;
};

void Create();
void Add();
void Viewing();
void Lin_Search();
void Sort();
void QuickSort();
void Dv_Search();
void Book();


int main()
{
	int ch;
	setlocale(LC_ALL, "RU");
	do {
		cout << "1. Создание\n2. Добавление\n3. Просмотр\n4. Линейный поиск по названию в файле\n5. Сортировка методом прямого выбора по дате\n6. Сортировка методом QuickSort по продолжительности сеанса\n7. Двоичный поиск по продолжительности\n8. Забронировать места\n0. Выход" << endl;
		cin >> ch;
		if (!cin) {
			cout << "Error!\n";
			return 1;
		}
		switch (ch) {
		case 1: Create(); break;
		case 2: Add(); break;
		case 3: Viewing(); break;
		case 4: Lin_Search(); break;
		case 5: Sort(); break;
		case 6: QuickSort(); break;
		case 7: Dv_Search(); break;
		case 8: Book(); break;
		case 0: cout << "Выход\n"; break;
		default: cout << "Error!" << endl; break;
		}
	} while (ch != 0);
	return 0;
}

void Create() {
	FILE* f;
	fopen_s(&f, "file.txt", "w+");
	if (f == NULL) {
		cout << "Файл не удалось открыть" << endl;
		return;
	}
	else cout << "Файл успешно создан" << endl;
	fclose(f);
	Add();
}

void Add() {
	FILE* f;
	fopen_s(&f, "file.txt", "ab");
	if (f == NULL) {
		cout << "Файл не удалось открыть" << endl;
		return;
	}
	else {
		int n;
		cout << "Введите количество фильмов в прокате\n";
		cin >> n;
		if (!cin) {
			cout << "Error!\n";
			return;
		}
		for (int i = 0; i < n; i++) {
			Cinema c;
			cout << "Введите название кинофильма\n";
			cin >> c.name;
			cout << "Введите дату сеанса (число)\n";
			cin >> c.date;
			cout << "Введите время начало сеанса\n";
			cin >> c.time_nach;
			cout << "Введите продолжительность сеанса\n";
			cin >> c.duration;
			cout << "Введите число свободных мест\n";
			cin >> c.freeplac;
			fwrite(&c, 1, sizeof(c), f);
			cout << endl;
		}
	}
	fclose(f);
}

void Viewing() {
	FILE* f;
	fopen_s(&f, "file.txt", "rb");
	if (f == NULL) {
		cout << "Файл не удалось открыть" << endl;
		return;
	}
	else {
		Cinema c;
		while (fread(&c, sizeof(c), 1, f))
		{
			printf("Название кинофильма: %s \nДата сеанса: %d\nВремя начала сеанса:% 4.2f\nПродолжительность сеанса:%d\nЧисло свободных мест:%d\n\n",c.name, c.date, c.time_nach,c.duration,c.freeplac);
		}
	}
	fclose(f);
}

	void Lin_Search() {
	FILE* f;
	fopen_s(&f, "file.txt", "rb");
	if (f == NULL) {
		cout << "Файл не удалось открыть" << endl;
		return;
	}
	else {
		Cinema c;
		char x[20]; int count=0, COunt=0;
		cout << "Введите название фильма" << endl;
		cin >> x;
		while (fread(&c, sizeof(c), 1, f)) {
			for (int i = 0; i < 20; i++)
			{
				if (c.name[i] == x[i])count++;
			}
			if (count == 20)
				printf("Название кинофильма: %s \nДата сеанса: %d\nВремя начала сеанса:% 4.2f\nПродолжительность сеанса:%d\nЧисло свободных мест:%d\n\n", c.name, c.date, c.time_nach, c.duration, c.freeplac);
			else COunt++;
		}
		if (COunt == _filelength(_fileno(f)) / sizeof(Cinema))cout << "Нет подходящих сеансов"<<endl;
	}
	fclose(f);
	}

void Sort() {
	FILE* f;
	fopen_s(&f, "file.txt", "rb");
	if (f == NULL) {
		cout << "Файл не удалось открыть" << endl;
		return;
	}
	else {
		int i, j, min;
		int kolvo = _filelength(_fileno(f)) / sizeof(Cinema);
	    Cinema* c = new Cinema[kolvo];
		Cinema t;
		fread(c, sizeof(Cinema), kolvo, f);
		for (i = 0; i < kolvo - 1; i++) {
			min = i;
			for (j = i + 1; j < kolvo; j++)
				if (c[j].date < c[min].date) min = j;
			if (min != i) {
				t = c[i];
				c[i] = c[min];
				c[min] = t;
			}
		}
		for (int i = 0; i < kolvo; i++)
		{
			printf("Название кинофильма: %s \nДата сеанса: %d\nВремя начала сеанса:% 4.2f\nПродолжительность сеанса:%d\nЧисло свободных мест:%d\n\n", c[i].name, c[i].date, c[i].time_nach, c[i].duration, c[i].freeplac);
		}
		delete[]c;
	}
	fclose(f);
}

void QuickSort() {
	FILE* f;
	fopen_s(&f, "file.txt", "rb");
	if (f == NULL) {
		cout << "Файл не удалось открыть" << endl;
		return;
	}
	else {
		int kolvo = _filelength(_fileno(f)) / sizeof(Cinema);
		Cinema* c = new Cinema[kolvo];
		fread(c, sizeof(Cinema), kolvo, f);
		struct
		{
			int l;
			int r;
		} stack[20];
		int i, j, left, right, a = 0;
		Cinema t, x;
		stack[a].l = 0; stack[a].r = kolvo - 1;
		while (a != -1)
		{
			left = stack[a].l; right = stack[a].r;
			a--;
			while (left < right)
			{
				i = left; j = right; x = c[(left + right) / 2];
				while (i <= j)
				{
					while (c[i].duration < x.duration) i++;
					while (c[j].duration > x.duration) j--;
					if (i <= j) {
						t = c[i]; c[i] = c[j]; c[j] = t;
						i++; j--;
					}
				}

				if ((j - left) < (right - i))
				{
					if (i < right) {
						a++;
						stack[a].l = i;
						stack[a].r = right;
					}
					right = j;
				}
				else {
					if (left < j) {
						a++;
						stack[a].l = left;
						stack[a].r = j;
					}
					left = i;
				}
				}
				}
				for (int i = 0; i < kolvo; i++)
				{
				printf("Название кинофильма: %s \nДата сеанса: %d\nВремя начала сеанса:% 4.2f\nПродолжительность сеанса:%d\nЧисло свободных мест:%d\n\n", c[i].name, c[i].date, c[i].time_nach, c[i].duration, c[i].freeplac);
				}
				delete[]c;
				}
				fclose(f);
				}

void Dv_Search() {
	FILE* f;
	fopen_s(&f, "file.txt", "rb");
	if (f == NULL) {
		cout << "Файл не удалось открыть" << endl;
		return;
	}
	else {
		int kolvo = _filelength(_fileno(f)) / sizeof(Cinema);
		cout << "Введите продолжительность фильма" << endl;
		double x;
		cin >> x;
		Cinema* c = new Cinema[kolvo];
		Cinema t;
		fread(c, sizeof(Cinema), kolvo, f);
		int i, j, min, count = 0;
		for (i = 0; i < kolvo - 1; i++) {
			min = i;
			for (j = i + 1; j < kolvo; j++)
				if (c[j].duration < c[min].duration) min = j;
			if (min != i) {
				t = c[i];
				c[i] = c[min];
				c[min] = t;
			}
		}

		i = 0;
		j = kolvo - 1;
		while (i <= j) {
			int sr = (i + j) / 2;
			if (c[sr].duration < x)
				i = sr + 1;
			else if (c[sr].duration > x)
				j = sr - 1;
			else {
				printf("Название кинофильма: %s \nДата сеанса: %d\nВремя начала сеанса:% 4.2f\nПродолжительность сеанса:%d\nЧисло свободных мест:%d\n\n", c[sr].name, c[sr].date, c[sr].time_nach, c[sr].duration, c[sr].freeplac);
				break;
			}
		}

		if (i > j)
			cout << "Нет подходящих сеансов" << endl;
		delete[] c;
	}

	fclose(f);
}
void Book() {
	FILE* f;
	fopen_s(&f, "file.txt", "rb");
	if (f == NULL) {
		cout << "Файл не удалось открыть" << endl;
		return;
	}
	else {
		Cinema c;
		int count = 0; int dat=0, sit=0, pl=0; double tim=0;
		cout << "Введите дату сегодня" << endl;
		cin >> dat;
		cout << "Введите дату сеанса" << endl;
		cin >> sit;
		cout << "Введите самое позднее время сеанса" << endl;
		cin >> tim;
		cout << "Введите количество мест для резервации" << endl;
		cin >> pl;
		while (fread(&c, sizeof(c), 1, f)) {

			if (dat < sit && tim >= c.time_nach && pl <= c.freeplac)
			{
				c.freeplac -= pl;
				printf("Название кинофильма: %s \nДата сеанса: %d\nВремя начала сеанса:% 4.2f\nПродолжительность сеанса:%d\n\n", c.name, c.date, c.time_nach, c.duration);
				count++;
			}
			
		}
		if(count==0) cout << "Невозможно сделать заказ" << endl;
		fclose(f);
	}
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
