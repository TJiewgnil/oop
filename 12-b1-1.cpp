/* 2153680 赵凌葳 信14 */
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM	4
#define SCORE_NUM	5

/* --- 不允许定义任何形式的全局变量 --- */

/***************************************************************************
  函数名称：average
  功    能：求第一门课的平均分
  输入参数：(*score)[SCORE_NUM]
  返 回 值：void
  说    明：相关输出都放在函数中即可
***************************************************************************/
void average(int(*score)[SCORE_NUM])
{
    /* 函数定义语句部分：
       1、本函数中仅允许定义 1个简单变量 + 1个指针变量 */

       /* 函数执行语句部分：
          1、不允许再定义任何类型的变量，包括 for (int i=0;...）等形式定义变量
          2、循环变量必须是指针变量，后续语句中不允许出现[]形式访问数组
             不允许：int a[10], i;
                     for(i=0; i<10; i++)
                         cout << a[i];
             允许  ：int a[10], p;
                     for(p=a; p<a+10; p++)
                         cout << *p;          */
    int(*p)[SCORE_NUM], sum = 0;
    for (p = score; p < score + STUDENT_NUM; p++)
        sum += **p;
    cout << "第1门课平均分："<< (double)sum / STUDENT_NUM << endl;

}

/***************************************************************************
  函数名称：fail
  功    能：找出有两门以上课程不及格的学生
  输入参数：(*score)[SCORE_NUM]
  返 回 值：void
  说    明：相关输出都放在函数中即可
***************************************************************************/
void fail(int(*score)[SCORE_NUM])
{
    /* 函数定义语句部分：
       1、本函数中仅允许定义 2个简单变量 + 1个行指针变量 + 1个简单指针变量 */

       /* 函数执行语句部分（要求同average）*/
    int(*line)[SCORE_NUM], *column,fail, sum;
    cout << "2门以上不及格的学生：" << endl;
    for (line = score; line < score + STUDENT_NUM; line++) {
        fail = 0, sum = 0;
        for (column = *line; column < *line + SCORE_NUM; column++) 
            if (*column < 60)
                fail++;
        if (fail >= 2) {
            cout << "No：" << line - score + 1;
            for (column = *line; column < *line + SCORE_NUM; column++) {
                cout << setw(3)<< * column;
                sum += *column;
            }
            cout << " " << "平均：" << (double)sum / SCORE_NUM << endl;
        }
    }
}

/***************************************************************************
  函数名称：good
  功    能：找出平均成绩在90分以上或全部成绩在85分以上的学生
  输入参数：(*score)[SCORE_NUM]
  返 回 值：void
  说    明：
***************************************************************************/
void good(int(*score)[SCORE_NUM])
{
    /* 函数定义语句部分：
       1、本函数中仅允许定义 2个简单变量 + 1个行指针变量 + 1个简单指针变量 */

       /* 函数执行语句部分（要求同average）*/
    int(*line)[SCORE_NUM], * column, succ, sum;
    cout << "平均90以上或全部85以上的学生：" << endl;
    for (line = score; line < score + STUDENT_NUM; line++) {
        succ = 0, sum = 0;
        for (column = *line; column < *line + SCORE_NUM; column++) {
            if (*column >= 85)
                succ++;
            sum += *column;
        }
        if (succ == 5 || sum >= 90 * SCORE_NUM) {
            cout << "No：" << line - score + 1;
            for (column = *line; column < *line + SCORE_NUM; column++) {
                cout << setw(3) << *column;
            }
            cout << " " << "平均：" << (double)sum / SCORE_NUM << endl;
        }
    }

}

/***************************************************************************
  函数名称：main
  功    能：定义数组、指针，调用各函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
    int a[STUDENT_NUM][SCORE_NUM] = {
        {91, 81, 71, 61, 51},	//第1个学生的1-5门课的成绩
        {92, 82, 72, 32, 52},   //第2个学生的1-5门课的成绩
        {93, 83, 99, 80, 95},   //第3个学生的1-5门课的成绩
        {97, 85, 87, 91, 88} }; //第4个学生的1-5门课的成绩

    /* 除上面的预置数组外，本函数中仅允许定义 1个行指针变量 + 1个简单指针变量 */
    int(*stu)[SCORE_NUM] = a, * subj = *stu;
    cout << "初始信息：" << endl;
    for (; stu < a + STUDENT_NUM; stu++) {
        cout << "No." << stu - a + 1 << "的1-5门课成绩：";
        for (; subj < *stu + SCORE_NUM; subj++) {
            if (subj == *stu)
                cout << *subj;
            else
                cout << setw(3) << *subj;
        }
        cout << endl;
    }
    cout << endl;

    stu = a;
    average(stu);
    cout << endl;

    stu = a;
    fail(stu);
    cout << endl;

    stu = a;
    good(stu);

    /* 函数执行语句部分（要求同average）*/
    return 0;
}
