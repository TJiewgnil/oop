/* 学号 班级 姓名 */
#include <iostream>
using namespace std;
#include "90-02-b1.h"
#include "../include/cmd_console_tools.h"
#include <conio.h>
#include <iomanip>

const char* menu_content[]{
		"A.命令行找出可消除项",
		"B.命令行完成一次消除（分步骤显示）",
		"C.命令行完成一关（分步骤显示）",
		"D.伪图形页面下鼠标选择一个色块（无分割线）",
		"E.伪图形页面下鼠标选择一个色块（有分割线）",
		"F.伪图形页面下完成一次合成（分步骤显示）",
		"G.伪图形页面（完整版）",
		"Q.退出",
		NULL
};

const char* menu_options = "ABCDEFGQ";

void func_cons_mtarget_one_al() {

}

void func_cons_synthesis() {

}

void func_cons_final() {

}

void func_quit(int& quit) {
	quit = 1;
}

struct functions {
	char option;
	void (*f1)(int& quit);//f1一定指向用于退出程序的函数
	void (*f2)(int type);//find_recursion
	void (*f3)(int type);//find_no_recursion
	void (*f4)(int type, int one_step_or_level);//combi_or_eli_one_step
	void (*f5)(int type, int one_step_or_level);//combi_or_eli_one_level
	void (*f6)(int type, int apartline, int show_or_choose);//伪图形解//star_nal_ch//syn_nal_nch
	void (*f7)(int type, int apartline, int show_or_choose);//伪图形解//star_al_ch //syn_al_nch
	void (*f8)(int type, int apartline, int show_or_choose);//伪图形解//          //syn_al_ch
	void (*f9)();
	void (*f10)();
};

functions func[]{
/*f1*/	{'Q',func_quit,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
/*f2*/	{'A',NULL,func_find,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},//no_recursion
/*f3*/  /*{'2',NULL,NULL,func_find(recursion),NULL,NULL,NULL,NULL,NULL,NULL,NULL},*/
/*f4*/	{'B',NULL,NULL,NULL,func_eli,NULL,NULL,NULL,NULL,NULL,NULL},//one_step
/*f5*/	{'C',NULL,NULL,NULL,NULL,func_eli,NULL,NULL,NULL,NULL,NULL},//one_level
/*f6*/	{'D',NULL,NULL,NULL,NULL,NULL,func_cons_mtarget_one,NULL,NULL,NULL,NULL},   //伪图形解//star_nal_ch//syn_nal_nch
/*f7*/	{'E',NULL,NULL,NULL,NULL,NULL,NULL,func_cons_mtarget_one,NULL,NULL,NULL},   //伪图形解//star_al_ch //syn_al_nch
/*f8*/  /*{'7',NULL,NULL,NULL,NULL,NULL,NULL,NULL,func_cons_mtarget_one,NULL,NULL},*/ //伪图形解//           //syn_al_ch
/*f9*/	{'F',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,func_cons_synthesis,NULL},
/*f10*/	{'G',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,func_cons_final},
/*f0*/	{'\0',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};

int main()
{
	int option = 0, quit = 0;
	while (1) {
		quit = 0;
		cct_cls();
		int type = star_eli;
		option = menu(menu_content, menu_options);
		for (int i = 0; func[i].option; i++)
			if (func[i].option == option) {
				if (func[i].f1 != NULL)
					func[i].f1(quit);
				else if (func[i].f2 != NULL)
					func[i].f2(type); // syn_ten_no_recursion//star_eli
				else if (func[i].f3 != NULL)
					func[i].f3(type); // syn_ten
				else if (func[i].f4 != NULL)
					func[i].f4(type, one_step);//syn_ten//star_eli
				else if (func[i].f5 != NULL)
					func[i].f5(type, one_level);//syn_ten//star_eli
				else if (func[i].f6 != NULL) {
					if (type == syn_ten)
						func[i].f6(type, nal, choose_n);  //伪图形解//star_nal_ch//syn_nal_nch
					else if (type == star_eli)
						func[i].f6(type, nal, choose);
				}
				else if (func[i].f7 != NULL) {
					if (type == syn_ten)
						func[i].f7(type, al, choose_n);     //伪图形解//star_al_ch //syn_al_nch
					else if (type == star_eli)
						func[i].f7(type, al, choose);
				}
				else if (func[i].f8 != NULL)
					func[i].f8(type, al, choose);     //伪图形解//           //syn_al_ch
				else if (func[i].f9 != NULL)
					func[i].f9();
				else if (func[i].f10 != NULL)
					func[i].f10();
				break;
			}
		if (quit)
			break;
	}
	return 0;
}

void func_cons_mtarget_one(int type, int apartline, int show_or_choose)
{
	int hang = 0, lie = 0, same = 0, target = 0, x = 0, y = 0, score = 0, max = 0;
	int array[hangmax][liemax], array_copy[hangmax + 2][liemax + 2];
	reset(array, array_copy);
	shuru_hl(hang, lie);
	/*if (type == syn_ten)
		aim(target);
	else if (type == star_eli)
		level(target,hang*lie);*/
	random(array, 0, hang, lie, type);
	copy(array, array_copy, array_to_copy);
	screen_set(apartline, hang, lie);
	print_fig(array, hang, lie, apartline, type);
	if (show_or_choose == choose_n) {
		tj_exit();
		cct_cls();
	}
	else if (show_or_choose == choose) {
		element(array[y][x], x, y, element_fg_bl, type, apartline);
		while (1) {
			move(array, hang, lie, x, y, type, apartline);
			copy(array, array_copy, array_to_copy);
			int ret = search_no(array_copy, y, x);
			if (!ret) {
				element(array[y][x], x, y, element_fg_bl, type, apartline);
				cct_gotoxy(0, hang * 4 + 5);
				cout << "周围无相同值，";
			}
			else if (show_or_choose == choose_n) {
				int leave = 0;
				print_pro(array, array_copy, x, y, hang, lie, array[y][x], score, target, leave, type, apartline);
				if (!leave) {
					for (int i = 0; i < hang; i++)
						for (int j = 0; j < lie; j++)
							if (!array[j][i])
								element(array[y][x], i, j, element_fg_bl, type, apartline);
					continue;
				}
			}
			if (show_or_choose == choose)
				break;
		}
	}
}

