/* 2153680 赵凌葳 信14 */
#include <iostream>
#include <fstream>
using namespace std;
#include <cstdlib>
#include <string.h>

struct student {
	int no;
	char name[9];
	int score;
	int rank;
};

void tj_strcpy(char a[9], char b[9])
{
	for (int i = 0;; i++) {
		if (a[i] == '\0') {
			int j = 0;
			while (1) {
				a[i + j] = b[i + j];
				if (b[i + j] == '\0') {
					b[i] = '\0';
					break;
				}
				j++;
			}
			break;
		}
		else if (b[i] == '\0') {
			int j = 0;
			while (1) {
				b[i + j] = a[i + j];
				if (a[i + j] == '\0') {
					a[i] = '\0';
					break;
				}
				j++;
			}
			break;
		}
		else {
			char k = a[i];
			a[i] = b[i];
			b[i] = k;
		}
	}

}

void reverse(struct student* p, int i)
{
	int no = 0, score = 0, rank = 0;
	char name[9] = { 0 };
	//中转=前
	no = (p + i)->no;
	tj_strcpy(name, (p + i)->name);
	score = (p + i)->score;
	rank = (p + i)->rank;
	//前=后
	(p + i)->no = (p + i + 1)->no;
	tj_strcpy((p + i)->name, (p + i + 1)->name);
	(p + i)->score = (p + i + 1)->score;
	(p + i)->rank = (p + i + 1)->rank;
	//后=中转
	(p + i + 1)->no = no;
	tj_strcpy((p + i + 1)->name, name);
	(p + i + 1)->score = score;
	(p + i + 1)->rank = rank;
}

int main()
{
	//打开文件
	ifstream infile;
	infile.open("student.txt", ios::in);
	if (!infile.is_open()) {
		cout << "打开文件失败" << endl;
		return -1;
	}

	//读取总人数
	int num = 0, i = 0, j = 0;
	infile >> num;

	//申请连续空间
	student* p = new(nothrow)student[num];
	if (p == NULL) {
		printf("内存申请失败\n");
		return -1;
	}

	//读入数据
	for (i = 0; i < num; i++) {
		infile >> (p + i)->no >> (p + i)->name >> (p + i)->score;
		(p + i)->rank = 0;
	}
	//关闭文件
	infile.close();

	//成绩排序
	for (j = 0; j < num; j++)
		for (i = 0; i < num - j - 1; i++)
			if ((p + i)->score < (p + i + 1)->score)
				reverse(p, i);

	//赋入名次
	int same = 0, samerank = 1;
	p->rank = 1;
	for (i = 1; i < num; i++) {
		if ((p + i)->score == (p + i + 1)->score)
			same++;
		else {
			for (j = 0; j <= same; j++)
				(p + i - j)->rank = samerank + 1;
			samerank += same + 1;
			same = 0;
		}
	}

	//学号排序
	for (j = 0; j < num; j++)
		for (i = 0; i < num - j - 1; i++)
			if (((p + i)->rank == (p + i + 1)->rank) && ((p + i)->no > (p + i + 1)->no))
				reverse(p, i);

	//输出
	for (i = 0; i < num; i++)
		cout << (p + i)->no << " " << (p + i)->name << " " << (p + i)->score << " " << (p + i)->rank << endl;

	//释放内存
	delete[]p;
}