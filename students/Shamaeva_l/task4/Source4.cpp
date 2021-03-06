#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <ctime>
using namespace std;
struct dateWhenItWasReached
{
	/* Структура необходима в дальнейшем дляхранения и вывода начальной даты
	подсчёта и для даты, когда было достигнуто максимальное число шагов.
	*/
	int endDay;
	int endMonth;
	int endYear;
};

class Pedometer
{
public:
	int row; // Количество строк в массиве данных
	int **dataArray; // Динамический двумерный массив для случайных данных и данных из файла
	int tempArray[8]; // Временный массив для хранения данных о новом подсчёте
	int flagNewCount = 0; // Флажок, отслеживающий, задан ли новый подсчёт
	int date[3]; // Массив для вывода даты
	dateWhenItWasReached endDate = {};
	Pedometer() // Конструктор
	{
		/* В конструкторе происходит заполнение динамического двумерного
		массива случайно сгенерированными данными и вывод его на экран.
		Далее все методы работают с этим массивом, пока пользователь
		не откроет файл с новыми данными.
		*/
		srand(time(0)); // Привязываем случайность ко времени
		row = 10;
		dataArray = new int*[row];
		for (int i = 0; i < row; i++) // Инициализация массива данных случайными данными
		{
			dataArray[i] = new int[8];
			for (int j = 7; j >= 0; j--)
			{
				switch (j)
				{
				case 0: // День
				{
					if (dataArray[i][1] == 1 || dataArray[i][1] == 3 || dataArray[i][1] == 5 || dataArray[i][1] == 7 || dataArray[i][1] == 8 || dataArray[i][1] == 10 || dataArray[i][1] == 12)
					{
						dataArray[i][j] = rand() % 31 + 1;
					}
					if (dataArray[i][1] == 4 || dataArray[i][1] == 6 || dataArray[i][1] == 9 || dataArray[i][1] == 11)
					{
						dataArray[i][j] = rand() % 30 + 1;
					}
					if (dataArray[i][1] == 2)
					{
						if ((dataArray[i][2] - 2000) % 4)
						{
							dataArray[i][j] = rand() % 28 + 1;
						}
						else
						{
							dataArray[i][j] = rand() % 29 + 1;
						}
					}
					break;
				}
				case 1: // Месяц
				{
					dataArray[i][j] = rand() % 12 + 1;
					break;
				}
				case 2: // Год
				{
					dataArray[i][j] = rand() % 18 + 2000;
					break;
				}
				case 3: // Час начала
				{
					dataArray[i][j] = rand() % 24;
					break;
				}
				case 4: // Минуты начала
				{
					dataArray[i][j] = rand() % 60;
					break;
				}
				case 5: // Час конца
				{
					dataArray[i][j] = rand() % 24;
					break;
				}
				case 6: // Минуты конца
				{
					dataArray[i][j] = rand() % 60;
					break;
				}
				case 7: // Количество шагов
				{
					dataArray[i][j] = rand() % 10000 + 10;
					break;
				}
				}
			}
		}
		cout << "Рандомно созданная история: \n";
		for (int i = 0; i < row; i++) // Вывод данных на экран
		{
			for (int j = 0; j < 8; j++)
			{
				switch (j)
				{
				case 0: // День
				{
					cout << "Дата: " << dataArray[i][j] << ".";
					break;
				}
				case 1: // Месяц
				{
					cout << dataArray[i][j] << ".";
					break;
				}
				case 2: // Год
				{
					cout << dataArray[i][j] << "    ";
					break;
				}
				case 3: // Час начала
				{
					cout << "Начало: " << dataArray[i][j] << ":";
					break;
				}
				case 4: // Минуты начала
				{
					cout << dataArray[i][j] << "    ";
					break;
				}
				case 5: // Час конца
				{
					cout << "Конец: " << dataArray[i][j] << ":";
					break;
				}
				case 6: // Минуты конца
				{
					cout << dataArray[i][j] << "    ";
					break;
				}
				case 7: // Количество шагов
				{
					cout << dataArray[i][j] << " шагов ";
					break;
				}
				}
			}
			cout << "\n";
		}
		cout << "\n\n";
	}
	~Pedometer() //Деструктор
	{
		delete dataArray; // Освобождаем память 
	}
	void SetStartDate(int day, int month, int year) // Метод "Установить дату начала подсчетов"
	{
		/* Данный метод заменяет дату начала
		подсчётов датой, которую ввёл пользователь.
		*/
		endDate.endDay = day;
		endDate.endMonth = month;
		endDate.endYear = year;
	}
	string GetStartDate() // Метод "Узнать дату начала подсчетов"
	{
		/* Данный метод возвращает строку с данными о начале подсчётов.
		*/
		string str;
		str = "\nДата: " + to_string(endDate.endDay) + '.' + to_string(endDate.endMonth) + '.' + to_string(endDate.endYear) + "\n\n";
		return str;
	}
	void SetСount(int tempData[]) // Метод "Задать подсчет"
	{
		/* Данный метод сохраняет данные, введенные пользователем
		во временный массив. Далее может использоваться методе
		"Посмотреть подсчёт" и для записи этих данных в файл.
		*/
		flagNewCount = 1;
		tempArray[0] = tempData[0];
		tempArray[1] = tempData[1];
		tempArray[2] = tempData[2];
		tempArray[3] = tempData[3];
		tempArray[4] = tempData[4];
		tempArray[5] = tempData[5];
		tempArray[6] = tempData[6];
		tempArray[7] = tempData[7];
	}
	string GetСount() // Метод "Информацию о выбранном подсчете"
	{
		/* Данный метод возвращает строку с данными,
		которые ввёл ранее пользователь.
		*/
		string str;
		str = "\nДата: " + to_string(tempArray[0]) + '.' + to_string(tempArray[1]) + '.'
			+ to_string(tempArray[2]) + "   Начало: " + to_string(tempArray[3]) + ":"
			+ to_string(tempArray[4]) + "   Конец: " + to_string(tempArray[5]) + ":"
			+ to_string(tempArray[6]) + "   " + to_string(tempArray[7]) + " шагов\n\n";
		return str;
	}
	int AverageSteps(int month, int year) // Метод "Среднее число шагов"
	{
		/* Данный метод возвращает среднее арифметическое число шагов
		в выбранном месяце или за всю историю наблюдений.
		*/
		int average = 0;
		int сount = 0;
		if (month == 0) // Если месяц равен 0, то считаем среднее за всю историю наблюдений
		{
			for (int i = 0; i < row; i++)
			{
				average += dataArray[i][7];
			}
			average = average / row;
			return average;
		}
		else // Иначе ситаем все записи в выброном месяце и ищем среднее
		{
			for (int i = 0; i < row; i++)
			{
				if (dataArray[i][1] == month && dataArray[i][2] == year)
				{
					average += dataArray[i][7];
					сount++;
				}
			}
			average = average / сount;
			return average;
		}
	}
	int AverageStepsDay(int dayOfWeek) // Метод "Среднее число шагов в выбранный день недели"
	{
		/* Данный метод возвращает среднее арифметическое число шагов
		в выбранный день недели или за всю историю наблюдений.
		Для определения дня недели по заданой дате, используем формулу Зеллера.
		*/
		int year, mon, day, yyear, hund, dday;
		int avg = 0;
		int сount = 0;
		for (int i = 0; i < row; i++)
		{
			day = dataArray[i][0];
			mon = dataArray[i][1];
			year = dataArray[i][2];

			if (mon < 3)
			{
				mon += 12;
				year -= 1;
				day += 1;
			}
			yyear = year % 100;
			hund = year / 100;
			dday = (((mon + 1) * 26 / 10) + day + yyear + yyear / 4 + hund / 4 - 2 * hund) % 7; // формула Зеллера
			switch (dday) // Полученное число отличается от привычных нам обозначений дня недели, поэтому производим замену (например 6 = суббота)
			{
			case 0:
			{
				dday = 6; // Суббота
				break;
			}
			case 1:
			{
				dday = 7; // Воскресенье
				break;
			}
			case 2:
			{
				dday = 1; // Понедельник
				break;
			}
			case 3:
			{
				dday = 2; // Вторник
				break;
			}
			case 4:
			{
				dday = 3; // Среда
				break;
			}
			case 5:
			{
				dday = 4; // Четверг
				break;
			}
			case 6:
			{
				dday = 5; // Пятница
				break;
			}
			}

			if (dday == dayOfWeek)
			{
				avg += dataArray[i][7];
				сount++;
			}
		}
		avg = avg / сount;
		return avg;
	}
	int MaxSteps(int month, int year) // Метод "Максимальное число шагов"
	{
		/* Данный метод возвращает максимальное число шагов
		в день в выбранном месяце или за всю историю наблюдений.
		Так же метод запоминает дату, когда было достигнуто максимальное число шагов.
		*/
		int max = 0;
		int day = 0;
		int tempCount = 0;
		int сountDay = 1;
		int сount = 0;
		int arrayMonth[31];
		for (int i = 0; i < 31; i++)
		{
			arrayMonth[i] = 0;
		}
		if (month == 0) // Если месяц равен 0, то считаем максимальное за всю историю наблюдений
		{
			for (int i = 0; i < row; i++) // Считаем количество дней за всю историю
			{
				if (i != 0)
				{
					if ((dataArray[i][0] != dataArray[i - 1][0]) || (dataArray[i][1] != dataArray[i - 1][1]))
					{
						сountDay++;
					}
				}
			}

			int *arrayDay = new int[сountDay]; // Создаём массив, в котором будут храниться количество шагов за каждый день 
			for (int i = 0; i < сountDay; i++)
			{
				arrayDay[i] = 0;
			}
			for (int i = 0; i < row; i++) // Записываем в массив сумму шагов каждого дня
			{
				if (i != 0)
				{
					if ((dataArray[i][0] != dataArray[i - 1][0]) || (dataArray[i][1] != dataArray[i - 1][1]))
					{
						arrayDay[сount] += dataArray[i][7];
						сount++;
					}
					else
					{
						arrayDay[сount - 1] += dataArray[i][7];
					}
				}
				else
				{
					arrayDay[сount] += dataArray[i][7];
					сount++;
				}
			}
			for (int i = 0; i < сount; i++) // Сравниваем каждую запись массива и ищем максимальное число шагов
			{
				if (max < arrayDay[i])
				{
					max = arrayDay[i];
					tempCount = i;
				}
			}

			сount = 0;
			for (int i = 0; i < row; i++) // Пробегаемся по массиву и ищем когда было достигнуто максимальное число шагов
			{
				if (i != 0)
				{
					if ((dataArray[i][0] != dataArray[i - 1][0]) || (dataArray[i][1] != dataArray[i - 1][1]))
					{
						if (tempCount == сount)
						{
							endDate.endDay = dataArray[i][0];
							endDate.endMonth = dataArray[i][1];
							endDate.endYear = dataArray[i][2];
							break;
						}
						сount++;
					}
				}
				else
				{
					if (tempCount == сount)
					{
						endDate.endDay = dataArray[i][0];
						endDate.endMonth = dataArray[i][1];
						endDate.endYear = dataArray[i][2];
						break;
					}
					сount++;
				}
			}

			return max;
		}
		else // Иначе ситаем все записи в выброном месяце и ищем максимальное
		{
			for (int i = 0; i < row; i++) // Записываем в массив количество шагов за каждый день месяца
			{
				if (dataArray[i][1] == month && dataArray[i][2] == year)
				{
					for (int j = 1; j < 32; j++)
					{
						if (dataArray[i][0] == j)
						{
							arrayMonth[j - 1] += dataArray[i][7];
						}
					}
				}
			}
			for (int i = 0; i < 31; i++) // Сравниваем каждую запись массива и ищем максимальное число шагов
			{
				if (max < arrayMonth[i])
				{
					max = arrayMonth[i];
					day = i + 1;
				}
			}
			endDate.endDay = day;
			endDate.endMonth = month;
			endDate.endYear = year;
			return max;
		}
	}
	dateWhenItWasReached GetEndDate()
	{
		return endDate;
	}
	void SaveFile() // Метод "Сохранить в файл"
	{
		/* Данный метод сохраняет в файл массив с данными.
		Любые изменения массива данных будут сохраненны.
		*/

		ofstream rec("D:\\RegFile.txt", ios_base::trunc);
		if (!rec)
		{
			cout << "\nФайл не открыт!\n\n";
		}
		else
		{
			cout << "\nФайл открыт!\n\n";

			for (int i = 0; i < row; i++) // Сохранение массива данных в файл
			{
				for (int j = 0; j < 8; j++)
				{
					rec << dataArray[i][j] << " ";
				}
				rec << endl;
			}

			if (flagNewCount = 1) // Если пользователь задавал новый подсчёт, то сохранить его в файл
			{
				for (int i = 0; i < 8; i++)
				{
					rec << tempArray[i] << " ";
				}
				rec << endl;
			}
			rec.close();
		}
	}
	void OpenFile() // Метод "Считать историю подсчетов из файла"
	{
		/* Данный метод отрывает файл и записывает считаные
		даные в динамический двумерный массив и выводит его на экран.
		*/
		row = 0;
		delete dataArray; // Освобождаем память от случайно сгенерированых данных
		ifstream file("D:\\OpenFile.txt");
		if (!file)
		{
			cout << "\nФайл не открыт!\n\n";
		}
		else
		{
			cout << "\nФайл открыт!\n\n";

			char *str = new char[1024];
			while (!file.eof()) // Считаем количество записей в файле
			{
				file.getline(str, 1024, '\n');
				row++;
			}
			cout << "В файле " << row << " записей:\n";

			file.seekg(0, ios::beg);
			file.clear();

			dataArray = new int*[row]; // Устанавливаем размерность двумерного массива
			for (int i = 0; i < row; i++)
			{
				dataArray[i] = new int[8];
			}

			for (int i = 0; i < row; i++) // Записываем данные в массив
			{
				for (int j = 0; j < 8; j++)
				{
					file >> dataArray[i][j];
					switch (j)
					{
					case 0:
					{
						cout << "Дата: " << dataArray[i][j] << ".";
						break;
					}
					case 1:
					{
						cout << dataArray[i][j] << ".";
						break;
					}
					case 2:
					{
						cout << dataArray[i][j] << "    ";
						break;
					}
					case 3:
					{
						cout << "Начало: " << dataArray[i][j] << ":";
						break;
					}
					case 4:
					{
						cout << dataArray[i][j] << "    ";
						break;
					}
					case 5:
					{
						cout << "Конец: " << dataArray[i][j] << ":";
						break;
					}
					case 6:
					{
						cout << dataArray[i][j] << "    ";
						break;
					}
					case 7:
					{
						cout << dataArray[i][j] << " шагов ";
						break;
					}
					}
				}
				cout << "\n";
			}
			cout << "\n\n";
			file.close();
		}
	}
};
int main()
{
	setlocale(LC_ALL, "rus");
	Pedometer obj1;
	int flag = 1;
	int stream;
	int transferPar[8];
	dateWhenItWasReached endDate;
	while (flag == 1)
	{
		cout << "Меню:" << endl;
		cout << "1) Установить дату начала подсчетов " << endl;
		cout << "2) Узнать дату начала подсчетов " << endl;
		cout << "3) Задать подсчет " << endl;
		cout << "4) Получить информацию о выбранном подсчете " << endl;
		cout << "5) Найти среднее число шагов в выбранном месяце или за всю историю наблюдений" << endl;
		cout << "6) Найти среднее число шагов в выбранный день недели за всю историю наблюдений " << endl;
		cout << "7) Найти максимальное число шагов в день в выбранном месяце или за всю историю наблюдений и дату,когда оно было достигнуто " << endl;
		cout << "8) Сохранить историю подсчетов в файл " << endl;
		cout << "9) Считать историю подсчетов из файла " << endl;
		cout << "Enter: ";
		cin >> stream;
		switch (stream)
		{
		case 1:
		{
			cout << "Введите дату (пример: 25 2 2018): \n";
			cin >> transferPar[0] >> transferPar[1] >> transferPar[2];
			obj1.SetStartDate(transferPar[0], transferPar[1], transferPar[2]);
			cout << "\nДата установлена!\n\n";
			cout << "Enter...\n\n";
			_getch();
			break;
		}
		case 2:
		{
			cout << obj1.GetStartDate();
			cout << "Enter...\n\n";
			_getch();
			break;
		}
		case 3:
		{
			cout << "Введите дату нового подсчёта (пример: 25 2 2018): \n";
			cin >> transferPar[0] >> transferPar[1] >> transferPar[2];
			cout << "Введите время начала нового подсчёта (пример: 20 45): \n";
			cin >> transferPar[3] >> transferPar[4];
			cout << "Введите время конца нового подсчёта (пример: 21 15): \n";
			cin >> transferPar[5] >> transferPar[6];
			cout << "Введите количество шагов (пример: 1350): \n";
			cin >> transferPar[7];
			obj1.SetСount(transferPar);
			cout << "\nПодсчёт задан!\n\n";
			cout << "Enter...\n\n";
			_getch();
			break;
		}
		case 4:
		{
			cout << obj1.GetСount();
			cout << "Enter...\n\n";
			_getch();
			break;
		}
		case 5:
		{
			cout << "Введите месяц и год (пример: 12 2017)(0 0 - вся история наблюдений): \n";
			cin >> transferPar[0] >> transferPar[1];
			cout << "\nСреднее число шагов: " << obj1.AverageSteps(transferPar[0], transferPar[1]) << "\n\n";
			cout << "Enter...\n\n";
			_getch();
			break;
		}
		case 6:
		{
			cout << "Введите день недели (пример: 5 (пятница)): \n";
			cin >> transferPar[0];
			cout << "\nСреднее число шагов в этот день недели: " << obj1.AverageStepsDay(transferPar[0]) << "\n\n";
			cout << "Enter...\n\n";
			_getch();
			break;
		}
		case 7:
		{
			cout << "Введите месяц и год (пример: 12 2017)(0 0 - вся история наблюдений): \n";
			cin >> transferPar[0] >> transferPar[1];
			cout << "\nМаксимальное число шагов: " << obj1.MaxSteps(transferPar[0], transferPar[1]);
			endDate = obj1.GetEndDate();
			cout << "\nБыло достигнуто: " << endDate.endDay << "." << endDate.endMonth << "." << endDate.endYear << "\n\n";
			cout << "Enter...\n\n";
			_getch();
			break;
		}
		case 8:
		{
			obj1.SaveFile();
			cout << "Запись в файл завершена!\n\n";
			cout << "Enter...\n\n";
			_getch();
			break;
		}
		case 9:
		{
			obj1.OpenFile();
			cout << "Enter...\n\n";
			_getch();
			break;
		}
		}
	}
	_getch();
}

