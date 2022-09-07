/*2153680 信14 赵凌葳*/
//内部数组和伪图形共用的函数
#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;
#include "cmd_console_tools.h"
#include "90-b2.h"

int menu()
{
	char choice = -1;
	cout << "---------------------------------------" << endl;
	cout << "1.命令行找出可合成项并标识（非递归）" << endl;
	cout << "2.命令行找出可合成项并标识（递归）" << endl;
	cout << "3.命令行完成一次合成（分步骤显示）" << endl;
	cout << "4.命令行完整版（分步骤显示）" << endl;
	cout << "5.伪图形界面显示初始数组（无分隔线）" << endl;
	cout << "6.伪图形界面显示初始数组（有分隔线）" << endl;
	cout << "7.伪图形界面下用箭头键/鼠标选择当前色块" << endl;
	cout << "8.伪图形界面完成一次合成（分步骤）" << endl;
	cout << "9.伪图形界面完整版(支持鼠标)" << endl;
	cout << "---------------------------------------" << endl;
	cout << "0.退出" << endl;
	cout << "---------------------------------------" << endl;
	cout << "[请选择:]" ;
	while (choice < '0' || choice > '9')
		choice = _getch();
	return choice - '0';
}

void reset(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2])
{
	for (int i = 0; i < hangmax; i++)
		for (int j = 0; j < liemax; j++)
			a[i][j] = -1;
	for (int i = 0; i < hangmax + 2; i++)
		for (int j = 0; j < liemax + 2; j++)
			a_copy[i][j] = -1;
}

void shuru_hl(int& hang, int& lie)
{
	while (1) {
		cout << "请输入行数(" << hangmin << "-" << hangmax << ")：" << endl;
		cin>>hang;
		if (hang >= hangmin && hang <= hangmax)
			break;
		cin.clear();
		cin.ignore(100000, '\n');
	}
	while (1) {
		cout << "请输入列数(" << liemin << "-" << liemax << ")：" << endl;
		cin >> lie;
		if (lie >= liemin && lie <= liemax)
			break;
		cin.clear();
		cin.ignore(100000, '\n');
	}
}

void shuru_xy(int hang, int lie, char xy[3])
{
	getchar();
	int coordx = 0, coordy = 0;
	cout << "请以字母+数字形式[例：c2]输入矩阵坐标：";
	while (1) {
		cct_getxy(coordx, coordy);

		fgets(xy,3,stdin);
        if (xy[0] >= 'a' && xy[0] <= ('a' + hang))
			xy[0] -= 'a' - 'A';
		xy[0] -= 'A';
		xy[1] -= '0';
		if (xy[0] >= 0 && xy[0] <= hang && xy[1] >= 0 && xy[1] < lie)
			break;
		else {
			cct_gotoxy(coordx, coordy);
			cout << "                    " << endl;
			cout << "输入错误，请重新输入.";
			cct_gotoxy(coordx, coordy);
		}
	}
	cout << "输入为"<<char(xy[0]+'A')<<"行"<< char(xy[1] + '0')<< "列" << endl;
	cout << endl;
}

void random(int a[hangmax][liemax], int max, int hang, int lie)
{
	int rate = 0;
	srand((unsigned)time(0));
	for (int i = 0; i < hang; i++)
		for (int j = 0; j < lie; j++) {
			if (a[i][j] == -1) 
				a[i][j] = rand() % 3 + 1;
			else if (a[i][j] == 0)
				switch (max) {
					case 1:
					case 2:
					case 3:
						a[i][j] = 1 + rand() % 3;
						break;
					case 4:
						rate = 1 + rand() % 10;
						if (rate == 1)
							a[i][j] = 4;
						else
							a[i][j] = 1 + rand() % 3;
						break;
					case 5:
						rate = 1 + rand() % 20;
						if (rate == 1 || rate == 2)
							a[i][j] = 5;
						else if (rate == 3 || rate == 4 || rate == 5)
							a[i][j] = 4;
						else
							a[i][j] = 1 + rand() % 3;
						break;
					case 6:
						rate = 1 + rand() % 20;
						if (rate == 1)
							a[i][j] = 6;
						else if (rate == 2 || rate == 3 || rate == 4)
							a[i][j] = 5;
						else 
							a[i][j] = 1 + rand() % 4;
						break;
					default:
						rate = 1 + rand() % 20;
						if (rate == 1)
							a[i][j] = max;
						else if (rate == 2)
							a[i][j] = max - 1;
						else if (rate == 3 || rate == 4)
							a[i][j] = max - 2;
						else 
							a[i][j] = 1 + rand() % (max - 4);
						break;
				}
		}
}


void fuzhi(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2],int a_for_copy)
{
	for (int i = 0; i < hangmax; i++)
		for (int j = 0; j < liemax; j++)
			if (a[i][j] != -1 && a_for_copy)
				a_copy[i + 1][j + 1] = a[i][j];
			else
				a[i][j] = a_copy[i + 1][j + 1];
}

int search_no(int a_copy[hangmax + 2][liemax + 2], int x, int y)
{
	int value = a_copy[x+1][y+1];
	a_copy[x+1][y+1] = 0;
	int former = 1, latter = 0;
	while (former != latter) {
		former = latter;
		for (int i = 1; i < hangmax + 1; i++)
			for (int j = 1; j < liemax + 1; j++) 
				if (a_copy[i][j] == 0) {
					if (a_copy[i - 1][j] == value) {
						a_copy[i - 1][j] = 0;
						latter++;
					}
					if (a_copy[i + 1][j] == value) {
						a_copy[i + 1][j] = 0;
						latter++;
					}
					if (a_copy[i][j - 1] == value) {
						a_copy[i][j - 1] = 0;
						latter++;
					}
					if (a_copy[i][j + 1] == value) {
						a_copy[i][j + 1] = 0;
						latter++;
					}
				}
	}
	return latter;
}

int search(int a_copy[hangmax + 2][liemax + 2], int x, int y,int value)
{
	static int  count = 0;
	a_copy[x][y] = 0;
	if (x > 0 && x < (hangmax + 2) && y>0 && y < (liemax + 2)) {
		if (a_copy[x - 1][y] == value) {
			count++;
			a_copy[x - 1][y] = 0;
			search(a_copy, x - 1, y, value);
		}
		if (a_copy[x + 1][y] == value) {
			count++;
			a_copy[x + 1][y] = 0;
			search(a_copy, x + 1, y, value);
		}
		if (a_copy[x][y - 1] == value) {
			count++;
			a_copy[x][y - 1] = 0;
			search(a_copy, x, y - 1, value);
		}
		if (a_copy[x][y + 1] == value) {
			count++;
			a_copy[x][y + 1] = 0;
			search(a_copy, x, y + 1, value);
		}
	}
	return count;
}


void huiche(int type)
{
	int coordx = 0, coordy = 0;
	char ch = 0;
	if (type >= 0) {
		cout << "按回车键进行";
		if (!type)
			cout << "数组下落除0操作..." << endl;
		else
			cout << "新值填充..." << endl;
	}
	else if(type==-1)
		cout << "本次合成结束，按回车键继续新一次的合成..." << endl;

	while (1) {
		cct_getxy(coordx, coordy);
		ch = _getch();
		if (ch == '\r')
			break;
		cct_gotoxy(coordx, coordy);
	}
}


void tj_exit()
{
	cout << "本小题结束，请输入End继续...";
	int coordx=0, coordy=0;
	char end[4];
	while (1) {
		cct_getxy(coordx, coordy);
		cin >> end;
		if ((end[0]=='e'||end[0]=='E')&& (end[1] == 'n' || end[1] == 'N')&& (end[2] == 'd' || end[2] == 'D'))
			break;
		else {
			cct_gotoxy(coordx, coordy);
			cout << "                    " << endl;
			cout << "输入错误，请重新输入.";
			cct_gotoxy(coordx, coordy);
		}
	}
}

void aim(int& target)
{
	while (1) {
		cout << "请输入合成目标(" << targetmin << "-" << targetmax << ")：" << endl;
		cin >> target;
		if (target >= 5 && target <= 20)
			break;
		cin.clear();
		cin.ignore(100000, '\n');
	}
}