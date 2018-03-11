#include <iostream> 
#include <string> 
#include <math.h> 
using namespace std;
class Teilor
{
	int n;
	int function;
	double x;
public:
	Teilor(int _n = 0, double _x = 0)
	{
		n = _n;
		x = _x;
	}

	~Teilor()
	{
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
		if (function == 1)
		{
			cout << "x";
			for (int i = 3, k = 0; i <= n; i++, i++, k++)
			{
				if (k % 2 == 0)
					cout << "-";
				else
					cout << "+";
				cout << "x^(" << i << ")/" << i << "!";
			}
			cout << endl;
		}
		if (function == 2)
		{
			cout << "1";
			for (int i = 2, k = 0; i <= n; i++, i++, k++)
			{
				if (k % 2 == 0)
					cout << "-";
				else
					cout << "+";
				cout << "x^(" << i << ")/" << i << "!";
			}
			cout << endl;
		}
		if (function == 3)
		{
			cout << "1+x";
			for (int i = 2; i <= n; i++)
			{
				cout << "+x^(" << i << ")/" << i << "!";
			}
			cout << endl;
		}
	}


	double Member(int k)
	{
		double step;
		if (function == 1)
		{
			if (k % 2 == 0)
				return 0;
			else
			{
				step = x;
				for (int i = 3; i <= k; i++, i++)
					step *= ((-1)*x*x / (i*(i - 1)));
				return step;
			}
		}
		if (function == 2)
		{
			if (k % 2 == 1)
				return 0;
			else
			{
				step = 1;
				for (int i = 2; i <= k; i++, i++)
					step *= ((-1)*x*x / (i*(i - 1)));
				return step;
			}
		}
		if (function == 3)
		{
			step = 1;
			for (int i = 1; i <= k; i++)
				step *= (x / i);
			return step;
		}
	}

	void Sravnenie()
	{
		if (function == 1)
		{
			cout << "Raznica= " << sin(x) - Sin() << endl;
		}
		if (function == 2)
		{
			cout << "Raznica= " << cos(x) - Cos() << endl;
		}
		if (function == 3)
		{
			cout << "Raznica= " << exp(x) - Exp() << endl;
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


	double Result()
	{
		if (function == 1)
			return Sin();
		if (function == 2)
			return Cos();
		if (function == 3)
			return Exp();
	}
	double Sin()
	{
		double step = x;
		double sum = x;
		for (int i = 3; i <= n; i++, i++)
		{
			step *= ((-1)*x*x / (i*(i - 1)));
			sum += step;
		}
		return sum;

	}

	double Cos()
	{
		double step = 1;
		double sum = 1;
		for (int i = 2; i <= n; i++, i++)
		{
			step *= ((-1)*x*x / (i*(i - 1)));
			sum += step;
		}
		return sum;

	}
	double Exp()
	{
		double step = 1;
		double sum = 1;
		for (int i = 1; i <= n; i++)
		{
			step *= (x / i);
			sum += step;
		}
		return sum;
	}
};
int main()
{
	Teilor obj1;
	int n = 0, x = 0, f, c;
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
	cout << obj1.Result() << endl;
	cout << "Sravnim s etalonom" << endl;
	obj1.Sravnenie();
	cout << "Vvedite shlen, kotoriy hotite vichislit:'" << endl;
	cin >> c;
	cout << c << "Shlen=" << obj1.Member(c) << endl;
	cout << "Formula:" << endl;
	obj1.Print();
	system("pause");
}