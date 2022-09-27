/* 2153680 ÕÔÁèİÚ ĞÅ°² */
#include <iostream>
using namespace std;

void f_sub(int x)
{
	cout << "x = " << x << endl;
}

void (*f_str(const char* p))(int x)
{
	cout << "str = " << p << endl;
	return f_sub;
}

int main()
{
	void(*(*f[3])(const char* p))(int x);
	f[0] = f_str;
	f[0]("Hello")(2);
	f[0]("Tongji")(7);
	return 0;
}