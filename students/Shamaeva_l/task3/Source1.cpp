#include <iostream>
#include <math.h> 
using namespace std;
class TeilorSeries
{
	int n;
	int function;
	double x;
public:
	TeilorSeries(int _n = 0, double _x = 0, int _function = 0)
	{
		n = _n;
		x = _x;
		function = _function;
	}
	~TeilorSeries()
	{
	}
	TeilorSeries& operator=(const TeilorSeries& ob)
	{
		n = ob.n;
		x = ob.x;
		function = ob.function;
		return *this;
	}
	void SetCount(int _n)
	{
		n = _n;
	}
	void SetFunction(int f)
	{
		function = f;
	}
	void SetPoint(double _x)
	{
		x = _x;
	}
	void Print()
	{
		switch (function)
		{
		case 1:

		{
			cout << "x";
			for (int i = 2; i <= n; i++)
			{
				if (i % 2 == 0)
					cout << "-";
				else
					cout << "+";
				cout << "x^" << (2 * i - 1) << "/" << (2 * i - 1) << "!";
			}
			cout << endl;
			break;
		}
		case 2:

		{
			cout << "1+x^2/2!";
			for (int i = 2; i < n; i++)
			{
				if (i % 2 == 0)
					cout << "-";
				else
					cout << "+";
				cout << "x^" << 2 * i << "/" << 2 * i << "!";
			}
			cout << endl;
			break;
		}
		case 3:
		{
			cout << "1";
			for (int i = 1; i < n; i++)
			{
				cout << "+x^(" << i << ")/" << i << "!";
			}
			cout << endl;
			break;
		}
		}
	}
	double GetMemberOfSeries(int k)
	{
		double step;
		switch (function)
		{
		case 1:

		{
			if (k % 2 == 0)
				return 0;
			else
			{
				step = x;
				for (int i = 3; i <= k; i++, i++)
					step *= ((-1)*x*x / (i*(i - 1)));
				return step;
				break;
			}
		}
		case 2:
		{
			if (k % 2 == 1)
				return 0;
			else
			{
				step = 1;
				for (int i = 2; i <= k; i++, i++)
					step *= ((-1)*x*x / (i*(i - 1)));
				return step;
				break;
			}
		}
		case 3:

		{
			step = 1;
			for (int i = 1; i <= k; i++)
				step *= (x / i);
			return step;
			break;
		}
		}
	}
	void Comparison()
	{
		switch (function)
		{
		case 1:
		{
			cout << "Raznica= " << sin(x) - ResultOfFunctionEvaluation() << endl;
			break;
		}
		case 2:
		{
			cout << "Raznica= " << cos(x) - ResultOfFunctionEvaluation() << endl;
			break;
		}
		case 3:

		{
			cout << "Raznica= " << exp(x) - ResultOfFunctionEvaluation() << endl;
			break;
		}
		}
	}
	int GetCount(void)
	{
		return n;
	}
	double GetPoint(void)
	{
		return x;
	}
	double ResultOfFunctionEvaluation()
	{
		switch (function)
		{
		case 1:
		{
			double step = x;
			double sum = x;
			for (int i = 3; i <= n; i++, i++)
			{
				step *= ((-1)*x*x / (i*(i - 1)));
				sum += step;
			}
			return sum;
			break;
		}

		case 2:
		{
			double step = 1;
			double sum = 1;
			for (int i = 2; i <= n; i++, i++)
			{
				step *= ((-1)*x*x / (i*(i - 1)));
				sum += step;
			}
			return sum;
			break;
		}
		case 3:
		{
			double step = 1;
			double sum = 1;
			for (int i = 1; i <= n; i++)
			{
				step *= (x / i);
				sum += step;
			}
			return sum;
			break;
		}
		}
	}
};
int main()
{
	int n = 0, x = 0, f, c;
	TeilorSeries obj1;
	cout << "Vvedite kolichestvo chlenov:" << endl;
	cin >> n;
	obj1.SetCount(n);
	cout << "Vvedite tochku x:" << endl;
	cin >> x;
	obj1.SetPoint(x);
	cout << "Viberite funkciyu:" << endl;
	cout << "1.Sin(x)" << endl;
	cout << "2.Cos(x)" << endl;
	cout << "3.Exp(x)" << endl;
	cin >> f;
	obj1.SetFunction(f);
	cout << "Resultat" << endl;
	cout << obj1.ResultOfFunctionEvaluation() << endl;
	cout << "Sravnim s etalonom" << endl;
	obj1.Comparison();
	cout << "Vvedite shlen, kotoriy hotite vichislit:'" << endl;
	cin >> c;
	cout << c << "Shlen=" << obj1.GetMemberOfSeries(c) << endl;
	cout << "Formula:" << endl;
	obj1.Print();
	system("pause");
}