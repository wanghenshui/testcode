/*
��Ŀ����

��ʵ��һ���㷨���ڲ�ʹ�ö������ݽṹ�ʹ���ռ������£���תһ���������ַ���(����ʹ�õ������̱���)��

����һ��string iniString���뷵��һ��string��Ϊ��ת����ַ�������֤�ַ����ĳ���С�ڵ���5000��
����������

"This is nowcoder"

���أ�"redocwon si sihT"

*/
// ûɶֵ��˵��
class Reverse {
public:
    string reverseString(string iniString) {
        // write code here
        return string(iniString.rbegin(),iniString.rend());
    }
};