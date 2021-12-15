/*����Ҫ�ж�һ�� ������ �Ƿ��� һ�ö�����������

���������� �������£�
���������������գ��������������н���ֵ��С�����ĸ�����ֵ�����������������գ��������������н���ֵ���������ĸ�����ֵ��������������Ҳ�ֱ�Ϊ������������

�㲻��Ҫ�ӱ�׼�����ж���������׼�����ӡ����ֻ��Ҫ�����һ������checkBST���ɣ�������true����ʾ����rootΪ���Ķ������Ƕ�������������������false����ʾ�����Ƕ�������������
���Լٶ�����Ҫ�жϵĶ���������������ڵ��ֵ������ͬ����ÿ���ڵ��ֵ��������10000��*/

//���������������������һ����������
void inorder_traversal(Node* root, vector<int>& nodes)
{
	if (root == nullptr)
		return;
	inorder_traversal(root->left, nodes);
	nodes.push_back(root->data);
	inorder_traversal(root->right, nodes);
}

bool checkBST(Node* root)
{
	vector<int> nodes;
	inorder_traversal(root, nodes);
	for (int i = 1; i < nodes.size(); ++i)
		if (!(nodes[i - 1] < nodes[i]))
			return false;
	return true;
}