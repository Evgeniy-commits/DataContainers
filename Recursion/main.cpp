#include <iostream>
using namespace std;

void elevator(int floor);
unsigned long long factorial(int number);
double power(double base, int exponent);
int fibonachy(int n);
void printFib(int limit);

void main()
{
	setlocale(LC_ALL, "");
	int n;
	double base;
	int exponent;
	//cout << "Введите номер этажа: "; cin >> n;
	//elevator(n);
	//cout << "факториал какого числа найти: "; cin >> n;
	//cout << n << "!= " << factorial(n) << endl;
	/*cout << "Введите основание степени: "; cin >> base;
	cout << "Введите показатель степени: "; cin >> exponent;
	cout << base << " в степени " << exponent << " = " << power(base, exponent) << endl;

	cout << "Введите показатель степени: "; cin >> exponent;
	cout << base << " в степени " << exponent << " = " << power(base, exponent) << endl;*/

	int limit;
	cout << "Введите предел, до которого выводить ряд Фибоначчи: ";	cin >> limit;
	printFib(limit);
}

void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Вы в подвале" << endl;
		return;
	}
	cout << "Вы на " << floor << " этаже" << endl;
	elevator(floor - 1);
	cout << "Вы на " << floor << " этаже" << endl;	
}

unsigned long long factorial(int number)
{
	if (number == 0 || number == 1) return 1;
	return number * factorial(number - 1);
}

double power(double base, int exponent)
{
	return exponent == 0 ? 1 :
		   exponent < 0 ? 1 / base * power(base, exponent + 1) :
		   base * power(base, exponent - 1);
}

int fibonachy(int n) 
{
	return n <= 1 ? n : (fibonachy(n - 1) + fibonachy(n - 2));
}

void printFib(int limit)
{
	for (int n = 0; !(fibonachy(n) > limit); n++) cout << fibonachy(n) << "\t";
	cout << endl;
}