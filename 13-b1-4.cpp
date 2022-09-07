/* 2153680 ������ ��14 */
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
	//��ת=ǰ
	no = (p + i)->no;
	tj_strcpy(name, (p + i)->name);
	score = (p + i)->score;
	rank = (p + i)->rank;
	//ǰ=��
	(p + i)->no = (p + i + 1)->no;
	tj_strcpy((p + i)->name, (p + i + 1)->name);
	(p + i)->score = (p + i + 1)->score;
	(p + i)->rank = (p + i + 1)->rank;
	//��=��ת
	(p + i + 1)->no = no;
	tj_strcpy((p + i + 1)->name, name);
	(p + i + 1)->score = score;
	(p + i + 1)->rank = rank;
}

int main()
{
	//���ļ�
	ifstream infile;
	infile.open("student.txt", ios::in);
	if (!infile.is_open()) {
		cout << "���ļ�ʧ��" << endl;
		return -1;
	}

	//��ȡ������
	int num = 0, i = 0, j = 0;
	infile >> num;

	//���������ռ�
	student* p = new(nothrow)student[num];
	if (p == NULL) {
		printf("�ڴ�����ʧ��\n");
		return -1;
	}

	//��������
	for (i = 0; i < num; i++) {
		infile >> (p + i)->no >> (p + i)->name >> (p + i)->score;
		(p + i)->rank = 0;
	}
	//�ر��ļ�
	infile.close();

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
			if (((p + i)->rank == (p + i + 1)->rank) && ((p + i)->no > (p + i + 1)->no))
				reverse(p, i);

	//���
	for (i = 0; i < num; i++)
		cout << (p + i)->no << " " << (p + i)->name << " " << (p + i)->score << " " << (p + i)->rank << endl;

	//�ͷ��ڴ�
	delete[]p;
}