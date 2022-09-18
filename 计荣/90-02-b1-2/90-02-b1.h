#pragma once
/*2153680 –≈14 ’‘¡Ë›⁄*/
#pragma once
#define hangmin 5
#define hangmax 8
#define liemin 5
#define liemax 10
#define print_array 0
#define print_array_color 1
#define print_array_sign 2
#define star_eli 0
#define syn_ten 1
#define syn_ten_no_recursion 2
#define array_to_copy 1
#define copy_to_array 0
#define syn_score_times 3
#define star_score_times 5
#define enter_next 0
#define enter_fall 1
#define enter_shl 2
#define enter_fill 3
#define enter_pure 4
#define one_step 0
#define one_level 1
#define array_same -2
#define array_empty -1
#define array_zero 0
#define combi_eli_Y 0
#define combi_eli_N 1
#define combi_eli_Q -1
#define nal 0
#define al 1
#define choose_n 0
#define choose 1
#define element_fg_bl 1
#define element_fg_wh -1
#define element_fg_hwh 0
#define element_all_hwh -2

struct functions;

void func_find(int type);

void func_eli(int type, int cycle);

void func_cons_mtarget_one(int type, int apartline, int show_or_choose);

void shuru_hl(int& hang, int& lie);

int menu(const char* menu_content[], const char* menu_options);

void apartline(int length);

void print_num(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int mark);

void shuru_xy(int hang, int lie, char xy[3]);

void reset(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2]);

void random(int a[hangmax][liemax], int max, int hang, int lie, int type);

void copy(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int a_to_copy);

int search_no(int a_copy[hangmax + 2][liemax + 2], int x, int y);

int search(int a_copy[hangmax + 2][liemax + 2], int x, int y, int value, int& same_last);

int search_find_same(int a_copy[hangmax + 2][liemax + 2], int x, int y, int value);

void tj_exit();

void aim(int& target);

int combi_or_eli(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int x, int y, int& score, int type);

void level(int& target, int area);
	
bool possibility(int a_copy[hangmax + 2][liemax + 2]);

void fall(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2]);

void tianchong(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int max, int hang, int lie);

void print_fig(int a[hangmax][liemax], int hang, int lie, int apartline, int type);

void screen_set(int apartline, int hang, int lie);

void element(int value, int x, int y, int color, int type, int apartline);

void print_pro(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int x, int y, int hang, int lie, int value, int& score, int target, int leave, int type, int apartline);

void mk(int& move, int& click, int& arrow);

void move(int a[hangmax][liemax], int hang, int lie, int& x, int& y, int type, int apartline);