/* 2153680 ������ ��14 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct student {
	int no;
	char name[9];
	int score;
	struct student* next;
};

int main()
{
	FILE* infile;
	infile = fopen("list.txt", "r");
	if (infile == NULL) {
		printf("���ļ�ʧ��\n");
		return -1;
	}
	struct student* head = NULL, * p = NULL, * q = NULL;
	int i = 0, num = 0;
	while (1) {
		if (i)
			q = p;
		p = (struct student*)malloc(sizeof(struct student));
		if (p == NULL) {
			printf("�ڴ�����ʧ��\n");
			return -1;
		}
		fscanf(infile, "%d", &num);
		if (num != 9999999) {
			if (!i)
				head = p;
			else
				q->next = p;
			if (!i)
				i++;
			//��ȡ����
			fscanf(infile, "%s %d", p->name, &p->score);
			p->no = num;
			p->next = NULL;
		}
		else {
			q->next = NULL;
			free(p);
			break;
		}
	}
	//�ر��ļ�
	fclose(infile);

	//����������д�ӡ
	q = head;
	while (1) {
		p = q;
		q = p->next;
		printf("%d %s %d\n", p->no, p->name, p->score);
		if (p->next == NULL) {
			free(p);
			break;
		}
		free (p);
	}

}