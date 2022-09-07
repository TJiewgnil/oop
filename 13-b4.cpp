/* 2153680 赵凌葳 信14 */
#include <iostream>
#include <fstream>
using namespace std;
#include <cstdlib>
//读入数据时申请连续空间，因为要查找指定数据，效率高
//储存录取信息时申请链式空间，可以不用申请新空间，直接将原连续空间中需要的数据链接起来，再把其它数据删掉即可。

struct student {
	int no;
	char name[12];
	char school[10];
	struct student* next;
};

int main()
{
	int apply = 0, admit = 0, i = 0, j = 0, chosen = 0;
	//打开输入文件
	ifstream infile;
	infile.open("stulist.txt", ios::in);
	if (!infile.is_open()) {
		cout << "打开输入文件失败" << endl;
		return -1;
	}
	infile >> admit >> apply;
	int* luck = new(nothrow)int[admit];
	//for (i = 0; i < admit; i++)
		//luck[i] = 0;
	srand((unsigned int)time(0));
	chosen = rand() % apply;
	luck[0] = chosen;
	i = 1;
	srand((unsigned int)time(0));
	while (i != admit) {
		chosen = rand() % apply;
		int same = 0;
		for (j = 0; j < i; j++)
			if (luck[i] == luck[j]) {
				same++;
				break;
			}
		if (!same) {
			luck[i] = chosen;
			i++;
		}
	}
	for (i = 0; i < admit; i++)
		for (j = 0; j < admit - i - 1; j++)
			if (luck[j] > luck[j + 1]) {
				int value = luck[j];
				luck[j] = luck[j + 1];
				luck[j + 1] = value;
			}
	//打开输出文件
	ofstream oufile;
	oufile.open("result.txt", ios::out);
	if (!oufile.is_open()) {
		cout << "打开输出文件失败" << endl;
		return -1;
	}
	student* head = NULL, * p = NULL, * q = NULL, * mid = NULL;
	int num = 0, applyn = 0, admitn = 0;
	i = 0;
	while (1) {
		applyn++;
		if (applyn == luck[admitn])
			if (i)
				q = p;
		mid = new(nothrow)student;
		if (mid == NULL) {
			cout << "内存申请失败" << endl;
			return -1;
		}
		if (applyn == luck[admitn]) {
			p = mid;
			if (!i)
				head = p;
			else
				q->next = p;
			if (!i)
				i++;
		}
		if (applyn == luck[admitn]) {
			//读取数据
			infile >> p->no >> p->name >> p->school;
			cout << admitn << " " << applyn << endl;
			p->next = NULL;
			admitn++;
			if (admitn == admit)
				break;
		}
		else {
			//读取数据
			infile >> mid->no >> mid->name >> mid->school;
			delete mid;
		}
	}
	//关闭输入文件
	infile.close();
	//遍历链表进行打印
	q = head;
	while (1) {
		p = q;
		q = p->next;
		oufile << p->no << " " << p->name << " " << p->school << endl;
		if (p->next == NULL) {
			delete p;
			break;
		}
		delete p;
	}
	//关闭输出文件
	oufile.close();
}