/* 2153680 赵凌葳 信14 */
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
		cout << "打开文件失败" << endl;
		return -1;
	}
	student* head = NULL, * p = NULL, * q = NULL;
	int i = 0, num = 0;
	while (1) {
		if (i)
			q = p;
		p = new(nothrow)student;
		if (p == NULL) {
			cout << "内存申请失败" << endl;
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
			//读取数据
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
	//关闭文件
	infile.close();
	//遍历链表进行打印
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