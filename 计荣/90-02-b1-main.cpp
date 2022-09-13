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

void func_eli(){

}

void func_level(){

}

void func_cons_mtarget_one_sp() {

}

void func_cons_mtarget_one_n() {

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
	void (*f2)(int type);
	void (*f3)();
	void (*f4)();
	void (*f5)();
	void (*f6)();
	void (*f7)();
	void (*f8)();
	void (*f9)();
	void (*f10)();
};

functions func[]{
	{'A',NULL,func_find,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{'B',NULL,NULL,func_eli,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{'C',NULL,NULL,NULL,func_level,NULL,NULL,NULL,NULL,NULL,NULL},
	{'D',NULL,NULL,NULL,NULL,func_cons_mtarget_one_sp,NULL,NULL,NULL,NULL,NULL},
	{'E',NULL,NULL,NULL,NULL,NULL,func_cons_mtarget_one_n,NULL,NULL,NULL,NULL},
	{'F',NULL,NULL,NULL,NULL,NULL,NULL,func_cons_synthesis,NULL,NULL,NULL},
	{'G',NULL,NULL,NULL,NULL,NULL,NULL,NULL,func_cons_final,NULL,NULL},
	{'Q',func_quit,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	{'\0',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};

int main()
{
	int option = 0, quit = 0;
	while (1) {
		quit = 0;
		cct_cls();
		option = menu(menu_content, menu_options);
		for (int i = 0; func[i].option; i++)
			if (func[i].option == option) {
				if (func[i].f1 != NULL)
					func[i].f1(quit);
				else if (func[i].f2 != NULL)
					func[i].f2(star_eli);
				else if (func[i].f3 != NULL)
					func[i].f3();
				else if (func[i].f4 != NULL)
					func[i].f4();
				else if (func[i].f5 != NULL)
					func[i].f5();
				else if (func[i].f6 != NULL)
					func[i].f6();
				else if (func[i].f7 != NULL)
					func[i].f7();
				else if (func[i].f8 != NULL)
					func[i].f8();
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
