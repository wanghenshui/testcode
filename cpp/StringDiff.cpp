/*
��Ŀ����

��ʵ��һ���㷨��ȷ��һ���ַ����������ַ��Ƿ�ȫ����ͬ����������Ҫ������ʹ�ö���Ĵ洢�ṹ��

����һ��string iniString���뷵��һ��boolֵ,True���������ַ�ȫ����ͬ��False���������ͬ���ַ�����֤�ַ����е��ַ�ΪASCII�ַ����ַ����ĳ���С�ڵ���3000��
����������

"aeiou"

���أ�True

"BarackObama"

���أ�False


*/

//����˼· 
//����ȥ��
//hash ����ȥ��
//ע���ַ�256��������һ�������Ż��ĵ�
//������� ����������뵽

class Different {
public:
	bool checkDifferent(string iniString) {
		// write code here
		const int SIZE = iniString.size();
		if (SIZE > 256)
			return false;
		sort(iniString.begin(), iniString.end());
		iniString.erase(unique(iniString.begin(), iniString.end()), iniString.end());

		return SIZE == iniString.size();
	}
};