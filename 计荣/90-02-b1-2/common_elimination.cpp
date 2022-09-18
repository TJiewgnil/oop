#include <iostream>
#include "../include/cmd_console_tools.h"
#include "../90-02-b1/90-02-b1.h"
#include <conio.h>
#include <iomanip>
#include <windows.h>
using namespace std;

void apartline(int length)
{
	for (int i = 0; i < length; i++)
		cout << "=";
	cout << endl;
}

void shuru_hl(int& hang, int& lie)
{
	while (1) {
		cout << "请输入行数(" << hangmin << "-" << hangmax << ")：" << endl;
		cin >> hang;
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

void print_num(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int mark)
{
	if (mark == print_array) {
		cout << endl;
		cout << "当前数组：" << endl;
	}
	else if (mark == print_array_sign)
		cout << "查找结果数组：" << endl;
	else if (mark == print_array_color)
		cout << "当前数组(不同色标识)：" << endl;
	cout << "  | ";
	int lie = 0, hang = 0;
	for (; lie < liemax; lie++)
		if (a[0][lie] == array_empty)//changed
			break;
	for (; hang < hangmax; hang++)
		if (a[hang][0] == array_empty)//changed
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
			if (mark!= print_array_sign) {
				cout << " ";
				if (a_copy[i + 1][j + 1]==array_same && mark != print_array)//changed
					cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
				cout << a[i][j];
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << " ";
			}
			else if (mark== print_array_sign)
				if (a_copy[i + 1][j + 1] == array_same)//changed
					cout << " " << "*" << " ";
				else
					cout << " " << 0 << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int menu(const char* menu_content[], const char* menu_options)
{
	char option = 0;
	cout << "请选择：" << endl;
	int i = 0, length = 0;
	while (menu_content[i]) {
		if (strlen(menu_content[i]) > (unsigned int)length)
			length = strlen(menu_content[i]);
		i++;
	}
	i = 0;
	apartline(length);
	while (menu_content[i]) {
		cout << menu_content[i] << endl;
		i++;
	}
	apartline(length);
	while (1) {
		option = _getch();
		int j = 0;
		while (menu_options[j]) {
			if (option >= 'a' && option <= 'z')
				option = option - 'a' + 'A';
			if (menu_options[j] == option)
				return option;
			else
				j++;
		}
	}
}

void shuru_xy(int hang, int lie, char xy[3])
{
	getchar();
	int coordx = 0, coordy = 0, error = 0;
	cout << "请以字母+数字形式[例：c2]输入矩阵坐标：";
	while (1) {
		cct_getxy(coordx, coordy);
		fgets(xy, 3, stdin);
		if (error) {
			cct_gotoxy(0, coordy + 1);
			cout << "                     " << endl;
		}
		error = 0;
		if (xy[0] >= 'a' && xy[0] <= ('a' + hang))
			xy[0] -= 'a' - 'A';
		xy[0] -= 'A';
		xy[1] -= '0';
		if (xy[0] >= 0 && xy[0] <= hang-1 && xy[1] >= 0 && xy[1] < lie)
			break;
		else {
			cct_gotoxy(coordx, coordy);
			cout << "                     " << endl;
			cout << "                                             " << endl;
			cct_gotoxy(0, coordy + 1);
			cout << "输入错误，请重新输入.";
			cct_gotoxy(coordx, coordy);
			error = 1;
		}
	}
	cct_gotoxy(coordx, coordy);
	cout << "输入为" << char(xy[0] + 'A') << "行" << char(xy[1] + '0') << "列" << endl;
	cout << endl;
}

void reset(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2])
{
	for (int i = 0; i < hangmax; i++)
		for (int j = 0; j < liemax; j++)
			a[i][j] = array_empty;//changed
	for (int i = 0; i < hangmax + 2; i++)
		for (int j = 0; j < liemax + 2; j++)
			a_copy[i][j] = array_empty;//changed
}

void random(int a[hangmax][liemax], int max, int hang, int lie,int type)
{
	int rate = 0;
	srand((unsigned)time(0));
	for (int i = 0; i < hang; i++)
		for (int j = 0; j < lie; j++) {
			if (type == star_eli)
				a[i][j] = rand() % 5 + 1;
			else if (type == syn_ten) {
				if (a[i][j] == array_empty)//changed
					a[i][j] = rand() % 3 + 1;
				else if (a[i][j] == array_zero)//changed
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
}

void copy(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int a_to_copy)
{
	for (int i = 0; i < hangmax; i++)
		for (int j = 0; j < liemax; j++)
			if (a[i][j] != array_empty)
				if (a_to_copy == array_to_copy)
					a_copy[i + 1][j + 1] = a[i][j];
				else
					a[i][j] = a_copy[i + 1][j + 1];
}

int search_no(int a_copy[hangmax + 2][liemax + 2], int x, int y)
{
	int value = a_copy[x + 1][y + 1];
	a_copy[x + 1][y + 1] = array_same;
	int former = 1, latter = 0;
	while (former != latter) {
		former = latter;
		for (int i = 1; i+1 < hangmax + 2; i++)
			for (int j = 1; j+1 < liemax + 2; j++)
				if (a_copy[i][j] == array_same) {
					if (a_copy[i - 1][j] == value) {
						a_copy[i - 1][j] = array_same;
						latter++;
					}
					if (a_copy[i + 1][j] == value) {
						a_copy[i + 1][j] = array_same;
						latter++;
					}
					if (a_copy[i][j - 1] == value) {
						a_copy[i][j - 1] = array_same;
						latter++;
					}
					if (a_copy[i][j + 1] == value) {
						a_copy[i][j + 1] = array_same;
						latter++;
					}
				}
	}
	if(!latter)
		a_copy[x + 1][y + 1] = value;
	return latter;
}

int search(int a_copy[hangmax + 2][liemax + 2], int x, int y, int value, int& same_last)
{
	int same = search_find_same(a_copy, x, y, value);
	if (same == same_last) {
		a_copy[x][y] = value;
		return 0;
	}
	else {
		same_last = same;
		return 1;
	}
}

int search_find_same(int a_copy[hangmax + 2][liemax + 2], int x, int y, int value)
{
	static int  same = 0;
	a_copy[x][y] = array_same;
	if (x - 1 >= 0 && x + 1 < (hangmax + 2) && y - 1 >= 0 && y + 1 < (liemax + 2)) {
		if (a_copy[x - 1][y] == value) {
			same++;
			a_copy[x - 1][y] = array_same;
			search_find_same(a_copy, x - 1, y, value);
		}
		if (a_copy[x + 1][y] == value) {
			same++;
			a_copy[x + 1][y] = array_same;
			search_find_same(a_copy, x + 1, y, value);
		}
		if (a_copy[x][y - 1] == value) {
			same++;
			a_copy[x][y - 1] = array_same;
			search_find_same(a_copy, x, y - 1, value);
		}
		if (a_copy[x][y + 1] == value) {
			same++;
			a_copy[x][y + 1] = array_same;
			search_find_same(a_copy, x, y + 1, value);
		}
	}
	return same;
}

void tj_exit()
{
	cout << "本小题结束，请输入End继续...";
	int coordx = 0, coordy = 0;
	char end[4];
	while (1) {
		cct_getxy(coordx, coordy);
		cin >> end;
		if ((end[0] == 'e' || end[0] == 'E') && (end[1] == 'n' || end[1] == 'N') && (end[2] == 'd' || end[2] == 'D'))
			break;
		else {
			cct_gotoxy(coordx, coordy);
			cout << "                    " << endl;
			cout << "输入错误，请重新输入.";
			cct_gotoxy(coordx, coordy);
		}
	}
}

int combi_or_eli(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int x, int y, int& score, int type)
{
	int value = a[x][y], yes = 0, coordx = 0, coordy = 0, jump = 0, quantity = 0, score_once = 0;
	if (type == syn_ten)
		cout << "请确认是否把相邻的相同值合并到" << char(x + 'A') << char(y + '0') << "中(Y/N/Q)：";
	else if (type == star_eli)
		cout << "请确认是否把相邻的相同值消除(Y/N/Q)：";
	while (1) {
		cct_getxy(coordx, coordy);
		yes = _getch();
		if (yes == 'y' || yes == 'Y')
			jump = combi_eli_Y;
		else if (yes == 'n' || yes == 'N')
			jump = combi_eli_N;
		else if (yes == 'q' || yes == 'Q')
			jump = combi_eli_Q;
		else {
			cct_gotoxy(coordx, coordy);
			continue;
		}
		break;
	}
	if (jump != combi_eli_Y) {
		if (jump == combi_eli_N)
			for (int i = 1; i < hangmax - 1; i++)//还原search中被标记的数据
				for (int j = 1; j < liemax - 1; j++)
					if (a_copy[i][j] == array_same)
						a_copy[i][j] = value;
		cout << endl;
		return jump;
	}
	for (int i = hangmax - 1; i >= 0; i--)//合并
		for (int j = 0; j < liemax; j++)
			if (a_copy[i + 1][j + 1] == array_same) {
				a[i][j] = array_zero;
				quantity++;
			}
	if (type == syn_ten) {
		score_once = value * quantity * syn_score_times;
		score += score_once;
		a[x][y] = ++value;
	}
	else if (type == star_eli) {
		score_once = quantity * quantity * star_score_times;
		score += score_once;
	}
	cout << endl;
	cout << "相同值归并后的数组(不同色标识)：" << endl;
	print_num(a, a_copy, print_array_color);
	cout << "本次得分：" << score_once;
	return jump;
}//max=value

bool possibility(int a_copy[hangmax + 2][liemax + 2])
{
	int value = 0;
	bool possibility = 0;
	for (int i = 1; i < hangmax + 1; i++) {
		for (int j = 1; j < liemax + 1; j++) 
			if (a_copy[i][j]!=array_empty&& a_copy[i][j] != array_zero) {
				value = a_copy[i][j];
				if (a_copy[i - 1][j] == value || a_copy[i + 1][j] == value || a_copy[i][j - 1] == value || a_copy[i][j + 1] == value) {
					possibility = 1;
					break;
				}
			}
		if (possibility)
			break;
	}
	return possibility;
}

void enter(int content)
{
	int coordx = 0, coordy = 0;
	char key_enter = 0;
	if (content == enter_next)
		cout << "本次合成结束，按回车键继续新一次的合成..." << endl;
	else {
		cout << "按回车键进行";
		if (content == enter_fall)
			cout << "数组下落除0操作..." << endl;
		else if (content == enter_shl)
			cout << "右侧全0列平移操作..." << endl;
		else if (content == enter_fill)
			cout << "新值填充操作..." << endl;
	}

	while (1) {
		cct_getxy(coordx, coordy);
		key_enter = _getch();
		if (key_enter == '\r')
			break;
		cct_gotoxy(coordx, coordy);
	}
}

void fall(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2])
{
	for (int i = hangmax - 1; i > 0; i--)
		for (int j = 0; j < liemax; j++)
			if (!a[i][j])
				for (int k = i - 1; k >= 0; k--)
					if (a[k][j]) {
						a[i][j] = a[k][j];
						a[k][j] = array_zero;
						break;
					}
	copy(a, a_copy, array_to_copy);
	cout << "下落除0后" ;
	print_num(a, a_copy, print_array_color);
	cout << endl;
}

void fill(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int max, int hang, int lie)
{
	random(a, max, hang, lie, syn_ten);
	cout << "0位置产生新值后";
	print_num(a, a_copy, print_array_color);
	copy(a, a_copy, array_to_copy);
	cout << endl;
}

void shl(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2])
{
	int lie, hang;
	for(lie=liemax-1;lie>=0;lie--)
		if (a[0][lie] != array_empty) {
			for (hang = 0; hang < hangmax; hang++)
				if (a[hang][lie])
					break;
			if (a[hang][lie] == array_empty || hang == hangmax - 1)//就将右侧列全部左移1列
				for (int lie_shl = lie; lie_shl < liemax - 1; lie_shl++)
					if (a[0][lie_shl + 1] != array_empty)//-1的列不要移动，if a[0][lie + 1]==-1，全列置0
						for (int hang_shl = 0; hang_shl < hangmax; hang_shl++) {
							if (a[hang_shl][lie_shl] == array_empty)
								break;
							a[hang_shl][lie_shl] = a[hang_shl][lie_shl + 1];
							if (lie_shl + 1 == liemax - 1 || lie_shl + 1 < liemax - 1 && a[0][lie_shl + 2] == array_empty)
								a[hang_shl][lie_shl + 1] = 0;
						}
		}
	cout << "右侧全0列平移后";
	print_num(a, a_copy, print_array_color);
	copy(a, a_copy, array_to_copy);
	cout << endl;
}

void screen_set(int apartline,int hang,int lie)
{
	int cols, lines, buffer_cols, buffer_lines;
	cct_getconsoleborder(cols, lines, buffer_cols, buffer_lines);
	if (apartline==nal) {
		cct_setconsoleborder(lie * 6 + 7, hang * 3 + 10, buffer_cols * hang, buffer_lines * lie);
		cout << "屏幕当前设置为：" << hang * 3 + 10 << "行" << lie * 6 + 7 << "列" << endl;
	}
	else if (apartline == al) {
		cct_setconsoleborder(lie * 8 + 5, hang * 4 + 10, buffer_cols * hang, buffer_lines * lie);
		cout << "屏幕当前设置为：" << hang * 4 + 10 << "行" << lie * 8 + 5 << "列" << endl;
	}
}

void print_element(int type, int value)
{
	if (type == syn_ten)
		cout << setw(2) << value;
	else if (type == star_eli)
		cout << "★";
}

void print_fig(int a[hangmax][liemax], int hang, int lie, int apartline, int type)//╃╔╗╚╝╟│╢─╤╧║═
{
	cout << setiosflags(ios::left) << setw(2 + 2) << " ";
	for (int i = 0; i < lie; i++) {
		cout << setw(2) << " " << setw(2) << i << setw(2) << " ";
		Sleep(10);
		if (apartline == al)
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
		else if (apartline == al)
			cout << "╤";
	}
	for (int i = 0; i < hang; i++) {
		for (int m = 0; m < 4; m++) {
			if (apartline == nal && m == 3 && i != hang - 1)
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
				else if (apartline == al)
					cout << "╟";
			}
			else
				cout << "║";
			Sleep(10);
			for (int j = 0; j < lie; j++) {
				if (m == 3) {
					if (i == hang - 1)
						cout << "═══";
					else if (apartline == al)
						cout << "───";
				}
				else {
					cct_setcolor(a[i][j], COLOR_BLACK);
					if (m == 0)
						cout << "╔═╗";
					else if (m == 1) {
						cout << "║";
						print_element(type, a[i][j]);
						cout << "║";
					}
					else if (m == 2)
						cout << "╚═╝";
					cct_setcolor(COLOR_WHITE, COLOR_BLACK);
				}
				Sleep(10);
				if (j == lie - 1)
					if (m == 3) {
						if (i == hang - 1)
							cout << "╝";
						else if (apartline == al)
							cout << "╢";
					}
					else
						cout << "║";
				else
					if (m == 3) {
						if ((i == hang - 1) && (apartline == al))
							cout << "╧";
						else if (apartline == al)
							cout << "╃";
					}
					else if (apartline == al)
						cout << "│";
			}
			if (!(m == 3 && apartline == nal))
				cout << endl;
		}
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cout << endl;
}

void element(int value, int x, int y, int color, int type, int apartline)
{
	int x_coe = 0, y_coe = 0;
	if (apartline == al) {
		x_coe = 8;
		y_coe = 4;
	}
	else if (apartline == nal) {
		x_coe = 6;
		y_coe = 3;
	}
	cct_gotoxy(5 + x_coe * x - 1, 4 + y_coe * y - 1);
	if (color == element_fg_bl)
		cct_setcolor(value, COLOR_BLACK);
	else if (color == element_fg_wh)
		cct_setcolor(value, COLOR_WHITE);
	else if (color == element_fg_hwh)
		cct_setcolor(value, COLOR_HWHITE);
	else if (color == element_all_hwh)
		cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
	if (color == element_all_hwh)
		cout << "      ";
	else
		cout << "╔═╗";
	cct_gotoxy(5 + x_coe * x - 1, 4 + y_coe * y);
	if (color == element_all_hwh)
		cout << "      ";
	else {
		cout << "║";
		print_element(type, value);
		cout << "║";
	}
	cct_gotoxy(5 + x_coe * x - 1, 4 + y_coe * y + 1);
	if (color == element_all_hwh)
		cout << "      ";
	else
		cout << "╚═╝";
}

void move(int a[hangmax][liemax], int hang, int lie, int& x, int& y, int type, int apartline)
{
	//base y=4 *4   x=5   *8
	//choosen  x-1 |y-1   *3*3
	//huirao   a[i][j]=-1 if(right)goto a[i][0]
	int MX = 0, MY = 0, MAction = 0, keycode1 = 0, keycode2 = 0, ret = 0, hang_coe = 3 + apartline;
	x = 0; y = 0;
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(0, hang * hang_coe + 4);
	cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束";
	cct_enable_mouse();
	while (1) {
		ret = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT) {
			if (MAction == MOUSE_ONLY_MOVED) {
				element(a[y][x], x, y, element_fg_bl, type, apartline);
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cct_gotoxy(0, hang * 4 + 3);
				cout << "x=" << MX << " y=" << MY;
				for (int m = 0; m < hang; m++)
					for (int n = 0; n < lie; n++)
						for (int i = -2; i <= 2; i++)
							for (int j = -1; j <= 1; j++)
								if ((MX == (6 + 8 * n + i)) && (MY == (4 + 4 * m + j))) {
									element(a[m][n], n, m, element_fg_hwh, type, apartline);
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
			element(a[y][x], x, y, element_fg_bl, type, apartline);
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
			element(a[y][x], x, y, element_fg_hwh, type, apartline);
			cct_gotoxy(0, hang * hang_coe + 4);
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			cout << "[当前键盘]" << char(y + 'A') << "行" << x << "列";
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

void print_pro(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int x, int y, int hang, int lie, int value, int& score, int target, int leave, int type, int apartline)
{
	while (1) {
		int score_once = 0, quantity = 0, move = 0, click = 0, arrow = 0;
		for (int i = 0; i < hangmax + 2; i++)
			for (int j = 0; j < liemax + 2; j++)
				if (a_copy[j][i]==array_zero)
					element(value, i - 1, j - 1, element_fg_wh, type, apartline);
		quantity++;
		element(value, x, y, element_fg_hwh, type, apartline);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		/*if (choice == 9) {
			score_once = value * quantity * scoretime;
			score += score_once;
			cct_gotoxy(0, 0);
			cout << "本次得分：" << score_once << " 总得分：" << score << " 合成目标：" << target << endl;
		}*/
		/*if (choice >= 8) {
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
							element(value, j - 1, i - 1, element_fg_bl, type);
			}
		}*/
		copy(a, a_copy, copy_to_array);
		cct_gotoxy(0, hang * 4 + 3);
		enter(enter_pure);
		for (int i = 0; i < hangmax + 2; i++)
			for (int j = 0; j < liemax + 2; j++)
				if (!a_copy[i][j])
					element(value, j - 1, i - 1, element_all_hwh, type, apartline);
		a[y][x]++;
		if (value < a[y][x])
			value = a[y][x];
		for (int n = 0; n < 20; n++) {
			element(value, x, y, element_fg_bl, type, apartline);
			Sleep(20);
			element(value, x, y, element_fg_hwh, type, apartline);
		}
		/*if (choice == 8) {
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
		}*/
		enter(enter_pure);
		for (int j = 0; j < lie; j++)
			for (int i = hang - 1; i > 0; i--)
				if (a[i][j]==array_zero)
					for (int k = i - 1; k >= 0; k--)
						if (a[k][j]) {
							element(a[k][j], j, k, element_all_hwh, type, apartline);
							Sleep(15);
							element(a[k][j], j, k + 1, element_fg_bl, type, apartline);
							Sleep(15);
							a[k + 1][j] = a[k][j];
							a[k][j] = 0;
							j -= 2;
							break;
						}
		/*if (choice == 8) {
			cct_gotoxy(0, hang * 4 + 3);
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			cout << "下落0完成，回车/单击左键赋新值";
		}*/
		copy(a, a_copy, array_to_copy);
		random(a, value, hang, lie, type);
		for (int i = 0; i < hang; i++)
			for (int j = 0; j < lie; j++)
				if (!a_copy[j + 1][i + 1]) {
					element(a[j][i], i, j, element_fg_bl, type, apartline);
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

void func_find(int type)
{
	int hang = 0, lie = 0, same = 0;
	int array[hangmax][liemax], array_copy[hangmax + 2][liemax + 2];
	char xy[3];
	reset(array, array_copy);
	shuru_hl(hang, lie);
	random(array, 0, hang, lie, type);
	copy(array, array_copy, array_to_copy);
	print_num(array, array_copy, print_array);
	int x = 0, y = 0;
	while (1) {
		shuru_xy(hang, lie, xy);
		if (!same) {
			cct_getxy(x, y);
			cct_gotoxy(0, y - 1);
			cout << "                                            " << endl;
			cct_gotoxy(x, y);
		}
		if (!array[xy[0]][xy[1]]) {
			cct_getxy(x, y);
			cct_gotoxy(0, y - 1);
			cout << "请选择非零位置！" << endl;
			cct_gotoxy(0, y - 2);
		}
		else {
			if (type == syn_ten_no_recursion) {
				same = search_no(array_copy, xy[0], xy[1]);
				if (same != 0)
					break;
			}
			else if (search(array_copy, xy[0] + 1, xy[1] + 1, array[xy[0]][xy[1]], same))
				break;
			cct_getxy(x, y);
			cct_gotoxy(0, y - 1);
			cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
			cct_gotoxy(0, y - 2);
		}
	}
	if (type == syn_ten) {
		print_num(array, array_copy, print_array_sign);
		getchar();
	}
	print_num(array, array_copy, print_array_color);
	if (!possibility(array_copy)) 
		cout << "无法找到可消除项，游戏结束！！！" << endl;
	tj_exit();
}

void func_eli(int type, int cycle) {
	int hang = 0, lie = 0, same = 0, target = 0, x = 0, y = 0, score = 0, max = 0;
	int array[hangmax][liemax], array_copy[hangmax + 2][liemax + 2];
	char xy[3];
	reset(array, array_copy);
		shuru_hl(hang, lie);
		/*if (type == syn_ten)
			aim(target);
		else if (type == star_eli)
			level(target,hang*lie);*/
		random(array, 0, hang, lie, type);
		copy(array, array_copy, array_to_copy);
		print_num(array, array_copy, print_array);
	while (1) {
		while (1) {
			shuru_xy(hang, lie, xy);
			if (!same) {
				cct_getxy(x, y);
				cct_gotoxy(0, y - 1);
				cout << "                                            " << endl;
				cct_gotoxy(x, y);
			}
			if (!array[xy[0]][xy[1]]) {
				cct_getxy(x, y);
				cct_gotoxy(0, y - 1);
				cout << "请选择非零位置！" << endl;
				cct_gotoxy(0, y - 2);
			}
			else {
				if (type == syn_ten_no_recursion) {
					same = search_no(array_copy, xy[0], xy[1]);
					if (same != 0)
						break;
				}
				else if (search(array_copy, xy[0] + 1, xy[1] + 1, array[xy[0]][xy[1]], same))
					break;
				cct_getxy(x, y);
				cct_gotoxy(0, y - 1);
				cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
				cct_gotoxy(0, y - 2);
			}
		}
		if (type == syn_ten)
			print_num(array, array_copy, print_array_sign);
		print_num(array, array_copy, print_array_color);
		int choice;
		choice = combi_or_eli(array, array_copy, xy[0], xy[1], score, star_eli);
		if (choice!= combi_eli_N) {
			if (choice == combi_eli_Q)
				break;
			max = array[xy[0]][xy[1]] + 1;
			cout << " 总得分：" << score << endl;
			cout << endl;
			enter(enter_fall);
			fall(array, array_copy);
			if (type == syn_ten) {
				enter(enter_fill);
				fill(array, array_copy, max, xy[0], xy[1]);
			}
			else if (type == star_eli) {
				enter(enter_shl);
				shl(array, array_copy);
			}
			if (!possibility(array_copy)) {
				cout << "无法找到可消除项，游戏结束！！！" << endl;
				break;
			}
			if (cycle== one_step)
				break;
		}
		else
			print_num(array, array_copy, print_array);
	}
	tj_exit();
}

