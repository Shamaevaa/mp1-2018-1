#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <ctime>
using namespace std;
class Pedometer
{
public:
	int p;
	int **ary;
	int ary2[8];
	int ko = 0;
	int kp = 0;
	int dte[3];
	string str;
	int ave = 0;
	int k = 0;
	int year, mon, day, yyear, hund, dday;
	int avg = 0;
	int max = 0;
	int dat = 0;
	int h = 0;
	int ka = 1;
	int ary4[31];
	int pk = 0;
	Pedometer()
	{
		srand(time(0));
		p = 10;
		ary = new int*[p];
		for (int i = 0; i < p; i++)
		{
			ary[i] = new int[8];
			for (int j = 7; j >= 0; j--)
			{
				switch (j)
				{
				case 0:
				{
					if (ary[i][1] == 1 || ary[i][1] == 3 || ary[i][1] == 5 || ary[i][1] == 7 || ary[i][1] == 8 || ary[i][1] == 10 || ary[i][1] == 12)
					{
						ary[i][j] = rand() % 31 + 1;
					}
					if (ary[i][1] == 4 || ary[i][1] == 6 || ary[i][1] == 9 || ary[i][1] == 11)
					{
						ary[i][j] = rand() % 30 + 1;
					}
					if (ary[i][1] == 2)
					{
						if ((ary[i][2] - 2000) % 4)
						{
							ary[i][j] = rand() % 28 + 1;
						}
						else
						{
							ary[i][j] = rand() % 29 + 1;
						}
					}
					break;
				}
				case 1:
				{
					ary[i][j] = rand() % 12 + 1;
					break;
				}
				case 2:
				{
					ary[i][j] = rand() % 18 + 2000;
					break;
				}
				case 3:
				{
					ary[i][j] = rand() % 24;
					break;
				}
				case 4:
				{
					ary[i][j] = rand() % 60;
					break;
				}
				case 5:
				{
					ary[i][j] = rand() % 24;
					break;
				}
				case 6:
				{
					ary[i][j] = rand() % 60;
					break;
				}
				case 7:
				{
					ary[i][j] = rand() % 10000 + 10;
					break;
				}
				}
			}
		}
		cout << "Рандомно созданная история: \n";
		for (int i = 0; i < p; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				switch (j)
				{
				case 0:
				{
					cout << "Дата: " << ary[i][j] << ".";
					break;
				}
				case 1:
				{
					cout << ary[i][j] << ".";
					break;
				}
				case 2:
				{
					cout << ary[i][j] << "    ";
					break;
				}
				case 3:
				{
					cout << "Начало: " << ary[i][j] << ":";
					break;
				}
				case 4:
				{
					cout << ary[i][j] << "    ";
					break;
				}
				case 5:
				{
					cout << "Конец: " << ary[i][j] << ":";
					break;
				}
				case 6:
				{
					cout << ary[i][j] << "    ";
					break;
				}
				case 7:
				{
					cout << ary[i][j] << " шагов ";
					break;
				}
				}
			}
			cout << "\n";
		}
		cout << "\n\n";
	}
	~Pedometer()
	{
		delete ary;
	}
	void SetDate(int d, int m, int y)
	{
		ary[0][0] = d;
		ary[0][1] = m;
		ary[0][2] = y;
	}
	string GetDate()
	{
		str = "\nДата: " + to_string(ary[0][0]) + '.' + to_string(ary[0][1]) + '.' + to_string(ary[0][2]) + "\n\n";
		return str;
	}
	void SetMeter(int r[])
	{
		ko = 1;
		ary2[0] = r[0];
		ary2[1] = r[1];
		ary2[2] = r[2];
		ary2[3] = r[3];
		ary2[4] = r[4];
		ary2[5] = r[5];
		ary2[6] = r[6];
		ary2[7] = r[7];
	}
	string GetMeter()
	{
		str = "\nДата: " + to_string(ary2[0]) + '.' + to_string(ary2[1]) + '.' + to_string(ary2[2]) + "   Начало: " + to_string(ary2[3]) + ":" + to_string(ary2[4]) + "   Конец: " + to_string(ary2[5]) + ":" + to_string(ary2[6]) + "   " + to_string(ary2[7]) + " шагов\n\n";
		return str;
	}
	int Average(int m1, int m2)
	{
		if (m1 == 0)
		{
			for (int i = 0; i < p; i++)
			{
				ave += ary[i][7];
			}
			ave = ave / p;
			return ave;
		}
		else
		{
			for (int i = 0; i < p; i++)
			{
				if (ary[i][1] == m1 && ary[i][2] == m2)
				{
					ave += ary[i][7];
					k++;
				}
			}
			ave = ave / k;
			return ave;
		}
	}
	int AverageDay(int m)
	{
		for (int i = 0; i < p; i++)
		{
			day = ary[i][0];
			mon = ary[i][1];
			year = ary[i][2];

			if (mon < 3)
			{
				mon += 12;
				year -= 1;
				day += 1;
			}
			yyear = year % 100;
			hund = year / 100;
			dday = (((mon + 1) * 26 / 10) + day + yyear + yyear / 4 + hund / 4 - 2 * hund) % 7;

			switch (dday)
			{
			case 0:
			{
				dday = 6;
				break;
			}
			case 1:
			{
				dday = 7;
				break;
			}
			case 2:
			{
				dday = 1;
				break;
			}
			case 3:
			{
				dday = 2;
				break;
			}
			case 4:
			{
				dday = 3;
				break;
			}
			case 5:
			{
				dday = 4;
				break;
			}
			case 6:
			{
				dday = 5;
				break;
			}
			}

			if (dday == m)
			{
				avg += ary[i][7];
				k++;
			}
		}
		avg = avg / k;
		return avg;
	}
	int Max(int m1, int m2)
	{
		for (int i = 0; i < 31; i++)
		{
			ary4[i] = 0;
		}

		if (m1 == 0)
		{
			for (int i = 0; i < p; i++)
			{
				if (i != 0)
				{
					if ((ary[i][0] != ary[i - 1][0]) || (ary[i][1] != ary[i - 1][1]))
					{
						k++;
					}
				}
			}
			int *ary5 = new int[k];
			for (int i = 0; i < k; i++)
			{
				ary5[i] = 0;
			}
			for (int i = 0; i < p; i++)
			{
				if (i != 0)
				{
					if ((ary[i][0] != ary[i - 1][0]) || (ary[i][1] != ary[i - 1][1]))
					{
						ary5[pk] += ary[i][7];
						pk++;
					}
					else
					{
						ary5[pk - 1] += ary[i][7];
					}
				}
				else
				{
					ary5[pk] += ary[i][7];
					pk++;
				}
			}
			for (int i = 0; i < k; i++)
			{
				if (max < ary5[i])
				{
					max = ary5[i];
					h = i;
				}
			}
			pk = 0;
			for (int i = 0; i < p; i++)
			{
				if (i != 0)
				{
					if ((ary[i][0] != ary[i - 1][0]) || (ary[i][1] != ary[i - 1][1]))
					{
						if (h == pk)
						{
							dte[0] = ary[i][0];
							dte[1] = ary[i][1];
							dte[2] = ary[i][2];
							break;
						}
						pk++;
					}
				}
				else
				{
					if (h == pk)
					{
						dte[0] = ary[i][0];
						dte[1] = ary[i][1];
						dte[2] = ary[i][2];
						break;
					}
					pk++;
				}
			}
			return max;
		}
		else
		{
			for (int i = 0; i < p; i++)
			{
				if (ary[i][1] == m1 && ary[i][2] == m2)
				{
					for (int j = 1; j < 32; j++)
					{
						if (ary[i][0] == j)
						{
							ary4[j - 1] += ary[i][7];
						}
					}
				}
			}
			for (int i = 0; i < 31; i++)
			{
				if (max < ary4[i])
				{
					max = ary4[i];
					dat = i + 1;
				}
			}
			dte[0] = dat;
			dte[1] = m1;
			dte[2] = m2;
			return max;
		}
	}
	void SaveFile()
	{
		ofstream rec("D:\\RegFile.txt", ios_base::trunc);
		if (!rec)
		{
			cout << "\nФайл не открыт!\n\n";
		}
		else
		{
			cout << "\nФайл открыт!\n\n";

			for (int i = 0; i < p; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					rec << ary[i][j] << " ";
				}
				rec << endl;
			}

			if (ko = 1)
			{
				for (int i = 0; i < 8; i++)
				{
					rec << ary2[i] << " ";
				}
				rec << endl;
			}
			rec.close();
		}
	}
	void OpenFile()
	{
		p = 0;
		delete ary;
		ifstream file("D:\\OpenFile.txt");
		if (!file)
		{
			cout << "\nФайл не открыт!\n\n";
		}
		else
		{
			cout << "\nФайл открыт!\n\n";

			char *str = new char[1024];
			while (!file.eof())
			{
				file.getline(str, 1024, '\n');
				p++;
			}
			cout << "В файле " << p << " записей:\n";

			file.seekg(0, ios::beg);
			file.clear();

			ary = new int*[p];
			for (int i = 0; i < p; i++)
			{
				ary[i] = new int[8];
			}

			for (int i = 0; i < p; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					file >> ary[i][j];
					switch (j)
					{
					case 0:
					{
						cout << "Дата: " << ary[i][j] << ".";
						break;
					}
					case 1:
					{
						cout << ary[i][j] << ".";
						break;
					}
					case 2:
					{
						cout << ary[i][j] << "    ";
						break;
					}
					case 3:
					{
						cout << "Начало: " << ary[i][j] << ":";
						break;
					}
					case 4:
					{
						cout << ary[i][j] << "    ";
						break;
					}
					case 5:
					{
						cout << "Конец: " << ary[i][j] << ":";
						break;
					}
					case 6:
					{
						cout << ary[i][j] << "    ";
						break;
					}
					case 7:
					{
						cout << ary[i][j] << " шагов ";
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
	int m = 1;
	int l;
	int dmy[8];
	while (m == 1)
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
		cin >> l;
		switch (l)
		{
		case 1:
		{
			cout << "Введите дату (пример: 25 2 2018): \n";
			cin >> dmy[0] >> dmy[1] >> dmy[2];
			obj1.SetDate(dmy[0], dmy[1], dmy[2]);
			cout << "\nДата установлена!\n\n";
			cout << "Enter...\n\n";
			_getch();
			break;
		}
		case 2:
		{
			cout << obj1.GetDate();
			cout << "Enter...\n\n";
			_getch();
			break;
		}
		case 3:
		{
			cout << "Введите дату нового подсчёта (пример: 25 2 2018): \n";
			cin >> dmy[0] >> dmy[1] >> dmy[2];
			cout << "Введите время начала нового подсчёта (пример: 20 45): \n";
			cin >> dmy[3] >> dmy[4];
			cout << "Введите время конца нового подсчёта (пример: 21 15): \n";
			cin >> dmy[5] >> dmy[6];
			cout << "Введите количество шагов (пример: 1350): \n";
			cin >> dmy[7];
			obj1.SetMeter(dmy);
			cout << "\nПодсчёт задан!\n\n";
			cout << "Enter...\n\n";
			_getch();
			break;
		}
		case 4:
		{
			cout << obj1.GetMeter();
			cout << "Enter...\n\n";
			_getch();
			break;
		}
		case 5:
		{
			cout << "Введите месяц и год (пример: 12 2017)(0 0 - вся история наблюдений): \n";
			cin >> dmy[0] >> dmy[1];
			cout << "\nСреднее число шагов: " << obj1.Average(dmy[0], dmy[1]) << "\n\n";
			cout << "Enter...\n\n";
			_getch();
			break;
		}
		case 6:
		{
			cout << "Введите день недели (пример: 5 (пятница)): \n";
			cin >> dmy[0];
			cout << "\nСреднее число шагов в этот день недели: " << obj1.AverageDay(dmy[0]) << "\n\n";
			cout << "Enter...\n\n";
			_getch();
			break;
		}
		case 7:
		{
			cout << "Введите месяц и год (пример: 12 2017)(0 0 - вся история наблюдений): \n";
			cin >> dmy[0] >> dmy[1];
			cout << "\nМаксимальное число шагов: " << obj1.Max(dmy[0], dmy[1]);
			cout << "\nБыло достигнуто: " << obj1.dte[0] << "." << obj1.dte[1] << "." << obj1.dte[2] << "\n\n";
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

