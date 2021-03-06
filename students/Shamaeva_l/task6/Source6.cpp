#include <iostream>
#include <string>
#include <locale>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class NumberGenerator {
private:
	int capacity;
public:
	NumberGenerator(int capacity) {
		this->capacity = capacity;
	}
	void doGenerate(char* A) {
		bool flag;
		srand(time(0));
		for (int i = 0; i < capacity; i++)
		{
			flag = false;
			A[i] = rand() % 10;
			do {
				for (int j = 0; j < i; j++)
				{
					if (A[j] == A[i]) {
						flag = true;
						A[i]++;
						if (A[i] == 10) A[i] = 0;
						break;
					}
					if (j == i - 1) flag = false;
				}
			} while (flag == true);
		}
	}
};

class Counter {
private:
	int capacity;
	char* original;
public:
	Counter(int capacity, char* original) {
		this->capacity = capacity;
		this->original = original;
	}

	void countBullsCows(char* userInput, int* bulls, int* cows) {
		for (int i = 0; i < capacity; i++)
		{
			if (original[i] == userInput[i] - '0')
			{
				(*bulls)++;
			}

			for (int j = 0; j < capacity; j++)
			{
				if (original[i] == userInput[j] - '0')
					(*cows)++;
			}
		}
	}
};

class Game {
private:
	int capacity;
public:
	Game(int capacity) {
		this->capacity = capacity;
	}

	void start() {
		int yes = 0;
		NumberGenerator gen(capacity);
		char* A = new char[capacity];
		gen.doGenerate(A);
		Counter counter(capacity, A);
		char* Ary = new char[capacity];
		while (yes != 1)
		{
			int bulls = 0;
			int cows = 0;
			cout << "Ваш вариант?" << endl;
			cin >> Ary;
			counter.countBullsCows(Ary, &bulls, &cows);
			if (bulls == capacity)
			{
				cout << endl;
				cout << "Поздравляю, вы выиграли!!!";
				cout << endl;
				yes = 1;
			}
			else {
				cout << endl;
				cout << bulls << " быков, " << cows - bulls << " коров!" << endl;
				bulls = 0;
				cows = 0;
			}
		}
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	int k = 1;
	int l;
	int m;
	int n;
	while (k == 1)
	{
		cout << "Добро пожаловать в игру \"Быки и коровы!\"" << endl;
		cout << "Выберите дальнейшие действия" << endl;
		cout << "1) Играть в увлекательную игру \"Быки и коровы!!\"" << endl;
		cout << "2) Выйти из программы." << endl;
		cout << "Ваш выбор: ";
		cin >> l;
		system("cls");
		switch (l)
		{
		case 1:
		{
			cout << "Хороший выбор!" << endl;
			cout << "Хотите ли вы вспомнить правила?" << endl;
			cout << "1) Да, конечно!" << endl;
			cout << "2)Нет, начну сразу играть." << endl;
			cout << "Ваш выбор:";
			cin >> m;
			system("cls");
			switch (m)
			{
			case 1:
			{
				cout << " Играют два игрока (человек и компьютер)" << endl;
				cout << "Игрок выбирает длину загадываемого числа – n." << endl;
				cout << "Компьютер «задумывает» n - значное число с неповторяющимися цифрами." << endl;
				cout << "Игрок делает попытку отгадать число – вводит n - значное число с неповторяющимися цифрами." << endl;
				cout << "Компьютер сообщает, сколько цифр угадано без совпадения с их позициями в загаданном числе(то есть количество коров) и сколько угадано вплоть до позиции в загаданном числе(то есть количество быков)." << endl;
				cout << "Игрок делает попытки, пока не отгадает всю последовательность." << endl;
				cout << "Удачи в игре!" << endl;
				cout << "Введите длину загадываемого числа:";
				cin >> n;
				Game game(n);
				game.start();
				cout << "Спасибо за игру!";
				_getch();
				system("cls");
				break;
			}
			case 2:
			{
				int n;
				cout << "Введите длину загадываемого числа: ";
				cin >> n;
				Game game(n);
				game.start();
				cout << "Спасибо за игру!";
				_getch();
				system("cls");
				break;
			}
			}
		}
		case 2:
		{
			exit(0);
			cout << "Спасибо за игру!";
			system("cls");
		}
		}
	}
}