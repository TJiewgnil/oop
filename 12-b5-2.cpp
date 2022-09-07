/* 2153680 赵凌葳 信14 */
#include <iostream>
#include <iomanip>
using namespace std;
const char* sp = "=====================================";
#define width 8

/***************************************************************************
  函数名称：matrix_print
  功    能：打印矩阵
  输入参数：const char *tip, T (&matrix)[N]
  返 回 值：void
  说    明：每个数字宽度为8，右对齐
***************************************************************************/
template <typename T, size_t N>
void matrix_print(const char *tip, T (&matrix)[N])	//将...替换为相应内容
{
	int line = (int)N, column = (int)(sizeof(matrix) / N / sizeof(**matrix));
	cout << tip << endl;
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++)
			cout << setw(width) << *(*(matrix + i) + j);
		cout << endl;
	}
	/* 按需增加内容 */
	return;
}

/***************************************************************************
  函数名称：trans
  功    能：对数据进行强制类型转换
  输入参数：T(aim), T2(value)
  返 回 值：(T)value
  说    明：
***************************************************************************/
template <typename T, typename T2>
T trans(T(aim), T2(value))
{
	return (T)value;
}


/***************************************************************************
  函数名称：matrix_addition
  功    能：相加
  输入参数：T (&m_add)[N], T(&m1)[N], T(&m2)[N]
  返 回 值：void
  说    明：
***************************************************************************/
template <typename T, size_t N>
void matrix_addition(T (&m_add)[N], T(&m1)[N], T(&m2)[N])	//将...替换为相应内容
{
	/* 按需增加内容 */
	cout << "源矩阵1 : 行=" << N << " 列=" << sizeof(m1) / N / sizeof(**m1) << " 占用空间=" << sizeof(m1) << "字节" << endl;
	cout << "源矩阵2 : 行=" << N << " 列=" << sizeof(m2) / N / sizeof(**m2) << " 占用空间=" << sizeof(m2) << "字节" << endl;
	cout << "和矩阵  : 行=" << N << " 列=" << sizeof(m_add) / N / sizeof(**m_add) << " 占用空间=" << sizeof(m_add) << "字节" << endl;
	for (int i = 0; i < (int)N; i++)
		for (int j = 0; j < (int)(sizeof(m_add) / N / sizeof(**m_add)); j++)
			*(*(m_add + i) + j) = trans(**m_add, *(*(m1 + i) + j) + *(*(m2 + i) + j));
}


/***************************************************************************
  函数名称：matrix_multiplication
  功    能：相乘
  输入参数：三个数组T(&m_mul)[N], T1(&m1)[N1], T2(&m2)[N2]
  返 回 值：void
  说    明：
***************************************************************************/
template <typename T,size_t N, typename T1, size_t N1, typename T2, size_t N2>
void matrix_multiplication(T(&m_mul)[N], T1(&m1)[N1], T2(&m2)[N2])	//将...替换为相应内容
{
	cout << typeid(T).name() << endl;
	/* 按需增加内容 */
	cout << "源矩阵1 : 行=" << N1 << " 列=" << sizeof(m1) / N1 / sizeof(**m1) << " 占用空间=" << sizeof(m1) << "字节" << endl;
	cout << "源矩阵2 : 行=" << N2 << " 列=" << sizeof(m2) / N2 / sizeof(**m2) << " 占用空间=" << sizeof(m2) << "字节" << endl;
	cout << "积矩阵  : 行=" << N << " 列=" << sizeof(m_mul) / N / sizeof(**m_mul) << " 占用空间=" << sizeof(m_mul) << "字节" << endl;
	int line, column, link;
	for (line = 0; line < (int)N; line++)
		for (column = 0; column < (int)(sizeof(m_mul) / N / sizeof(**m_mul)); column++) {
			*(*(m_mul + line) + column) = 0;
			for (link = 0; link < (int)N2; link++)
				*(*(m_mul + line) + column) += trans(**m_mul, *(*(m1 + line) + link) * *(*(m2 + link) + column));
		}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准更改
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
	matrix_print("加法运算，源矩阵1：", t1);
	matrix_print("加法运算，源矩阵2：", t2);
	matrix_addition(t_add, t1, t2);	//将t1和t2的和放入t_add中，人工保证三个矩阵行列一致
	matrix_print("加法运算，和矩阵 ：", t_add);
	cout << sp << endl;
	matrix_print("乘法运算，源矩阵1：", t1);
	matrix_print("乘法运算，源矩阵2：", t3);
	matrix_multiplication(t_mul, t1, t3);	//将t1和t2的和放入t_add中，人工保证三个矩阵行列一致
	matrix_print("乘法运算，积矩阵 ：", t_mul);
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
	/* 不要问为什么矩阵乘法数据类型不同，故意的 */
	float f3[4][3] = {
		{12.12f, 11.11f, 10.10f},
		{9.9f, 8.8f, 7.7f},
		{6.6f, 5.5f, 4.4f},
		{3.3f, 2.2f, 1.1f}
	};
	int i_mul[2][3];

	matrix_print("加法运算，源矩阵1：", d1);
	matrix_print("加法运算，源矩阵2：", d2);
	matrix_addition(d_add, d1, d2);	//将d1和d2的和放入d_add中，人工保证三个矩阵行列一致
	matrix_print("加法运算，和矩阵 ：", d_add);
	cout << sp << endl;
	matrix_print("乘法运算，源矩阵1：", d1);
	matrix_print("乘法运算，源矩阵2：", f3);
	matrix_multiplication(i_mul, d1, f3);	//将t1和t2的和放入t_add中，人工保证三个矩阵行列一致
	matrix_print("乘法运算，积矩阵 ：", i_mul);
	cout << sp << endl;

	return 0;
}
