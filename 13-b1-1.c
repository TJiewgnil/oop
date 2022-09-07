/* 2153680 ������ ��14 */
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
	//��ת=ǰ
	no = (p + i)->no;
	strcpy(name, (p + i)->name);
	score = (p + i)->score;
	rank = (p + i)->rank;
	//ǰ=��
	(p + i)->no = (p + i + 1)->no;
	strcpy((p + i)->name , (p + i + 1)->name);
	(p + i)->score = (p + i + 1)->score;
	(p + i)->rank = (p + i + 1)->rank;
	//��=��ת
	(p + i + 1)->no = no;
	strcpy((p + i + 1)->name, name);
	(p + i + 1)->score = score;
	(p + i + 1)->rank = rank;
}

int main() 
{
	//���ļ�
	FILE* infile;
	infile = fopen("student.txt", "r");
	if (infile == NULL) {
		printf("���ļ�ʧ��/n");
		return -1;
	}
	int num, i, j;

	//��ȡ������
	fscanf(infile, "%d", &num);

	//���������ռ�
	struct student* p = (struct student*)malloc(num * sizeof(struct student));
	if (p == NULL) {
		printf("�ڴ�����ʧ��\n");
		return -1;
	}

	//��������
	for (i = 0; i < num; i++) {
		fscanf(infile, "%d %s %d", &(p + i)->no, (p + i)->name, &(p + i)->score);
		(p + i)->rank = 0;
	}
	//�ر��ļ�
	fclose(infile);

	//�ɼ�����
	for (j = 0; j < num; j++)
		for (i = 0; i < num - j - 1; i++)
			if ((p + i)->score < (p + i + 1)->score)
				reverse(p, i);

	//��������
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

	//ѧ������
	for (j = 0; j < num; j++)
		for (i = 0; i < num - j - 1; i++)
			if ((p + i)->no > (p + i + 1)->no)
				reverse(p, i);

	//���
	for (i = 0; i < num; i++)
		printf("%d %s %d %d\n", (p + i)->no, (p + i)->name, (p + i)->score, (p + i)->rank);
	
	//�ͷ��ڴ�
	free(p);
}