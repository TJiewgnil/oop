/* 2153680 赵凌葳 信14 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
	int no;
	char name[9];
	int score;
	int rank;
};

void reverse(struct student* p, int i)
{
	int no = 0, score = 0, rank = 0;
	char name[9] = { 0 };
	//中转=前
	no = (p + i)->no;
	strcpy(name, (p + i)->name);
	score = (p + i)->score;
	rank = (p + i)->rank;
	//前=后
	(p + i)->no = (p + i + 1)->no;
	strcpy((p + i)->name , (p + i + 1)->name);
	(p + i)->score = (p + i + 1)->score;
	(p + i)->rank = (p + i + 1)->rank;
	//后=中转
	(p + i + 1)->no = no;
	strcpy((p + i + 1)->name, name);
	(p + i + 1)->score = score;
	(p + i + 1)->rank = rank;
}

int main() 
{
	//打开文件
	FILE* infile;
	infile = fopen("student.txt", "r");
	if (infile == NULL) {
		printf("打开文件失败/n");
		return -1;
	}
	int num, i, j;

	//读取总人数
	fscanf(infile, "%d", &num);

	//申请连续空间
	struct student* p = (struct student*)malloc(num * sizeof(struct student));
	if (p == NULL) {
		printf("内存申请失败\n");
		return -1;
	}

	//读入数据
	for (i = 0; i < num; i++) {
		fscanf(infile, "%d %s %d", &(p + i)->no, (p + i)->name, &(p + i)->score);
		(p + i)->rank = 0;
	}
	//关闭文件
	fclose(infile);

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
			if ((p + i)->no > (p + i + 1)->no)
				reverse(p, i);

	//输出
	for (i = 0; i < num; i++)
		printf("%d %s %d %d\n", (p + i)->no, (p + i)->name, (p + i)->score, (p + i)->rank);
	
	//释放内存
	free(p);
}