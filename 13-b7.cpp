#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int p[10] = { 1,2,3,4,5,6,7,8,9 };
    //p[12] = 17824820;    //此句越界①
    //p[14] = 14;    //此句越界
    //p[15] = 15;    //此句越界
    //p[10] = '\xfd'; //此句越界②
    cout << "addr:" << hex << (void*)(p) << endl;
    for (int i = -4; i < 16; i++) //注意，只有0-9是合理范围，其余都是越界读
        cout << hex << (void*)(p + i) << ":" << int(p[i]) << endl;
    
    return 0;//25
}
