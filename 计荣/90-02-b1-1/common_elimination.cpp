#include <iostream>
#include "../include/cmd_console_tools.h"
#include "../90-02-b1/90-02-b1.h"
#include <conio.h>
#include <iomanip>
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
		cout << "����������(" << hangmin << "-" << hangmax << ")��" << endl;
		cin >> hang;
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

void print_num(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int mark)
{
	if (mark == print_array) {
		cout << endl;
		cout << "��ǰ���飺" << endl;
	}
	else if (mark == print_array_sign)
		cout << "���ҽ�����飺" << endl;
	else if (mark == print_array_color)
		cout << "��ǰ����(��ͬɫ��ʶ)��" << endl;
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
			if (mark!= print_array_sign) {
				cout << " ";
				if (!a_copy[i + 1][j + 1] && mark != print_array)
					cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
				cout << a[i][j];
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << " ";
			}
			else if (mark== print_array_sign)
				if (!a_copy[i + 1][j + 1])
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
	cout << "��ѡ��" << endl;
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
	cout << "������ĸ+������ʽ[����c2]����������꣺";
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
			cout << "�����������������.";
			cct_gotoxy(coordx, coordy);
			error = 1;
		}
	}
	cct_gotoxy(coordx, coordy);
	cout << "����Ϊ" << char(xy[0] + 'A') << "��" << char(xy[1] + '0') << "��" << endl;
	cout << endl;
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

void random(int a[hangmax][liemax], int max, int hang, int lie,int type)
{
	int rate = 0;
	srand((unsigned)time(0));
	for (int i = 0; i < hang; i++)
		for (int j = 0; j < lie; j++) {
			if (type == star_eli)
				a[i][j] = rand() % 5 + 1;
			else if (type == syn_ten) {
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
}

void copy(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int a_to_copy)
{
	for (int i = 0; i < hangmax; i++)
		for (int j = 0; j < liemax; j++)
			if (a[i][j] != -1 && a_to_copy)
				a_copy[i + 1][j + 1] = a[i][j];
			else
				a[i][j] = a_copy[i + 1][j + 1];
}

int search_no(int a_copy[hangmax + 2][liemax + 2], int x, int y)
{
	int value = a_copy[x + 1][y + 1];
	a_copy[x + 1][y + 1] = 0;
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
	if(!latter)
		a_copy[x + 1][y + 1] = value;
	return latter;
}

int search(int a_copy[hangmax + 2][liemax + 2], int x, int y, int value)
{
	int same = 0;
	same = search_find_same(a_copy, x, y, value);
	if (!same)
		a_copy[x][y] = value;
	return same;
}

int search_find_same(int a_copy[hangmax + 2][liemax + 2], int x, int y, int value)
{
	static int  same = 0;
	a_copy[x][y] = 0;
	if (x > 0 && x < (hangmax + 2) && y>0 && y < (liemax + 2)) {
		if (a_copy[x - 1][y] == value) {
			same++;
			a_copy[x - 1][y] = 0;
			search_find_same(a_copy, x - 1, y, value);
		}
		if (a_copy[x + 1][y] == value) {
			same++;
			a_copy[x + 1][y] = 0;
			search_find_same(a_copy, x + 1, y, value);
		}
		if (a_copy[x][y - 1] == value) {
			same++;
			a_copy[x][y - 1] = 0;
			search_find_same(a_copy, x, y - 1, value);
		}
		if (a_copy[x][y + 1] == value) {
			same++;
			a_copy[x][y + 1] = 0;
			search_find_same(a_copy, x, y + 1, value);
		}
	}
	return same;
}

void tj_exit()
{
	cout << "��С�������������End����...";
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
			cout << "�����������������.";
			cct_gotoxy(coordx, coordy);
		}
	}
}

void combi_or_eli(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int x, int y, int& score,int type)
{
	int value = a[x][y], yes = 0, coordx = 0, coordy = 0, jump = 0, quantity = 0, hang = hangmax, lie = liemax, score_once = 0;
	while (1) {
		cout << "��ȷ���Ƿ�����ڵ���ֵͬ�ϲ���" << char(x + 'A') << char(y + '0') << "��(Y/N/Q)��";
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
		for (int i = hangmax - 1; i >= 0; i--)//�ϲ�
			for (int j = 0; j < liemax; j++)
				if (!a_copy[i + 1][j + 1]) {
					a[i][j] = 0;
					quantity++;
				}
				else if ((a_copy[i + 1][j + 1] == -1) && hang == hangmax && lie == liemax) {
					hang = i - 1;
					lie = j - 1;
				}
		if (type == syn_ten) {
			score_once = value * quantity * syn_score_times;
			score += score_once;
			a[x][y] = ++value;
		}
		else if(type==star_eli) {
			score_once = quantity * quantity * star_score_times;
			score += score_once;
		}
		cout << endl;
		cout << "��ֵͬ�鲢�������(��ͬɫ��ʶ)��" << endl;
		print_num(a, a_copy, print_array_color);
		cout << "���ε÷֣�" << score_once;
		break;
	}
}//max=value

bool possibility(int a_copy[hangmax + 2][liemax + 2])
{
	int value = 0;
	bool possibility = 0;
	for (int i = 1; i < hangmax + 1; i++) {
		for (int j = 1; j < liemax + 1; j++) {
			value = a_copy[i][j];
			if (a_copy[i - 1][j] == value|| a_copy[i + 1][j] == value|| a_copy[i][j - 1] == value || a_copy[i][j + 1] == value) {
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
	char ch = 0;
	if (content == enter_next)
		cout << "���κϳɽ��������س���������һ�εĺϳ�..." << endl;
	else {
		cout << "���س�������";
		if (content == enter_fall)
			cout << "���������0����..." << endl;
		else if (content == enter_shl)
			cout << "�Ҳ�ȫ0��ƽ�Ʋ���..." << endl;
		else if (content == enter_fill)
			cout << "��ֵ������..." << endl;
	}

	while (1) {
		cct_getxy(coordx, coordy);
		ch = _getch();
		if (ch == '\r')
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
						a[k][j] = 0;
						break;
					}
	copy(a, a_copy, array_to_copy);
	cout << "�����0��" ;
	print_num(a, a_copy, print_array_color);
	cout << endl;
}

void fill(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int max, int hang, int lie)
{
	random(a, max, hang, lie, syn_ten);
	cout << "0λ�ò�����ֵ��";
	print_num(a, a_copy, print_array_color);
	copy(a, a_copy, array_to_copy);
	cout << endl;
}

void shl(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2])
{
	int lie, hang;
	for(lie=liemax-1;lie>=0;lie--)
		if (a[0][lie] != -1) {
			for (hang = 0; hang < hangmax; hang++)
				if (a[hang][lie])
					break;
			if (a[hang][lie] == -1 || hang == hangmax - 1)//�ͽ��Ҳ���ȫ������1��
				for (int lie_shl = lie; lie_shl < liemax - 1; lie_shl++)
					if (a[0][lie + 1] != -1)
						for (int hang_shl = 0; hang_shl < hangmax; hang_shl++) {
							if (a[hang_shl][lie_shl] == -1)
								break;
							a[hang_shl][lie_shl] = a[hang_shl][lie_shl + 1];
						}
		}
	cout << "�Ҳ�ȫ0��ƽ�ƺ�";
	print_num(a, a_copy, print_array_color);
	copy(a, a_copy, array_to_copy);
	cout << endl;
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
			cct_gotoxy(0, y-1);
			cout << "                                            " << endl;
			cct_gotoxy(x, y);
		}
		if (type == syn_ten_no_recursion)
			same = search_no(array_copy, xy[0], xy[1]);
		else
			same = search(array_copy, xy[0]+1, xy[1]+1, array[xy[0]][xy[1]]);
		if (same != 0)
			break;
		else {
			cct_getxy(x, y);
			cct_gotoxy(0, y - 1);
			cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
			cct_gotoxy(0, y - 2);
		}
	}
	if (type == syn_ten)
		print_num(array, array_copy, print_array_sign);
	print_num(array, array_copy, print_array_color);
	tj_exit();
}

void func_eli(int type) {
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
		shuru_xy(hang, lie, xy);
		if (!same) {
			cct_getxy(x, y);
			cct_gotoxy(0, y - 1);
			cout << "                                            " << endl;
			cct_gotoxy(x, y);
		}
		if (type == syn_ten_no_recursion)
			same = search_no(array_copy, xy[0], xy[1]);
		else
			same = search(array_copy, xy[0] + 1, xy[1] + 1, array[xy[0]][xy[1]]);
		if (same != 0)
			break;
		else {
			cct_getxy(x, y);
			cct_gotoxy(0, y - 1);
			cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
			cct_gotoxy(0, y - 2);
		}
	}
	if (type == syn_ten)
		print_num(array, array_copy, print_array_sign);
	print_num(array, array_copy, print_array_color);
	combi_or_eli(array,array_copy, xy[0], xy[1], score, star_eli);
	max = array[xy[0]][xy[1]] + 1;
	cout << " �ܵ÷֣�" << score << endl;
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
	if (!possibility(array_copy))
		cout << "�޷��ҵ����������Ϸ����������" << endl;
	tj_exit();
}

