#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <vector>
#include <string> 
#include <ctime>

using namespace std;

class Event {
private:
	time_t date;
	string name; // название сеансов
	int price;
	int VIPprice;
	int hallNumber;
public:
	Event(int year, int month, int day, int hour, int minute, string name, int price, int VIPprice, int hallNumber) {
		time_t rawtime;
		struct tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		timeinfo->tm_year = year - 1900;
		timeinfo->tm_mon = month - 1;
		timeinfo->tm_mday = day;
		timeinfo->tm_hour = hour;
		timeinfo->tm_min = minute;
		date = mktime(timeinfo);
		this->name = name;
		this->price = price;
		this->VIPprice = VIPprice;
		this->hallNumber = hallNumber;
	}
	~Event() {}
	long long getDate() {
		return date;
	}
	string getDateAsString() {
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[80];
		rawtime = date;
		timeinfo = localtime(&rawtime);
		strftime(buffer, sizeof(buffer), "%d.%m %H:%M", timeinfo);
		std::string str(buffer);
		return str;
	}
	string getName() {
		return name;
	}
	int getPrice() {
		return price;
	}
	int getVIPprice() {
		return VIPprice;
	}
	int getHallNumber() {
		return hallNumber;
	}

	void printToConsole() {
		cout << "Дата : ";
		cout << getDateAsString().c_str() << endl;
		cout << "Фильм : ";
		cout << name.c_str() << endl;
		cout << "Зал : ";
		cout << hallNumber << endl;
	}
};
class Hall {
private:
	int rows, kolstlb, viprows;
public:
	Hall(int rows, int viprows, int kolstlb)
	{
		this->rows = rows;
		this->kolstlb = kolstlb;
		this->viprows = viprows;
	}
	~Hall() {}
	int getRows() {
		return rows;
	}
	int getVIPRows() {
		return viprows;
	}
	int getKolStlb() {
		return kolstlb;
	}
};

struct DayEvents {
	Event* arr[50];
	int size;
};

class CinemaCentr {
private:
	string name;
	vector<Hall> halls;
	map<int, DayEvents*> events;
	map<Event*, bool**> AllPlaces;
public:
	CinemaCentr(string name) {
		this->name = name;
	}
	~CinemaCentr() {
		for (map<Event*, bool**>::iterator it = AllPlaces.begin(); it != AllPlaces.end(); ++it)
			if (it->second != NULL) {
				delete[] it->second;
			}
	}
	void addHall(Hall hall) {
		halls.push_back(hall);
	}
	void addEvent(Event* event) {
		long long date = event->getDate();
		time_t rawtime;
		struct tm * timeinfo;
		rawtime = date;
		timeinfo = localtime(&rawtime);
		int day = timeinfo->tm_mday;
		DayEvents* dayEvents = events[day];
		if (!dayEvents) {
			dayEvents = new DayEvents();
			events[day] = dayEvents;
		}
		dayEvents->arr[dayEvents->size++] = event;

		int nomzal = event->getHallNumber();
		Hall zal = halls[nomzal - 1];
		bool** matr = new bool*[zal.getRows() + zal.getVIPRows()];
		for (int i = 0; i < zal.getRows() + zal.getVIPRows(); i++) {
			matr[i] = new bool[zal.getKolStlb()];
			for (int j = 0; j < zal.getKolStlb(); j++) {
				matr[i][j] = false;
			}
		}
		AllPlaces[event] = matr;
	}
	DayEvents* getByDate(int mDay) {
		return events[mDay];
	}
	bool check(Event* event, bool isVip, int numberNeedPlaces) {
		bool** matr = AllPlaces.at(event);
		int nz = event->getHallNumber();
		Hall h = halls[nz - 1];
		int from = isVip ? h.getRows() : 0;
		int to = isVip ? h.getVIPRows() + h.getRows() - 1 : h.getRows() - 1;
		for (int i = from; i <= to; i++) {
			int flag = 0;
			for (int j = 0; j < h.getKolStlb(); j++) {
				if (flag == numberNeedPlaces) {
					return true;
				}
				if (matr[i][j]) {
					flag = 0;
					continue;
				}
				else {
					flag++;
				}
			}
		}
		return false;
	}
	int* reserve(Event* event, bool isVip, int numberNeedPlaces) {
		bool** matr = AllPlaces.at(event);
		int nz = event->getHallNumber();
		Hall h = halls[nz - 1];
		int from = isVip ? h.getRows() : 0;
		int to = isVip ? h.getVIPRows() + h.getRows() - 1 : h.getRows() - 1;
		for (int i = from; i <= to; i++) {
			int flag = 0;
			for (int j = 0; j < h.getKolStlb(); j++) {
				if (flag == numberNeedPlaces) {
					int* reserved = new int[3];
					reserved[0] = i;
					reserved[1] = j - numberNeedPlaces;
					reserved[2] = j - 1;
					for (int k = reserved[1]; k <= reserved[2]; k++) {
						matr[i][k] = true;
					}
					return reserved;
				}
				if (matr[i][j]) {
					flag = 0;
					continue;
				}
				else {
					flag++;
				}
			}
		}
		return NULL;
	}
	void release(Event* event, int row, int from, int to) {
		bool** matr = AllPlaces.at(event);
		for (int i = from; i <= to; i++) {
			matr[row][i] = false;
		}
		return;
	}
};
class TicketCassa {
private:
	CinemaCentr * centr;
	int* seats;
	int dayM;
	int nomSeans;
	int kol;
	bool isVip;
public:
	TicketCassa(CinemaCentr* centr) {
		this->centr = centr;
	}
	~TicketCassa() {}
	int printAllToDay(int dayM, int* max) {
		bool print = false;
		int first = -1;
		DayEvents* events = centr->getByDate(dayM);
		if (events) {
			time_t currenttime = time(0);
			for (int i = 0; i < events->size; i++) {
				time_t seanstime = events->arr[i]->getDate();
				long diff = currenttime - seanstime;
				if (diff <= 600) {
					if (first == -1) {
						first = i + 1;
					}
					print = true;
					cout << i + 1 << ":";
					events->arr[i]->printToConsole();
					cout << endl;
					*max = i + 1;
				}
			}
		}
		if (!print) {
			cout << "В этот день ничего нет" << endl;
		}
		return first;
	}
	void printAvaliablebility(int dayM, int nomSeans, int kol, bool isVip) {
		DayEvents* events = centr->getByDate(dayM);
		if (events) {
			Event* event = events->arr[nomSeans - 1];
			if (centr->check(event, isVip, kol)) {
				cout << "Места есть" << endl;
			}
			else {
				cout << "Мест нет" << endl;
			}
		}
		else {
			cout << "Нет такого сеанса" << endl;
		}
	}
	void printCost(int dayM, int nomSeans, int kol, bool isVip) {
		DayEvents* events = centr->getByDate(dayM);
		if (events) {
			Event* event = events->arr[nomSeans - 1];
			time_t rawtime = event->getDate();
			struct tm * timeinfo = localtime(&rawtime);
			int hour = timeinfo->tm_hour;
			int price = isVip ? event->getVIPprice() : event->getPrice();
			if (hour<12)
				price = 0.75 * price;
			if (hour>18)
				price = 1.75 * price;
			int totalPrice = price * kol;
			cout << "Цена заказа=" << totalPrice << endl;
		}
		else {
			cout << "Нет такого сеанса" << endl;
		}
	}
	void reserve(int dayM, int nomSeans, int kol, bool isVip) {
		DayEvents* events = centr->getByDate(dayM);
		if (events) {
			Event* event = events->arr[nomSeans - 1];
			int* seats = centr->reserve(event, isVip, kol);
			if (seats) {
				this->seats = seats;
				this->dayM = dayM;
				this->nomSeans = nomSeans;
				this->kol = kol;
				this->isVip = isVip;
				cout << "Успешно" << endl;
			}
			else {
				cout << "Свободных мест нет" << endl;
			}
		}
		else {
			cout << "Нет такого сеанса" << endl;
		}
	}
	void cancel() {
		if (seats) {
			DayEvents* events = centr->getByDate(dayM);
			Event* event = events->arr[nomSeans - 1];
			centr->release(event, seats[0], seats[1], seats[2]);
			delete[] seats;
			cout << "Отменено" << endl;
		}
	}
	void printTicket() {
		if (seats) {
			DayEvents* events = centr->getByDate(dayM);
			Event* event = events->arr[nomSeans - 1];
			cout << "Ваш билет : " << endl;
			cout << "Дата и время вашего сеанса:" << endl;
			cout << event->getDateAsString().c_str() << endl;
			cout << "Название фильма: " << endl;
			cout << event->getName().c_str() << endl;
			cout << "Номер вашего зала: " << endl;
			cout << event->getHallNumber() << endl;
			cout << "Ряд" << endl;
			cout << seats[0] + 1 << endl;
			cout << "Места" << endl;
			cout << to_string(seats[1] + 1) + "-" + to_string(seats[2] + 1) << endl;
			delete[] seats;
		}
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	CinemaCentr electron("Electron");
	Hall hall1(10, 2, 20);
	Hall hall2(20, 3, 25);
	Event kino0(2018, 04, 22, 7, 30, "kino_bez_prodaji", 100, 200, 2);
	Event kino00(2018, 04, 22, 18, 30, "kino_s_prodaji", 100, 200, 2);
	Event kino1(2018, 04, 22, 20, 30, "kino1", 100, 200, 1);
	Event kino2(2018, 04, 22, 22, 30, "kino2", 100, 200, 2);
	electron.addHall(hall1);
	electron.addHall(hall2);
	electron.addEvent(&kino0);
	electron.addEvent(&kino00);
	electron.addEvent(&kino1);
	electron.addEvent(&kino2);
	TicketCassa kassa(&electron);
	int day = -1;
	int max = -1;
	int seans = -1;
	bool reserve = false;
	bool print = false;
	while (true)
	{
		int l;
		cout << "Меню:" << endl;
		if (day == -1) {
			cout << "1) Просмотр расписания на день и выбор сеанса" << endl;
			cout << "10) Завершить обслуживание" << endl;
		}
		else {
			if (!reserve) {
				cout << "2) Проверить наличие требуемого количества свободных мест на выбранный сеанс" << endl;
				cout << "3) Рассчитать общую стоимость билетов" << endl;
				cout << "4) Резервирование требуемого количества свободных мест на выбранный сеанс" << endl;
			}
			if (reserve && !print) {
				cout << "5) Отменить резерв" << endl;
				cout << "6) Сформировать билеты" << endl;
			}
			cout << "7) Посмотреть другой сеанс" << endl;
			cout << "10) Завершить обслуживание" << endl;
		}
		cout << "Enter: " << endl;
		cin >> l;
		switch (l)
		{
		case 1:
		{
			cout << "Введите день месяца для просмотра расписания" << endl;
			cin >> day;
			int first = kassa.printAllToDay(day, &max);
			while (seans < first || seans > max) {
				cout << "Введите номер интересующего сеанса" << endl;
				cin >> seans;
				if (seans < first) {
					cout << "Продажа на этот сеанс уже закрыта" << endl;
				}
				if (seans > max) {
					cout << "Сеанса с таким номером нет" << endl;
				}
			}
			break;
		}
		case 2:
		{
			int kol;
			bool vip;
			cout << "Введите количество требуемых мест и признак вип(0-не вип 1-вип)" << endl;
			cin >> kol >> vip;
			kassa.printAvaliablebility(day, seans, kol, vip);
			break;
		}
		case 3:
		{
			int kol;
			bool vip;
			cout << "Введите количество требуемых мест и признак вип(0-не вип 1-вип)" << endl;
			cin >> kol >> vip;
			kassa.printCost(day, seans, kol, vip);
			break;
		}
		case 4:
		{
			int kol;
			bool vip;
			cout << "Введите количество требуемых мест и признак вип(0-не вип 1-вип)" << endl;
			cin >> kol >> vip;
			kassa.reserve(day, seans, kol, vip);
			reserve = true;
			break;
		}
		case 5:
		{
			kassa.cancel();
			day = -1;
			max = -1;
			seans = -1;
			reserve = false;
			print = false;
			break;
		}
		case 6:
		{
			kassa.printTicket();
			print = true;
			break;
		}
		case 7:
		{
			day = -1;
			max = -1;
			seans = -1;
			reserve = false;
			print = false;
			break;
		}

		case 10:
			exit(0);
		}
	}
}
