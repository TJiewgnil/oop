/*2153680 信14 赵凌葳*/
//内部数组实现的各函数
#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;
#include "cmd_console_tools.h"
#include "90-b2.h"

void print_num(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int mark)
{
	if (mark == -1) {
		cout << endl;
		cout << "当前数组：" << endl;
	}
	else if (mark == 0)
		cout << "查找结果数组：" << endl;
	else if (mark == 1)
		cout << "当前数组(不同色标识)：" << endl;
	cout << "  | ";
	int lie = 0, hang = 0;
	for (; lie < liemax; lie++)
		if (a[0][lie] == -1)
			break;
	for (; hang < hangmax; hang++)
		if (a[hang][0] == -1)
			break;

	for (int j = 0; j < lie; j++)
		cout << " " << j << " ";
	cout << endl;
	cout << "--+-";
	for (int j = 0; j < lie; j++)
		cout << "---";
	cout << endl;

	for (int i = 0; i < hang; i++) {
		for (int j = 0; j < lie; j++) {
			if (!j)
				cout << char('A' + i) << " | ";
			if (mark) {
				cout << " ";
				if (!a_copy[i + 1][j + 1] && mark != -1)
					cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
				cout << a[i][j];
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << " ";
			}
			else if (!mark)
				if (!a_copy[i + 1][j + 1])
					cout << " " << "*" << " ";
				else
					cout << " " << 0 << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void hebing(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int x, int y, int& score, int target, int& max)
{
	int value = a[x][y], yes = 0, coordx = 0, coordy = 0, jump = 0, quantity = 0, hang = hangmax, lie = liemax, score_once = 0;
	while (1) {
		cout << "请确认是否把相邻的相同值合并到" << char(x + 'A') << char(y + '0') << "中(Y/N/Q)：";
		while (1) {
			cct_getxy(coordx, coordy);
			yes = _getch();
			if (yes == 'y' || yes == 'Y')
				break;
			else if (yes == 'n' || yes == 'N')
				jump = 1;
			else if (yes == 'q' || yes == 'Q')
				jump = -1;
			else {
				cct_gotoxy(coordx, coordy);
				continue;
			}
			break;
		}
		if (jump) {
			cout << endl;
			break;
		}
		for (int i = hangmax - 1; i >= 0; i--)//合并
			for (int j = 0; j < liemax; j++)
				if (!a_copy[i + 1][j + 1]) {
					a[i][j] = 0;
					quantity++;
				}
				else if ((a_copy[i + 1][j + 1] == -1) && hang == hangmax && lie == liemax) {
					hang = i - 1;
					lie = j - 1;
				}
		score_once = value * quantity * scoretime;
		score += score_once;
		max = ++value;
		a[x][y] = value;
		cout << endl;
		cout << "相同值归并后的数组(不同色标识)：" << endl;
		print_num(a, a_copy, 2);
		cout << "本次得分：" << score_once << " 总得分：" << score << " 合成目标：" << target << endl;
		cout << endl;
		break;
	}
}

void xialuo(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2])
{
	cout << "除0后的数组(不同色标识)：" << endl;
	for (int i = hangmax - 1; i > 0; i--)
		for (int j = 0; j < liemax; j++)
			if (!a[i][j])
				for (int k = i - 1; k >= 0; k--)
					if (a[k][j]) {
						a[i][j] = a[k][j];
						a[k][j] = 0;
						break;
					}
	fuzhi(a, a_copy, 1);
	print_num(a, a_copy, 2);
	cout << endl;
}

void tianchong(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int max, int hang, int lie)
{
	random(a, max, hang, lie);
	print_num(a, a_copy, 2);
}
