/* 2153680 赵凌葳 信14 */
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double infinite_integration(double (*type)(double), double high, double low, int n)
{
	double d = (high - low) / n, value = 0;
	for (double x = low+d; x <= high; x += d)
		value += d * type(x);
	return value;
}

int main()
{
	int n;
	double low, high, value;

	cout << "请输入sinxdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;
	value = infinite_integration(sin, high, low, n);
	cout << "sinxdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;

	cout << "请输入cosxdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;
	value = infinite_integration(cos, high, low, n);
	cout << "cosxdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;;

	cout << "请输入e^xdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;
	value = infinite_integration(exp, high, low, n);
	cout << "e^xdx[" << low << "~" << high << "/n=" << n << "] : " << value;

	cout << endl;
	return 0;
}