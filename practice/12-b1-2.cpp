/* 2153680 ������ �Ű� */
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM	4
#define SCORE_NUM	5

/* --- ���������κ���ʽ��ȫ�ֱ��� --- */

/***************************************************************************
  �������ƣ�average
  ��    �ܣ����һ�ſε�ƽ����
  ���������int(*score)[STUDENT_NUM]
  �� �� ֵ��void
  ˵    ����
***************************************************************************/
void average(int(*score)[STUDENT_NUM])//    int a[SCORE_NUM][STUDENT_NUM]
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
    int* p, sum = 0;
    for (p = *score; p < *score + STUDENT_NUM; p++)
        sum += *p;
    cout << "��1�ſ�ƽ���֣�" << (double)sum / STUDENT_NUM << endl;

}

/***************************************************************************
  �������ƣ�fail
  ��    �ܣ��ҳ����������Ͽγ̲������ѧ��
  ���������int(*score)[STUDENT_NUM]
  �� �� ֵ��void
  ˵    ����
***************************************************************************/
void fail(int(*score)[STUDENT_NUM])
{
    /* ����������䲿�֣�
       1���������н������� 3���򵥱��� + 1����ָ����� + 1����ָ����� */

       /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
    int(*line)[STUDENT_NUM] = score, * column, fail, sum;
    cout << "2�����ϲ������ѧ����" << endl;
    for (column = *score; column < *score + STUDENT_NUM; column++) {
        fail = 0, sum = 0;
        for (line = score; line < score + SCORE_NUM; line++)
            if (*(*line + (column - *score)) < 60)
                fail++;
        if (fail >= 2) {
            cout << "No��" << column - *score + 1;
            for (line = score; line < score + SCORE_NUM; line++) {
                cout << setw(3) << *(*line + (column - *score));
                sum += *(*line + (column - *score));
            }
            cout << " " << "ƽ����" << (double)sum / SCORE_NUM << endl;
        }
    }
}

/***************************************************************************
  �������ƣ�good
  ��    �ܣ��ҳ�ƽ���ɼ���90�����ϻ�ȫ���ɼ���85�����ϵ�ѧ��
  ���������int(*score)[STUDENT_NUM]
  �� �� ֵ��void
  ˵    ����
***************************************************************************/
void good(int(*score)[STUDENT_NUM])
{
    /* ����������䲿�֣�
       1���������н������� 3���򵥱��� + 1����ָ����� + 1����ָ����� */

       /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
       /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
    int(*line)[STUDENT_NUM] = score, * column, succ, sum;
    cout << "ƽ��90���ϻ�ȫ��85���ϵ�ѧ����" << endl;
    for (column = *score; column < *score + STUDENT_NUM; column++) {
        succ = 0, sum = 0;
        for (line = score; line < score + SCORE_NUM; line++) {
            if (*(*line + (column - *score)) >= 85)
                succ++;
            for (line = score; line < score + SCORE_NUM; line++)
                sum += *(*line + (column - *score));
            if (succ >= STUDENT_NUM || sum >= 90 * STUDENT_NUM) {
                cout << "No��" << column - *score + 1;
                for (line = score; line < score + SCORE_NUM; line++)
                    cout << setw(3) << *(*line + (column - *score));
                cout << " " << "ƽ����" << (double)sum / SCORE_NUM << endl;
            }
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
    int a[SCORE_NUM][STUDENT_NUM] = {
        {91,92,93,97},  //��1-4��ѧ���ĵ�1�ſγɼ�
        {81,82,83,85},  //��1-4��ѧ���ĵ�2�ſγɼ�
        {71,72,99,87},  //��1-4��ѧ���ĵ�3�ſγɼ�
        {61,32,80,91},  //��1-4��ѧ���ĵ�4�ſγɼ�
        {51,52,95,88} };//��1-4��ѧ���ĵ�5�ſγɼ�
    /* �������Ԥ�������⣬�������н������� 1����ָ����� + 1����ָ����� */

    /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
    int(*stu)[STUDENT_NUM] = a, * subj = *stu;
    cout << "��ʼ��Ϣ��" << endl;
    for (; stu < a + SCORE_NUM; stu++) {
        cout << "No.1-4ѧ���ĵ�" << stu - a + 1 << "�ſεĳɼ���";
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
