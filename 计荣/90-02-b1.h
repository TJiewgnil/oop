#pragma once
/*2153680 –≈14 ’‘¡Ë›⁄*/
#pragma once
#define hangmin 5
#define hangmax 8
#define liemin 5
#define liemax 10
#define print_array -2
#define print_array_color -3
#define print_array_sign -4
#define star_eli 0
#define syn_ten 1
#define syn_ten_no_recursion 2
#define array_to_copy 1
#define copy_to_array 0

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

void func_find(int type);

void tj_exit();
