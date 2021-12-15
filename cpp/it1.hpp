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
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root!=nullptr)
        {
            auto lres = inorderTraversal(root->left);
            for(auto&v:lres)
                res.push_back(v);
            res.push_back(root->val);
            auto rres = inorderTraversal(root->right);
            for(auto&v:rres)
                res.push_back(v);
        }
        return res;
    }
};