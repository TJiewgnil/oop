#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int p[10] = { 1,2,3,4,5,6,7,8,9 };
    //p[12] = 17824820;    //�˾�Խ���
    //p[14] = 14;    //�˾�Խ��
    //p[15] = 15;    //�˾�Խ��
    //p[10] = '\xfd'; //�˾�Խ���
    cout << "addr:" << hex << (void*)(p) << endl;
    for (int i = -4; i < 16; i++) //ע�⣬ֻ��0-9�Ǻ���Χ�����඼��Խ���
        cout << hex << (void*)(p + i) << ":" << int(p[i]) << endl;
    
    return 0;//25
}
