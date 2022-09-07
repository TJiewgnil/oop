/*2153680 ��14 ������*/
//�ڲ������αͼ�ι��õĺ���
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
	cout << "1.�������ҳ��ɺϳ����ʶ���ǵݹ飩" << endl;
	cout << "2.�������ҳ��ɺϳ����ʶ���ݹ飩" << endl;
	cout << "3.���������һ�κϳɣ��ֲ�����ʾ��" << endl;
	cout << "4.�����������棨�ֲ�����ʾ��" << endl;
	cout << "5.αͼ�ν�����ʾ��ʼ���飨�޷ָ��ߣ�" << endl;
	cout << "6.αͼ�ν�����ʾ��ʼ���飨�зָ��ߣ�" << endl;
	cout << "7.αͼ�ν������ü�ͷ��/���ѡ��ǰɫ��" << endl;
	cout << "8.αͼ�ν������һ�κϳɣ��ֲ��裩" << endl;
	cout << "9.αͼ�ν���������(֧�����)" << endl;
	cout << "---------------------------------------" << endl;
	cout << "0.�˳�" << endl;
	cout << "---------------------------------------" << endl;
	cout << "[��ѡ��:]" ;
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
		cout << "����������(" << hangmin << "-" << hangmax << ")��" << endl;
		cin>>hang;
		if (hang >= hangmin && hang <= hangmax)
			break;
		cin.clear();
		cin.ignore(100000, '\n');
	}
	while (1) {
		cout << "����������(" << liemin << "-" << liemax << ")��" << endl;
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
	cout << "������ĸ+������ʽ[����c2]����������꣺";
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
			cout << "�����������������.";
			cct_gotoxy(coordx, coordy);
		}
	}
	cout << "����Ϊ"<<char(xy[0]+'A')<<"��"<< char(xy[1] + '0')<< "��" << endl;
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
		cout << "���س�������";
		if (!type)
			cout << "���������0����..." << endl;
		else
			cout << "��ֵ���..." << endl;
	}
	else if(type==-1)
		cout << "���κϳɽ��������س���������һ�εĺϳ�..." << endl;

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
	cout << "��С�������������End����...";
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
			cout << "�����������������.";
			cct_gotoxy(coordx, coordy);
		}
	}
}

void aim(int& target)
{
	while (1) {
		cout << "������ϳ�Ŀ��(" << targetmin << "-" << targetmax << ")��" << endl;
		cin >> target;
		if (target >= 5 && target <= 20)
			break;
		cin.clear();
		cin.ignore(100000, '\n');
	}
}