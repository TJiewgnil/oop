/* ѧ�� �༶ ���� */
#include <iostream>
using namespace std;
#include "90-02-b1.h"
#include "../include/cmd_console_tools.h"
#include <conio.h>
#include <iomanip>

const char* menu_content[]{
		"A.�������ҳ���������",
		"B.���������һ���������ֲ�����ʾ��",
		"C.���������һ�أ��ֲ�����ʾ��",
		"D.αͼ��ҳ�������ѡ��һ��ɫ�飨�޷ָ��ߣ�",
		"E.αͼ��ҳ�������ѡ��һ��ɫ�飨�зָ��ߣ�",
		"F.αͼ��ҳ�������һ�κϳɣ��ֲ�����ʾ��",
		"G.αͼ��ҳ�棨�����棩",
		"Q.�˳�",
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
	void (*f1)(int& quit);//f1һ��ָ�������˳�����ĺ���
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
