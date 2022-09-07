/*2153680 信14 赵凌葳*/
//主函数及菜单
#include <iostream>
using namespace std;
#include "90-b2.h"
#include "cmd_console_tools.h"

int main()
{
	int hang = 0, lie = 0, max = 0, array[hangmax][liemax], array_copy[hangmax + 2][liemax + 2], target = 0, score = 0, jump = 0, x = 0, y = 0;
	char xy[3];

	while (1) {
		reset(array, array_copy);
		int choice = menu(), same = 0;
		if (choice == 0)
			break;
		cct_cls();
		shuru_hl(hang, lie);
		if (choice >= 3&&choice!=4&&choice >=8)
			aim(target);
		random(array, max, hang, lie);
		if (choice >= 5) {
			cct_cls();
			int cols, lines, buffer_cols, buffer_lines;
			cct_getconsoleborder(cols, lines, buffer_cols, buffer_lines);
			if (choice == 5) {
				cct_setconsoleborder(lie * 6 + 7, hang * 3 + 10, buffer_cols * hang, buffer_lines * lie);
				cout << "屏幕当前设置为：" << hang * 3 + 10 << "行" << lie * 6 + 7 << "列" << endl;
			}
			else {
				cct_setconsoleborder(lie * 8 + 5, hang * 4 + 10, buffer_cols * hang, buffer_lines * lie);
				cout << "屏幕当前设置为：" << hang * 4 + 10 << "行" << lie * 8 + 5 << "列" << endl;
			}
			print_fig(array, hang, lie,choice);
			if (choice > 6) {
				element(array[y][x], x, y, 0);
				while (1) {
					move(array, hang, lie, choice, x, y);
					fuzhi(array, array_copy, 1);
					int ret = search_no(array_copy, y, x);
					if (!ret) {
						element(array[y][x], x, y, 1);
						cct_gotoxy(0, hang * 4 + 5);
						cout << "周围无相同值，";
					}
					else if (choice != 7) {
						int leave = 0;
						print_pro(array, array_copy, x, y, hang, lie, array[y][x], score, target, choice, leave);
						if (!leave) {
							for (int i = 0; i < hang; i++)
								for (int j = 0; j < lie; j++)
									if (!array[j][i])
										element(array[y][x], i, j, 1);
							continue;
						}
					}
					if (choice == 7)
						break;
				}
			}
			tj_exit();
			cct_cls();
			continue;
		}
		while (1) {
			print_num(array, array_copy, -1);
			while (1) {
				shuru_xy(hang, lie, xy);
				fuzhi(array, array_copy,1);
				if (choice == 1)
					same = search_no(array_copy, xy[0], xy[1]);
				else
					same = search(array_copy, xy[0]+1, xy[1]+1,array[xy[0]][xy[1]]);
				if (same != 0)
					break;
				else if (choice == 3) {
					jump = 1;
					cout << "输入的矩阵坐标位置处无连续相同值" << endl; 
					tj_exit();
					break;
				}
				else
					cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
			}
			if (jump==1)
				break;
			print_num(array, array_copy, 0);
			print_num(array, array_copy, 1);
			if (choice >= 3) {
				hebing(array, array_copy, xy[0], xy[1], score, target, max);
				huiche(0);
				xialuo(array, array_copy);//下落除零
				huiche(1);
				tianchong(array, array_copy, max, hang, lie);//重新赋值
			}
			if (choice < 4)
				tj_exit();
			else
				huiche(-1);
			if (choice != 4)
				break;
		}
		cct_cls();
	}

}