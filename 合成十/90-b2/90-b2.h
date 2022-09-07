/*2153680 ÐÅ14 ÕÔÁèÝÚ*/
//ÉùÃ÷
#pragma once

#define hangmin 5
#define hangmax 8
#define liemin 5
#define liemax 10
#define targetmin 5
#define targetmax 20
#define scoretime 3

int menu();

void reset(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2]);

void shuru_hl(int& hang, int& lie);

void shuru_xy(int hang, int lie, char xy[3]);

void random(int a[hangmax][liemax], int max, int hang, int lie);

void print_num(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int mark);

void fuzhi(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int a_for_copy);

int search_no(int a_copy[hangmax + 2][liemax + 2], int x, int y);

int search(int a_copy[hangmax + 2][liemax + 2], int x, int y, int value);

void tj_exit();

void aim(int& target);

void hebing(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int x, int y, int& score, int target, int& max);

void xialuo(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2]);

void tianchong(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int max, int hang, int lie);

void huiche(int type);

void print_fig(int a[hangmax][liemax], int hang, int lie, int choice);

void move(int a[hangmax][liemax], int hang, int lie, int choice, int& x, int& y);

void print_pro(int a[hangmax][liemax], int a_copy[hangmax + 2][liemax + 2], int x, int y, int hang, int lie, int value, int& score, int target,int choice,int leave);

void element(int value, int x, int y, int black);

void mk(int& move, int& click, int& arrow);
