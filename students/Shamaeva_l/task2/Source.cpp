#include <iostream> 
#include <string> 
#include <conio.h> 
#include <cstdio>
using namespace std;

class String_
{
private:
	char* strings;
	int ind;
	int leng;
	char ch;
public:
	String_() //конструктор 
	{
		strings = new char;
	}

	~String_() //Деструктор 
	{
		//delete[] strings; 
	}

	void SetStr(char* a) //Введение новой строки 
	{
		int count = strlen(a);
		if (strlen(a) > 40)
		{
			cout << "Stroka bolshe 40!";
		}
		else
		{
			cout << "Stroka prinita! \n";
		}
		strings = a;
	}

	int LenStr() //Длина строки 
	{
		leng = strlen(strings);

		return leng;
	}

	void IndStr() //Символ по индексу 
	{
		cout << "Vvedite indeks: ";
		cin >> ind;
		cout << "Simvol: " << strings[ind - 1] << endl;
	}

	void IndRepStr() //Замена символа по индексу 
	{
		cout << "Vvedite indeks: ";
		cin >> ind;
		cout << "Vvedite simvol: ";
		cin >> ch;
		strings[ind - 1] = ch;
		cout << " New Stroka: " << strings << endl;
	}


	bool PoliStr() //Проверка на полиндром 
	{
		for (int i = 0; i < strlen(strings) / 2; ++i)
		{
			if (strings[i] != strings[strlen(strings) - i - 1])
			{
				//cout « "Stroka ne polindrom! \n"; 
				return false;
			}
		}
		return true;
	}

	void subStr(int fp, int sp) // Выделение подстроки
	{
		int i;
		for (int i = fp - 1; i < fp + sp - 1; i++)
		{
			cout << strings[i];
		}

	}
	void LatStr() // Нахождение символов латинского алфавита 
	{
		int count = 0;
		bool flag = false;
		for (int i = 0; i < strlen(strings); i++) {
			for (int j = 0; j < strlen(strings); j++) {
				if (i != j)
				{
					if (strings[i] == strings[j]) flag = true;
				}
			}
			if (flag == false)
				count++;
			flag = false;
		}
		cout << "Simvolov : " << count << endl;
	}

};

int main()
{
	int fp, sp;
	char * str = new char;
	String_ obj1;
	cout << "Vvedite stroku: ";
	cin >> str;
	obj1.SetStr(str);
	cout << "Dlina stroki: " << obj1.LenStr() << endl;
	obj1.LenStr();
	obj1.IndStr();
	obj1.PoliStr();
	obj1.IndRepStr();
	obj1.PoliStr();
	cout << "VVedite kollicestvo: ";
	cin >> sp;
	cout << "VVedite indeks: ";
	cin >> fp;
	obj1.subStr(fp, sp);
	if (obj1.PoliStr())
	{
		cout << "Stroka polindrom." << endl;
	}
	else
	{
		cout << "Stroka ne polindrom" << endl;
	}
	system("pause");
	return 0;

}