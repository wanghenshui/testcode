/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */


class Solution {
    void inorder_traversal(TreeNode* root, vector<int>& nodes)
    {
	    if (root == nullptr)
		    return;
	    inorder_traversal(root->left, nodes);
	    nodes.push_back(root->val);
	    inorder_traversal(root->right, nodes);
    }
public:
    bool isValidBST(TreeNode* root) {
        
        vector<int> nodes;
	    inorder_traversal(root, nodes);
	    for (int i = 1; i < nodes.size(); ++i)
		    if (!(nodes[i - 1] < nodes[i]))
    			return false;
	    return true;
    }
};