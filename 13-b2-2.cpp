/* 2153680 ������ ��14 */
#include <iostream>
#include <fstream>
using namespace std;
#include <cstdlib>

struct student {
	int no;
	char name[9];
	int score;
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
	int i = 0, num = 0;
	while (1) {
		if (i)
			q = p;
		p = new(nothrow)student;
		if (p == NULL) {
			cout << "�ڴ�����ʧ��" << endl;
			return -1;
		}
		infile >> num;
		if (num != 9999999) {
			if (!i)
				head = p;
			else
				q->next = p;
			if (!i)
				i++;
			//��ȡ����
			infile >> p->name >> p->score;
			p->no = num;
			p->next = NULL;
		}
		else {
			q->next = NULL;
			delete p;
			break;
		}
	}
	//�ر��ļ�
	infile.close();
	//����������д�ӡ
	q = head;
	while (1) {
		p = q;
		q = p->next;
		cout << p->no << " " << p->name << " " << p->score << endl;
		if (p->next == NULL) {
			delete p;
			break;
		}
		delete p;
	}
}