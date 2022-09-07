/* 2153680 ������ ��14 */
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM	4
#define SCORE_NUM	5

/* --- ���������κ���ʽ��ȫ�ֱ��� --- */

/***************************************************************************
  �������ƣ�average
  ��    �ܣ����һ�ſε�ƽ����
  ���������(*score)[SCORE_NUM]
  �� �� ֵ��void
  ˵    ���������������ں����м���
***************************************************************************/
void average(int(*score)[SCORE_NUM])
{
    /* ����������䲿�֣�
       1���������н������� 1���򵥱��� + 1��ָ����� */

       /* ����ִ����䲿�֣�
          1���������ٶ����κ����͵ı��������� for (int i=0;...������ʽ�������
          2��ѭ������������ָ���������������в��������[]��ʽ��������
             ������int a[10], i;
                     for(i=0; i<10; i++)
                         cout << a[i];
             ����  ��int a[10], p;
                     for(p=a; p<a+10; p++)
                         cout << *p;          */
    int(*p)[SCORE_NUM], sum = 0;
    for (p = score; p < score + STUDENT_NUM; p++)
        sum += **p;
    cout << "��1�ſ�ƽ���֣�"<< (double)sum / STUDENT_NUM << endl;

}

/***************************************************************************
  �������ƣ�fail
  ��    �ܣ��ҳ����������Ͽγ̲������ѧ��
  ���������(*score)[SCORE_NUM]
  �� �� ֵ��void
  ˵    ���������������ں����м���
***************************************************************************/
void fail(int(*score)[SCORE_NUM])
{
    /* ����������䲿�֣�
       1���������н������� 2���򵥱��� + 1����ָ����� + 1����ָ����� */

       /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
    int(*line)[SCORE_NUM], *column,fail, sum;
    cout << "2�����ϲ������ѧ����" << endl;
    for (line = score; line < score + STUDENT_NUM; line++) {
        fail = 0, sum = 0;
        for (column = *line; column < *line + SCORE_NUM; column++) 
            if (*column < 60)
                fail++;
        if (fail >= 2) {
            cout << "No��" << line - score + 1;
            for (column = *line; column < *line + SCORE_NUM; column++) {
                cout << setw(3)<< * column;
                sum += *column;
            }
            cout << " " << "ƽ����" << (double)sum / SCORE_NUM << endl;
        }
    }
}

/***************************************************************************
  �������ƣ�good
  ��    �ܣ��ҳ�ƽ���ɼ���90�����ϻ�ȫ���ɼ���85�����ϵ�ѧ��
  ���������(*score)[SCORE_NUM]
  �� �� ֵ��void
  ˵    ����
***************************************************************************/
void good(int(*score)[SCORE_NUM])
{
    /* ����������䲿�֣�
       1���������н������� 2���򵥱��� + 1����ָ����� + 1����ָ����� */

       /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
    int(*line)[SCORE_NUM], * column, succ, sum;
    cout << "ƽ��90���ϻ�ȫ��85���ϵ�ѧ����" << endl;
    for (line = score; line < score + STUDENT_NUM; line++) {
        succ = 0, sum = 0;
        for (column = *line; column < *line + SCORE_NUM; column++) {
            if (*column >= 85)
                succ++;
            sum += *column;
        }
        if (succ == 5 || sum >= 90 * SCORE_NUM) {
            cout << "No��" << line - score + 1;
            for (column = *line; column < *line + SCORE_NUM; column++) {
                cout << setw(3) << *column;
            }
            cout << " " << "ƽ����" << (double)sum / SCORE_NUM << endl;
        }
    }

}

/***************************************************************************
  �������ƣ�main
  ��    �ܣ��������顢ָ�룬���ø�����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
    int a[STUDENT_NUM][SCORE_NUM] = {
        {91, 81, 71, 61, 51},	//��1��ѧ����1-5�ſεĳɼ�
        {92, 82, 72, 32, 52},   //��2��ѧ����1-5�ſεĳɼ�
        {93, 83, 99, 80, 95},   //��3��ѧ����1-5�ſεĳɼ�
        {97, 85, 87, 91, 88} }; //��4��ѧ����1-5�ſεĳɼ�

    /* �������Ԥ�������⣬�������н������� 1����ָ����� + 1����ָ����� */
    int(*stu)[SCORE_NUM] = a, * subj = *stu;
    cout << "��ʼ��Ϣ��" << endl;
    for (; stu < a + STUDENT_NUM; stu++) {
        cout << "No." << stu - a + 1 << "��1-5�ſγɼ���";
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

    /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
    return 0;
}
