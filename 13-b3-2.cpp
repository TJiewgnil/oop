/* 2153680 赵凌葳 信14 */
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
		cout << "打开文件失败" << endl;
		return -1;
	}
	student* head = NULL, * p = NULL, * q = NULL;
	int i = 0;
	while (1) {
		if (i)
			q = p;
		p = new(nothrow)student;
		if (p == NULL) {
			cout << "内存申请失败" << endl;
			return -1;
		}
		if (!i)
			head = p;
		else
			q->next = p;
		if (!i)
			i++;
		//读取数据
		infile >>* p->no >> *p->name >> *p->score;
		if (*p->no == 9999999)
			break;
		p->next = NULL;
	}
	//关闭文件
	infile.close();
	//二次申请
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
			cout << "内存申请失败" << endl;
			return -1;
		}
		if (!i)
			head = p;
		else
			q->next = p;
		if (!i)
			i++;
		//读取数据
		infile >> *p->no >> *p->name >> *p->score;
		if (*p->no == 9999999)
			break;
		p->next = NULL;
	}

	//遍历链表进行打印
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