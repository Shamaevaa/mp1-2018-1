#include <iostream>
#include <math.h> 
using namespace std;
class TaylorSeries
{
	int n;
	int function;
	double x;
public:
	TaylorSeries(int _n = 0, double _x = 0, int _function = 0)
	{
		n = _n;
		x = _x;
		function = _function;
	}
	~TaylorSeries()
	{
	}
	TaylorSeries& operator=(const TaylorSeries& ob)
	{
		n = ob.n;
		x = ob.x;
		function = ob.function;
		return *this;
	}
	TaylorSeries(const TaylorSeries &ob1)
	{
		x = ob1.x;
		n = ob1.n;
		function = ob1.function;
	}
	void SetFunction(int f)
	{
		function = f;
	}
	void SetCount(int _n)
	{
		n = _n;
	}
	void SetPoint(double _x)
	{
		x = _x;
	}
	int GetFunction(void)
	{
		return function;
	}
	int GetCount(void)
	{
		return n;
	}
	double GetPoint(void)
	{
		return x;
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
			cout << "Difference with the standard= " << sin(x) - ResultOfFunctionEvaluation() << endl;
			break;
		}
		case 2:
		{
			cout << "Difference with the standard = " << cos(x) - ResultOfFunctionEvaluation() << endl;
			break;
		}
		case 3:

		{
			cout << "Difference with the standard= " << exp(x) - ResultOfFunctionEvaluation() << endl;
			break;
		}
		}
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
	int n = 0;
	int x = 0;
	int m = 1;
	int f, c, l;
	TaylorSeries obj1;
	while (m == 1)
	{
		cout << "Menu:" << endl;
		cout << "1) Set the current function " << endl;
		cout << "2) Get the current function " << endl;
		cout << "3) Set number of elements " << endl;
		cout << "4) Set the current number of members of the series " << endl;
		cout << "5) Set the current number of members of the series" << endl;
		cout << "6) Give the value of a given member of the series " << endl;
		cout << "7) Ñalculate the value of the series in the fired point õ " << endl;
		cout << "8) Output the deviation of the value of the series at the selected point from the reference value " << endl;
		cout << "Enter: ";
		cin >> l;
		system("cls");
		switch (l)
		{
		case 1:
		{
			cout << "Choose function \n" << endl;
			cout << "1.Sin(x)" << endl;
			cout << "2.Cos(x)" << endl;
			cout << "3.Exp(x)" << endl;
			cout << "Your choice: ";
			cin >> f;
			obj1.SetFunction(f);
			system("pause");
			system("cls");
			break;
		}
		case 2:
		{
			switch (obj1.GetFunction())
			{
			case 1:
			{
				cout << "Sin(x)" << endl;
				break;
			}
			case 2:
			{
				cout << "Cos(x)" << endl;
				break;
			}
			case 3:
			{
				cout << "Exp(x)" << endl;
				break;
			}
			}
			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			cout << "Enter the number of members of the series: ";
			cin >> n;
			obj1.SetCount(n);
			system("pause");
			system("cls");
			break;
		}
		case 4:
		{
			cout << obj1.GetCount() << endl;
			system("pause");
			system("cls");
			break;
		}
		case 5:
		{
			cout << "Enter the number of members of the series: ";
			cin >> n;
			obj1.SetCount(n);
			cout << "Formula: " << endl;
			obj1.Print();
			system("pause");
			system("cls");
			break;
		}
		case 6:
		{
			cout << "Enter the number of members of the series: ";
			cin >> n;
			obj1.SetCount(n);
			cout << "Enter the point x :";
			cin >> x;
			obj1.SetPoint(x);
			cout << "Enter the member who you want to calculate : ";
			cin >> c;
			cout << c << "Member of series =" << obj1.GetMemberOfSeries(c) << endl;
			system("pause");
			system("cls");
			break;
		}

		case 7:
		{
			cout << "Enter the number of members of the series: ";
			cin >> n;
			obj1.SetCount(n);
			cout << "Enter the point x: ";
			cin >> x;
			obj1.SetPoint(x);
			switch (obj1.GetFunction())
			{
			case 1:
			{
				cout << "Result\n" << obj1.ResultOfFunctionEvaluation() << endl;
				break;
			}
			case 2:
			{
				cout << "Result\n" << obj1.ResultOfFunctionEvaluation() << endl;
				break;
			}
			case 3:
			{
				cout << "Result\n" << obj1.ResultOfFunctionEvaluation() << endl;
				break;
			}
			}
			system("pause");
			system("cls");
			break;
		}
		case 8:
		{
			cout << "Enter the number of members of the series: ";
			cin >> n;
			obj1.SetCount(n);
			cout << "Enter the point x :";
			cin >> x;
			obj1.SetPoint(x);
			obj1.Comparison();
			system("pause");
			system("cls");
			break;
		}
		}
	}
}
