#include <iostream> 
#include <string> 
#include <conio.h> 

using namespace std;

class String_
{
private:
	string strings;
	int ind;
	char ch;
public:
	String_() //����������� 
	{
		strings = " ";
	}

	~String_() //���������� 
	{
		//delete[] strings; 
	}

	void SetStr() //�������� ����� ������ 
	{
		cout << "Vvedite stroku: ";
		cin >> strings;
		if (strings.size() > 40)
		{
			cout << "Stroka bolshe 40!";
		}
		else
		{
			cout << "Stroka prinita! \n";
		}
	}

	void LenStr() //����� ������ 
	{
		cout << "Dlina stroki: " << strings.size() << endl;
	}

	void IndStr() //������ �� ������� 
	{
		cout << "Vvedite indeks: ";
		cin >> ind;
		cout << "Simvol: " << strings[ind - 1] << endl;
	}

	void IndRepStr() //������ ������� �� ������� 
	{
		cout << "Vvedite indeks: ";
		cin >> ind;
		cout << "Vvedite simvol: ";
		cin >> ch;
		strings[ind - 1] = ch;
		cout << " New Stroka: " << strings << endl;
	}


	bool PoliStr() //�������� �� ��������� 
	{
		for (int i = 0; i < strings.size() / 2; ++i)
		{
			if (strings[i] != strings[strings.size() - i - 1])
			{
				//cout � "Stroka ne polindrom! \n"; 
				return false;
			}
		}
		return true;
	}

	void subStr(int fp, int sp) // ��������� ���������
	{
		int i;
		for (int i = fp-1; i < fp+sp-1; i++)
		{
			cout� strings[i];
		}

	}
	void LatStr() // ���������� �������� ���������� �������� 
	{
		int count = 0;
		bool flag = false;
		for (int i = 0; i < strings.size(); i++) {
			for (int j = 0; j < strings.size(); j++) {
				if (i != j)
				{
					if (strings[i] == strings[j]) flag = true;
				}
			}
			if (flag == false)
				count++;
			flag = false;
		}
		cout << "Simvolov : " << count � endl;
	}

};

int main()
{
	int fp, sp;
	String_ obj1;
	obj1.SetStr();
	obj1.LenStr();
	obj1.IndStr();
	obj1.PoliStr();
	obj1.IndRepStr();
	obj1.LatStr();
	obj1.PoliStr();
	cout << "VVedite kollicestvo: ";
	cin >> sp;
	cout << "VVedite indeks: ";
	cin >> fp;
	obj1.subStr(fp, sp);
	if (obj1.PoliStr())
	{
		cout << "Stroka polindrom.";
	}
	else
	{
		cout << "Stroka ne polindrom";
	}
	system("pause");
	return 0;

}