/*你需要判断一棵 二叉树 是否是 一棵二叉搜索树。

二叉搜索树 定义如下：
若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；它的左、右子树也分别为二叉搜索树。

你不需要从标准输入中读入或者向标准输出打印。你只需要将完成一个函数checkBST即可，它返回true即表示“以root为根的二叉树是二叉搜索树”，它返回false即表示“不是二叉搜索树”。
可以假定你需要判断的二叉树里，任意两个节点的值都不相同，且每个节点的值都不大于10000。*/

//二叉搜索树的中序遍历是一个递增序列
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