
#include "stdafx.h"
#include <iostream>
using namespace std;
class Ves {
	double kilo;
public:
	Ves(double _massa = 0)
	{
		kilo = _massa;
	}
	void setmassa(double _kilo)
	{
		kilo = _kilo;
	}
	double getmassa() const
	{
		return kilo;
	}
	double ConvertToFunt()
	{
		return kilo / 0.3732;
	}
	double ConvertToPood()
	{
		return kilo * 0.061048;
	}
	double ConvertToUnciya()
	{
		return kilo * 32.15075;
	}
	void Print()
	{
		cout << "Massa v kg= " << kilo << endl;
		cout << "Massa v funtah= " << ConvertToFunt() << endl;
		cout << "Massa v pudah= " << ConvertToPood() << endl;
		cout << "Massa v unciyah= " << ConvertToUnciya() << endl;
	}
	Ves& operator=(const Ves& op2)
	{
		kilo = op2.kilo;
		return *this;
	}
};

void main()
{
	Ves A;
	double n;
	cout << "Vvedite massu" << endl;
	cin >> n;
	A.setmassa(n);
	A.Print();
}

