#include <iostream>
using namespace std;
class ConvertVes {
	double kilo;
public:
	ConvertVes(double _massa = 0)
	{
		kilo = _massa;
	}
	void Setmassa(double _kilo)
	{
		kilo = _kilo;
	}
	double Getmassa()
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
	ConvertVes & operator=(const ConvertVes& op2)
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
	A.Setmassa(n);
	A.Print();
	system("pause");
}