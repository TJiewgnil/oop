/* 2153680 赵凌葳 信安 */
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM	4
#define SCORE_NUM	5

/* --- 不允许定义任何形式的全局变量 --- */

/***************************************************************************
  函数名称：average
  功    能：求第一门课的平均分
  输入参数：int(*score)[STUDENT_NUM]
  返 回 值：void
  说    明：
***************************************************************************/
void average(int(*score)[STUDENT_NUM])//    int a[SCORE_NUM][STUDENT_NUM]
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
    int* p, sum = 0;
    for (p = *score; p < *score + STUDENT_NUM; p++)
        sum += *p;
    cout << "第1门课平均分：" << (double)sum / STUDENT_NUM << endl;

}

/***************************************************************************
  函数名称：fail
  功    能：找出有两门以上课程不及格的学生
  输入参数：int(*score)[STUDENT_NUM]
  返 回 值：void
  说    明：
***************************************************************************/
void fail(int(*score)[STUDENT_NUM])
{
    /* 函数定义语句部分：
       1、本函数中仅允许定义 3个简单变量 + 1个行指针变量 + 1个简单指针变量 */

       /* 函数执行语句部分（要求同average）*/
    int(*line)[STUDENT_NUM] = score, * column, fail, sum;
    cout << "2门以上不及格的学生：" << endl;
    for (column = *score; column < *score + STUDENT_NUM; column++) {
        fail = 0, sum = 0;
        for (line = score; line < score + SCORE_NUM; line++)
            if (*(*line + (column - *score)) < 60)
                fail++;
        if (fail >= 2) {
            cout << "No：" << column - *score + 1;
            for (line = score; line < score + SCORE_NUM; line++) {
                cout << setw(3) << *(*line + (column - *score));
                sum += *(*line + (column - *score));
            }
            cout << " " << "平均：" << (double)sum / SCORE_NUM << endl;
        }
    }
}

/***************************************************************************
  函数名称：good
  功    能：找出平均成绩在90分以上或全部成绩在85分以上的学生
  输入参数：int(*score)[STUDENT_NUM]
  返 回 值：void
  说    明：
***************************************************************************/
void good(int(*score)[STUDENT_NUM])
{
    /* 函数定义语句部分：
       1、本函数中仅允许定义 3个简单变量 + 1个行指针变量 + 1个简单指针变量 */

       /* 函数执行语句部分（要求同average）*/
       /* 函数执行语句部分（要求同average）*/
    int(*line)[STUDENT_NUM] = score, * column, succ, sum;
    cout << "平均90以上或全部85以上的学生：" << endl;
    for (column = *score; column < *score + STUDENT_NUM; column++) {
        succ = 0, sum = 0;
        for (line = score; line < score + SCORE_NUM; line++) {
            if (*(*line + (column - *score)) >= 85)
                succ++;
            for (line = score; line < score + SCORE_NUM; line++)
                sum += *(*line + (column - *score));
            if (succ >= STUDENT_NUM || sum >= 90 * STUDENT_NUM) {
                cout << "No：" << column - *score + 1;
                for (line = score; line < score + SCORE_NUM; line++)
                    cout << setw(3) << *(*line + (column - *score));
                cout << " " << "平均：" << (double)sum / SCORE_NUM << endl;
            }
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
    int a[SCORE_NUM][STUDENT_NUM] = {
        {91,92,93,97},  //第1-4个学生的第1门课成绩
        {81,82,83,85},  //第1-4个学生的第2门课成绩
        {71,72,99,87},  //第1-4个学生的第3门课成绩
        {61,32,80,91},  //第1-4个学生的第4门课成绩
        {51,52,95,88} };//第1-4个学生的第5门课成绩
    /* 除上面的预置数组外，本函数中仅允许定义 1个行指针变量 + 1个简单指针变量 */

    /* 函数执行语句部分（要求同average）*/
    int(*stu)[STUDENT_NUM] = a, * subj = *stu;
    cout << "初始信息：" << endl;
    for (; stu < a + SCORE_NUM; stu++) {
        cout << "No.1-4学生的第" << stu - a + 1 << "门课的成绩：";
        for (; subj < *stu + STUDENT_NUM; subj++) {
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

    return 0;
}
