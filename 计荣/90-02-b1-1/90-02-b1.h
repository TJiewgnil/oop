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

struct functions;

void shuru_hl(int& hang, int& lie);

int menu(const char* menu_content[], const char* menu_options);

void apartline(int length);

void print_num(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int mark);

void shuru_xy(int hang, int lie, char xy[3]);

void reset(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2]);

void random(int a[hangmax][liemax], int max, int hang, int lie, int type);

void copy(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int a_to_copy);

int search_no(int a_copy[hangmax + 2][liemax + 2], int x, int y);

int search(int a_copy[hangmax + 2][liemax + 2], int x, int y, int value);

int search_find_same(int a_copy[hangmax + 2][liemax + 2], int x, int y, int value);

void tj_exit();

void aim(int& target);

void combi_or_eli(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int x, int y, int& score, int type);

void level(int& target, int area);
	
void func_find(int type);

void func_eli(int type);

bool possibility(int a_copy[hangmax + 2][liemax + 2]);

void fall(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2]);

void tianchong(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int max, int hang, int lie);
