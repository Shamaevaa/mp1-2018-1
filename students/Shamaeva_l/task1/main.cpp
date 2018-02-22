
#include <iostream>
using namespace std;
class ConvertVes {
	double kilo;
public:
	ConvertVes(double _massa = 0)
	{
		kilo = _massa;
	}
	void SetMassa(double _kilo)
	{
		kilo = _kilo;
	}
	double GetMassa()
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
	ConvertVes A;
	double n;
	cout << "Vvedite massu" << endl;
	cin >> n;
	A.setmassa(n);
	A.Print();
}

