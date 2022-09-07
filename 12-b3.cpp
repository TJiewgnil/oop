#include <iostream>
using namespace std;

int main()
{
	const char* month[][10] = { "January","Feburary","March","April","May","June","July","August","September","October","November","December"};
	cout << "ÇëÊäÈëÔÂ·Ý(1-12)" << endl;
	int num;
	cin >> num;
	if (cin.fail() || num > 12 || num < 1 || cin.peek()!='\n')
		cout << "Invalid" << endl;
	else
		cout << *(*month + num - 1) << endl;
	return 0;
}