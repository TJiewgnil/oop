/* 2153680 ������ ��14 */
#include <iostream>
#include <fstream>
using namespace std;
#include <cstdlib>

struct student {
	int *no;
	char *name;
	int *score;
	struct student* next;
};

int main()
{
	ifstream infile;
	infile.open("list.txt", ios::in);
	if (!infile.is_open()) {
		cout << "���ļ�ʧ��" << endl;
		return -1;
	}
	student* head = NULL, * p = NULL, * q = NULL;
	int i = 0;
	while (1) {
		if (i)
			q = p;
		p = new(nothrow)student;
		if (p == NULL) {
			cout << "�ڴ�����ʧ��" << endl;
			return -1;
		}
		if (!i)
			head = p;
		else
			q->next = p;
		if (!i)
			i++;
		//��ȡ����
		infile >>* p->no >> *p->name >> *p->score;
		if (*p->no == 9999999)
			break;
		p->next = NULL;
	}
	//�ر��ļ�
	infile.close();
	//��������
	i = 0;
	int space = 0;
	while (1) {
		if (i)
			q = p;
		for (space = 0;; space++) 
			if (p->name[space] == '\0')
				break;
		p->name = new(nothrow)char[space * sizeof(char)];
		if (p == NULL) {
			cout << "�ڴ�����ʧ��" << endl;
			return -1;
		}
		if (!i)
			head = p;
		else
			q->next = p;
		if (!i)
			i++;
		//��ȡ����
		infile >> *p->no >> *p->name >> *p->score;
		if (*p->no == 9999999)
			break;
		p->next = NULL;
	}

	//����������д�ӡ
	q = head;
	while (1) {
		p = q;
		if (*p->no == 9999999)
			break;
		q = p->next;
		cout << *p->no << " " << *p->name << " " << *p->score << endl;
		delete p;
	}
	return 0;
}