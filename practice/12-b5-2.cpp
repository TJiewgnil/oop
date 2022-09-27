/* 2153680 ������ �Ű� */
#include <iostream>
#include <iomanip>
using namespace std;
const char* sp = "=====================================";
#define width 8

/***************************************************************************
  �������ƣ�matrix_print
  ��    �ܣ���ӡ����
  ���������const char *tip, T (&matrix)[N]
  �� �� ֵ��void
  ˵    ����ÿ�����ֿ��Ϊ8���Ҷ���
***************************************************************************/
template <typename T, size_t N>
void matrix_print(const char* tip, T(&matrix)[N])	//��...�滻Ϊ��Ӧ����
{
	int line = (int)N, column = (int)(sizeof(matrix) / N / sizeof(**matrix));
	cout << tip << endl;
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++)
			cout << setw(width) << *(*(matrix + i) + j);
		cout << endl;
	}
	/* ������������ */
	return;
}

/***************************************************************************
  �������ƣ�trans
  ��    �ܣ������ݽ���ǿ������ת��
  ���������T(aim), T2(value)
  �� �� ֵ��(T)value
  ˵    ����
***************************************************************************/
template <typename T, typename T2>
T trans(T(aim), T2(value))
{
	return (T)value;
}


/***************************************************************************
  �������ƣ�matrix_addition
  ��    �ܣ����
  ���������T (&m_add)[N], T(&m1)[N], T(&m2)[N]
  �� �� ֵ��void
  ˵    ����
***************************************************************************/
template <typename T, size_t N>
void matrix_addition(T(&m_add)[N], T(&m1)[N], T(&m2)[N])	//��...�滻Ϊ��Ӧ����
{
	/* ������������ */
	cout << "Դ����1 : ��=" << N << " ��=" << sizeof(m1) / N / sizeof(**m1) << " ռ�ÿռ�=" << sizeof(m1) << "�ֽ�" << endl;
	cout << "Դ����2 : ��=" << N << " ��=" << sizeof(m2) / N / sizeof(**m2) << " ռ�ÿռ�=" << sizeof(m2) << "�ֽ�" << endl;
	cout << "�;���  : ��=" << N << " ��=" << sizeof(m_add) / N / sizeof(**m_add) << " ռ�ÿռ�=" << sizeof(m_add) << "�ֽ�" << endl;
	for (int i = 0; i < (int)N; i++)
		for (int j = 0; j < (int)(sizeof(m_add) / N / sizeof(**m_add)); j++)
			*(*(m_add + i) + j) = trans(**m_add, *(*(m1 + i) + j) + *(*(m2 + i) + j));
}


/***************************************************************************
  �������ƣ�matrix_multiplication
  ��    �ܣ����
  �����������������T(&m_mul)[N], T1(&m1)[N1], T2(&m2)[N2]
  �� �� ֵ��void
  ˵    ����
***************************************************************************/
template <typename T, size_t N, typename T1, size_t N1, typename T2, size_t N2>
void matrix_multiplication(T(&m_mul)[N], T1(&m1)[N1], T2(&m2)[N2])	//��...�滻Ϊ��Ӧ����
{
	cout << typeid(T).name() << endl;
	/* ������������ */
	cout << "Դ����1 : ��=" << N1 << " ��=" << sizeof(m1) / N1 / sizeof(**m1) << " ռ�ÿռ�=" << sizeof(m1) << "�ֽ�" << endl;
	cout << "Դ����2 : ��=" << N2 << " ��=" << sizeof(m2) / N2 / sizeof(**m2) << " ռ�ÿռ�=" << sizeof(m2) << "�ֽ�" << endl;
	cout << "������  : ��=" << N << " ��=" << sizeof(m_mul) / N / sizeof(**m_mul) << " ռ�ÿռ�=" << sizeof(m_mul) << "�ֽ�" << endl;
	int line, column, link;
	for (line = 0; line < (int)N; line++)
		for (column = 0; column < (int)(sizeof(m_mul) / N / sizeof(**m_mul)); column++) {
			*(*(m_mul + line) + column) = 0;
			for (link = 0; link < (int)N2; link++)
				*(*(m_mul + line) + column) += trans(**m_mul, *(*(m1 + line) + link) * *(*(m2 + link) + column));
		}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼����
***************************************************************************/
int main()
{
	int t1[3][4] = {
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12}
	};
	int t2[3][4] = {
		{12,11,10,9},
		{8,7,6,5},
		{4,3,2,1}
	};
	int t3[4][2] = {
		{1, 2},
		{3, 4},
		{5, 6},
		{7, 8}
	};
	int t_add[3][4], t_mul[3][2];

	cout << sp << endl;
	matrix_print("�ӷ����㣬Դ����1��", t1);
	matrix_print("�ӷ����㣬Դ����2��", t2);
	matrix_addition(t_add, t1, t2);	//��t1��t2�ĺͷ���t_add�У��˹���֤������������һ��
	matrix_print("�ӷ����㣬�;��� ��", t_add);
	cout << sp << endl;
	matrix_print("�˷����㣬Դ����1��", t1);
	matrix_print("�˷����㣬Դ����2��", t3);
	matrix_multiplication(t_mul, t1, t3);	//��t1��t2�ĺͷ���t_add�У��˹���֤������������һ��
	matrix_print("�˷����㣬������ ��", t_mul);
	cout << sp << endl;

	double d1[2][4] = {
		{1.1, 2.2, 3.3, 4.4},
		{5.5 ,6.6, 7.7, 8.8}
	};
	double d2[2][4] = {
		{8.8, 7.7, 6.6, 5.5},
		{4.4, 3.3, 2.2, 1.1}
	};
	double d_add[2][4];
	/* ��Ҫ��Ϊʲô����˷��������Ͳ�ͬ������� */
	float f3[4][3] = {
		{12.12f, 11.11f, 10.10f},
		{9.9f, 8.8f, 7.7f},
		{6.6f, 5.5f, 4.4f},
		{3.3f, 2.2f, 1.1f}
	};
	int i_mul[2][3];

	matrix_print("�ӷ����㣬Դ����1��", d1);
	matrix_print("�ӷ����㣬Դ����2��", d2);
	matrix_addition(d_add, d1, d2);	//��d1��d2�ĺͷ���d_add�У��˹���֤������������һ��
	matrix_print("�ӷ����㣬�;��� ��", d_add);
	cout << sp << endl;
	matrix_print("�˷����㣬Դ����1��", d1);
	matrix_print("�˷����㣬Դ����2��", f3);
	matrix_multiplication(i_mul, d1, f3);	//��t1��t2�ĺͷ���t_add�У��˹���֤������������һ��
	matrix_print("�˷����㣬������ ��", i_mul);
	cout << sp << endl;

	return 0;
}
