#include <vector>
#include <iostream>
#include <algorithm>
using std::reverse;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
/*
��Ŀ����

����� �������� ��ָ�ڶ���һ������Ϊ n ������ �����е�Ԫ�ض������ƶ� һ�� ��Ԫ��
�ٸ����� : ���������[1, 2, 3, 4, 5]����������λ������ ���ս������[3, 4, 5, 1, 2]��

	���ڸ���һ������Ϊ n ������ �Լ�������ת�ĵ�λ�� d
	��Ҫ�����ת������� ��һ�пո���ָ����������б�ʾ
	�����ʽ

	��׼����

	��һ�и������������ÿո�ָ���ʾ n �� d
	������һ�� n ���ÿո�ָ���������ʾԭʼ���� a
	��������

	1 <= n <= 100000
	1 <= d <= n
	1 <= a[i] <= 1000000
	�����ʽ

	��׼���

	���һ�г���Ϊ n �ÿո�ָ����������� ��ʾ a ����������ת d ����Ԫ�Ժ�Ľ��
	��������

	5 4
	1 2 3 4 5
	�������

	5 1 2 3 4
	*/

int main()
{
	int n;
	int d;
	cin >> n >> d;
	vector<int> res(n, 0);
	for (int i = 0; i < n; i++) { cin >> res[i]; }

	reverse(res.begin(), res.begin() + d);
	reverse(res.begin() + d, res.end());
	reverse(res.begin(), res.end());

	for (auto&v : res)	cout << v << " ";
	cout << endl;

	//system("pause");
	return 0;
}
