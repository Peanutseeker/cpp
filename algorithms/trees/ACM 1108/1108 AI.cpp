#include<iostream>
using namespace std;
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<stack>

struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char x): val(x), left(nullptr), right(nullptr) {}
};

// Helper function to build the tree recursively
TreeNode* helper(unordered_map<char, int>& inorder_map, int inleft, int inright, unordered_set<char>& levelorder) {
    if (inleft > inright) return nullptr;

    // The first element in levelorder set is the root
    char rootval = *(levelorder.begin());
    TreeNode* root = new TreeNode(rootval);
    int root_index = inorder_map[rootval];

    int leftsize = root_index - inleft;  // Number of nodes in the left subtree

    // Create a new set for the left subtree
    unordered_set<char> left_set;
    for (int i = 0; i < leftsize; i++) {
        // Find the element in inorder that belongs to the left subtree
        char left_char = inorder_map.find(inorder_map.find(rootval)->first)->first;
        left_set.insert(left_char);
        levelorder.erase(left_char);
    }

    root->left = helper(inorder_map, inleft, root_index - 1, left_set);
    root->right = helper(inorder_map, root_index + 1, inright, levelorder);

    return root;
}

// Function to build the tree from inorder and levelorder traversal strings
TreeNode* buildTree(string inorder, string levelorder) {
    int n = inorder.size();
    unordered_map<char, int> inorder_map;
    
    // Create a map of inorder character to index
    for (int i = 0; i < n; i++) {
        inorder_map[inorder[i]] = i;
    }

    unordered_set<char> levelset;
    for (char a : levelorder) {
        levelset.insert(a);  // Insert all characters of levelorder in the set
    }

    return helper(inorder_map, 0, n - 1, levelset);
}

// Preorder traversal of the tree (non-recursive)
string preorder(TreeNode* root) {
    string res = "";
    if (!root) return res;

    stack<TreeNode*> pre_stack;
    pre_stack.push(root);
    
    while (!pre_stack.empty()) {
        TreeNode* temp = pre_stack.top();
        pre_stack.pop();
        res += temp->val;  // Add root node value to result string
        
        // Push right child first, so left child is processed first
        if (temp->right) pre_stack.push(temp->right);
        if (temp->left) pre_stack.push(temp->left);
    }

    return res;
}

int main() {
    string in, level;
    cin >> in >> level;
    TreeNode* root = buildTree(in, level);
    cout << preorder(root);  // Output the preorder traversal
}
