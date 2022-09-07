/*2153680 信14 赵凌葳*/
//伪图形各函数
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
using namespace std;
#include "90-b2.h"
#include "cmd_console_tools.h"

void print_fig(int a[hangmax][liemax], int hang, int lie, int choice)//╃╔╗╚╝╟│╢─╤╧║═
{
	cout << setiosflags(ios::left)<<setw(2 + 2) << " ";
	for (int i = 0; i < lie; i++) {
		cout << setw(2) << " " << setw(2) << i << setw(2) << " ";
		Sleep(10);
		if (choice != 5)
			cout << setw(2) << " ";
	}
	cout << endl;
	cout << setw(2) << " ";
	cct_setcolor(COLOR_WHITE, COLOR_BLACK);
	cout << "╔";
	for (int i = 0; i < lie; i++) {
		cout << "═══";
		Sleep(10);
		if (i == (lie - 1))
			cout << "╗" << endl;
		else if(choice!=5)
			cout << "╤";
	}
	for (int i = 0; i < hang; i++) {
		for (int m = 0; m < 4; m++) {
			if (choice == 5 && m == 3 && i != hang - 1)
				break;
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			if (m == 1)
				cout << setw(2) << char('A' + i);
			else
				cout << setw(2) << " ";
			cct_setcolor(COLOR_WHITE, COLOR_BLACK);
			if (m == 3) {
				if (i == hang - 1)
					cout << "╚";
				else if (choice != 5)
					cout << "╟";
			}
			else
				cout << "║";
			Sleep(10);
			for (int j = 0; j < lie; j++) {
				if (m == 3) {
					if (i == hang - 1)
						cout << "═══";
					else if (choice != 5)
						cout << "───";
				}
				else {
					cct_setcolor(a[i][j], COLOR_BLACK);
					if (m == 0)
						cout << "╔═╗";
					else if (m == 1)
						cout << "║" << setw(2) << a[i][j] << "║";
					else if (m == 2)
						cout << "╚═╝";
					cct_setcolor(COLOR_WHITE, COLOR_BLACK);
				}
				Sleep(10);
				if (j == lie - 1)
					if (m == 3) {
						if (i == hang - 1)
							cout << "╝";
						else if (choice != 5)
							cout << "╢";
					}
					else
						cout << "║";
				else
					if (m == 3) {
						if ((i == hang - 1) && (choice != 5))
							cout << "╧";
						else if (choice != 5)
							cout << "╃";
					}
					else if (choice != 5)
						cout << "│";
			}
			if(!(m==3&&choice==5))
			cout << endl;
		}
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << endl;
}

void element(int value, int x, int y, int black)
{
	cct_gotoxy(5 + 8 * x - 1, 4 + 4 * y - 1);
	if (black==1)
		cct_setcolor(value, COLOR_BLACK);
	else if(black==-1)
		cct_setcolor(value, COLOR_WHITE);
	else if(!black)
		cct_setcolor(value, COLOR_HWHITE);
	else if(black==-2)
		cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
	if (black != -2)
		cout << "╔═╗";
	else
		cout << "      ";
	cct_gotoxy(5 + 8 * x - 1, 4 + 4 * y);
	if (black != -2)
		cout << "║" << setw(2) << value << "║";
	else
		cout << "      ";
	cct_gotoxy(5 + 8 * x - 1, 4 + 4 * y + 1);
	if (black != -2)
		cout << "╚═╝";
	else
		cout << "      ";
}

void move(int a[hangmax][liemax], int hang,int lie,int choice,int& x,int& y)
{
	//base y=4 *4   x=5   *8
	//choosen  x-1 |y-1   *3*3
	//huirao   a[i][j]=-1 if(right)goto a[i][0]
	int MX = 0, MY = 0, MAction = 0, keycode1 = 0, keycode2 = 0,ret=0;
	x = 0; y = 0;
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(0, hang * 4 + 4);
	cout << "箭头键/鼠标移动，回车键/单击左键选择";
	if (choice == 7)
		cout << "并结束";
	else 
		cout << "，Q/单击右键结束";
	cct_enable_mouse();
	while (1) {
		ret = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT) {
			if (MAction == MOUSE_ONLY_MOVED) {
				element(a[y][x], x, y, 1);
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cct_gotoxy(0, hang * 4 + 3);
				cout << "x=" << MX << " y=" << MY;
				for (int m = 0; m < hang; m++)
					for (int n = 0; n < lie; n++)
						for (int i = -2; i <= 2; i++)
							for (int j = -1; j <= 1; j++)
								if ((MX == (6 + 8 * n + i)) && (MY == (4 + 4 * m + j))) {
									element(a[m][n], n, m, 0);
									x = n;
									y = m;
									break;
								}
			}
			if (MAction == MOUSE_LEFT_BUTTON_CLICK)
				break;
		}
		else if (ret == CCT_KEYBOARD_EVENT) {
			if (keycode1 == '\r')
				break;
			element(a[y][x], x, y, 1);
			if (keycode2 == KB_ARROW_UP)
				if (y == 0)
					y = hang - 1;
				else
					y--;
			else if (keycode2 == KB_ARROW_DOWN)
				if (y == hang - 1)
					y = 0;
				else
					y++;
			else if (keycode2 == KB_ARROW_LEFT)
				if (x == 0)
					x = lie - 1;
				else
					x--;
			else if (keycode2 == KB_ARROW_RIGHT)
				if (x == lie - 1)
					x = 0;
				else
					x++;
			element(a[y][x], x, y, 0);
			cct_gotoxy(0, hang * 4 + 3);
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			if (choice >= 8)
				cout << "[当前键盘]" << char(y + 'A') << "行" << x << "列";
		}
	}
	if (choice == 7)
		cout << "选中了" << y << "行" << x << "列" << endl;
}

void print_pro(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int x, int y, int hang, int lie, int value, int& score, int target, int choice, int leave)
{
	while (1) {
		int score_once = 0, quantity = 0, move = 0, click = 0, arrow = 0;
		for (int i = 0; i < hangmax + 2; i++)
			for (int j = 0; j < liemax + 2; j++)
				if (!a_copy[j][i])
					element(value, i - 1, j - 1, -1);
		quantity++;
		element(value, x, y, 0);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		if (choice == 9) {
			score_once = value * quantity * scoretime;
			score += score_once;
			cct_gotoxy(0, 0);
			cout << "本次得分：" << score_once << " 总得分：" << score << " 合成目标：" << target << endl;
		}
		if (choice >= 8) {
			cct_gotoxy(0, hang * 4 + 3);
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键选择合并";
			mk(move, click, arrow);
			if (click == KB_ARROW_RIGHT || move) {
				leave = 1;
				break;
			}
			else {
				for (int i = 0; i < hangmax + 2; i++)
					for (int j = 0; j < liemax + 2; j++)
						if (!a_copy[i][j])
							element(value, j - 1, i - 1, 1);
			}
		}
		fuzhi(a, a_copy, 0);
		cct_gotoxy(0, hang * 4 + 3);
		huiche(-2);
		for (int i = 0; i < hangmax + 2; i++)
			for (int j = 0; j < liemax + 2; j++)
				if (!a_copy[i][j])
					element(value, j - 1, i - 1, -2);
		a[y][x]++;
		if (value < a[y][x])
			value = a[y][x];
		for (int n = 0; n < 20; n++) {
			element(value, x, y, 1);
			Sleep(20);
			element(value, x, y, 0);
		}
		if (choice == 8) {
			cct_gotoxy(0, hang * 4 + 3);
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			cout << "合成完成，回车键/单击左键下落0";
			while (1) {
				mk(move, click, arrow);
				if (arrow == '\r' || click)
					break;
			}
			move = 0;
			click = 0;
			arrow = 0;
		}
		huiche(-2);
		for (int j = 0; j < lie; j++)
			for (int i = hang - 1; i > 0; i--)
				if (!a[i][j])
					for (int k = i - 1; k >= 0; k--)
						if (a[k][j]) {
							element(a[k][j], j, k, -2);
							Sleep(15);
							element(a[k][j], j, k + 1, 1);
							Sleep(15);
							a[k + 1][j] = a[k][j];
							a[k][j] = 0;
							j -= 2;
							break;
						}
		if (choice == 8) {
			cct_gotoxy(0, hang * 4 + 3);
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			cout << "下落0完成，回车/单击左键赋新值";
		}
		fuzhi(a, a_copy, 1);
		random(a, value, hang, lie);
		for (int i = 0; i < hang; i++)
			for (int j = 0; j < lie; j++)
				if (!a_copy[j + 1][i + 1]) {
					element(a[j][i], i, j, 1);
					Sleep(20);
				}
		cct_gotoxy(0, hang * 4 + 3);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << "本次合成结束，按C或单击左键继续新一次合成";
		while (1) {
			mk(move, click, arrow);
			if (arrow == 'C' || click) {
				leave = 1;
				break;
			}
		}
	}
}

void mk(int& move, int& click, int& arrow)
{
	int MX = 0, MY = 0, MAction = 0, keycode1 = 0, keycode2 = 0, ret = 0;
	cct_enable_mouse();
	while (1) {
		ret = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT) {
			if (MAction == MOUSE_ONLY_MOVED) {
				move = 1;
				break;
			}
			if (MAction == MOUSE_LEFT_BUTTON_CLICK) {
				click = 1;
				break;
			}
		}
		else if (ret == CCT_KEYBOARD_EVENT) {
			if (keycode1 == '\r') {
				arrow = '\r';
				break;
			}
			if (keycode1 == 'c' || keycode1 == 'C') {
				arrow = 'c';
				break;
			}
			if (keycode2 == KB_ARROW_LEFT) {
				arrow = KB_ARROW_LEFT;
				break;
			}
			if ((keycode2 == KB_ARROW_RIGHT) || (keycode2 == KB_ARROW_UP) || (keycode2 == KB_ARROW_DOWN)) {
				arrow = KB_ARROW_RIGHT;
				break;
			}
		}
	}

}