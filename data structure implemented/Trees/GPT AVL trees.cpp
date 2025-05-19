#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class AVLTree {
private:
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
        int height;
        
        TreeNode() : val(0), left(nullptr), right(nullptr), height(0) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr), height(0) {}
    };
    
    TreeNode* root;
    
    // 获取节点高度
    int height(TreeNode* node) {
        if (node) {
            return node->height;
        } else {
            return -1;
        }
    }
    
    // 更新节点高度
    void updateHeight(TreeNode* node) {
        if (node) {
            node->height = max(height(node->left), height(node->right)) + 1;
        }
    }
    
    // 计算平衡因子
    int balanceFactor(TreeNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    
    // 右旋
    TreeNode* rightRotate(TreeNode* node) {
        TreeNode* root = node;
        TreeNode* child = node->left;
        TreeNode* grandchild = child->right;
        
        // 修改节点指针来右旋
        child->right = root;
        root->left = grandchild;
        
        // 更新节点高度，注意从下到上
        updateHeight(root);
        updateHeight(child);
        
        return child;
    }
    
    // 左旋
    TreeNode* leftRotate(TreeNode* node) {
        TreeNode* root = node;
        TreeNode* child = node->right;
        TreeNode* grandchild = child->left;
        
        // 修改节点指针来左旋
        child->left = root;
        root->right = grandchild;
        
        // 更新节点高度
        updateHeight(root);
        updateHeight(child);
        
        return child;
    }
    
    // 旋转平衡
    TreeNode* rotate(TreeNode* node) {
        if (balanceFactor(node) > 1) {  // 左偏树右旋
            if (balanceFactor(node->left) < 0) 
                node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        else if (balanceFactor(node) < -1) {  // 右偏树左旋
            if (balanceFactor(node->right) > 0) 
                node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        else return node;
    }
    
    // 插入节点（递归实现）
    TreeNode* insertNode(TreeNode* node, int x) {
        if (node) {
            if (node->val < x) 
                node->right = insertNode(node->right, x);
            else if (node->val > x)  
                node->left = insertNode(node->left, x);
            else 
                return node;  // 值已存在，不做改变
        } 
        else {
            return new TreeNode(x);
        }
        
        updateHeight(node);
        return rotate(node);
    }
    
    // 删除节点（递归实现）
    TreeNode* removeNode(TreeNode* node, int x) {
        if (!node) return nullptr;
        
        if (node->val < x) {
            node->right = removeNode(node->right, x);
        }
        else if (node->val > x) {
            node->left = removeNode(node->left, x);
        }
        else {  // 找到要删除的节点
            if (!node->left && !node->right) {  // 叶子节点
                delete node;
                return nullptr;
            }
            else if (node->left && !node->right) {  // 只有左子树
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            else if (!node->left && node->right) {  // 只有右子树
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else {  // 有两个子节点
                // 找到右子树的最小节点（中序后继）
                TreeNode* successor = node->right;
                while (successor->left) {
                    successor = successor->left;
                }
                
                // 用后继节点的值替换当前节点
                node->val = successor->val;
                
                // 删除后继节点
                node->right = removeNode(node->right, successor->val);
            }
        }
        
        updateHeight(node);
        return rotate(node);
    }
    
    // 检查是否为BST
    bool isBSTHelper(TreeNode* node, TreeNode* min = nullptr, TreeNode* max = nullptr) {
        if (!node) return true;
        
        if ((min && node->val <= min->val) || (max && node->val >= max->val))
            return false;
        
        return isBSTHelper(node->left, min, node) && isBSTHelper(node->right, node, max);
    }
    
    // 检查是否平衡
    bool isBalancedHelper(TreeNode* node) {
        if (!node) return true;
        
        int bf = balanceFactor(node);
        if (bf <= -2 || bf >= 2) return false;
        
        return isBalancedHelper(node->left) && isBalancedHelper(node->right);
    }
    
    // 清理树
    void deleteTreeHelper(TreeNode* node) {
        if (!node) return;
        deleteTreeHelper(node->left);
        deleteTreeHelper(node->right);
        delete node;
    }
    
public:
    // 构造函数
    AVLTree() : root(nullptr) {}
    
    // 析构函数
    ~AVLTree() {
        clear();
    }
    
    // 插入值
    void insert(int x) {
        root = insertNode(root, x);
    }
    
    // 删除值
    void remove(int x) {
        root = removeNode(root, x);
    }
    
    // 检查值是否存在
    bool contains(int x) {
        TreeNode* current = root;
        while (current) {
            if (current->val == x) return true;
            else if (current->val < x) current = current->right;
            else current = current->left;
        }
        return false;
    }
    
    // 清空树
    void clear() {
        deleteTreeHelper(root);
        root = nullptr;
    }
    
    // 检查树是否为AVL平衡树
    bool isBalanced() {
        return isBalancedHelper(root);
    }
    
    // 检查树是否为BST
    bool isBST() {
        return isBSTHelper(root);
    }
    
    // 层序遍历打印（带平衡因子）
    void printLevelOrder() {
        if (!root) {
            cout << "Empty Tree" << endl;
            return;
        }
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* temp = q.front();
                cout << temp->val << "(" << balanceFactor(temp) << ") ";
                
                if (temp->left) q.push(temp->left);
                if (temp->right) q.push(temp->right);
                
                q.pop();
            }
            cout << endl;
        }
    }
    
    // 判断树是否为空
    bool isEmpty() {
        return root == nullptr;
    }
};

int main() {
    AVLTree avl;
    
    cout << "=== Testing AVL insertion ===" << endl;
    
    // 测试1：简单插入
    vector<int> values = {10, 20, 30, 15, 5, 25};
    for (int val : values) {
        avl.insert(val);
        cout << "Inserted " << val << " - Tree structure:" << endl;
        avl.printLevelOrder();
        cout << "Is AVL balanced? " << (avl.isBalanced() ? "Yes" : "No") << endl;
        cout << "Is BST? " << (avl.isBST() ? "Yes" : "No") << endl;
        cout << endl;
    }
    
    // 测试2：顺序插入（BST的最坏情况）
    cout << "=== Testing sequential insertions ===" << endl;
    AVLTree avl2;
    for (int i = 1; i <= 10; i++) {
        avl2.insert(i);
    }
    cout << "Sequential insertion 1-10 - Tree structure:" << endl;
    avl2.printLevelOrder();
    cout << "Is AVL balanced? " << (avl2.isBalanced() ? "Yes" : "No") << endl;
    cout << "Is BST? " << (avl2.isBST() ? "Yes" : "No") << endl;
    cout << endl;
    
    // 测试3：测试删除
    cout << "=== Testing AVL deletion ===" << endl;
    
    vector<int> to_delete = {20, 10, 25};
    for (int val : to_delete) {
        cout << "Deleting " << val << endl;
        avl.remove(val);
        cout << "After deletion - Tree structure:" << endl;
        avl.printLevelOrder();
        cout << "Is AVL balanced? " << (avl.isBalanced() ? "Yes" : "No") << endl;
        cout << "Is BST? " << (avl.isBST() ? "Yes" : "No") << endl;
        cout << endl;
    }
    
    // 测试4：删除不存在的元素
    cout << "Deleting non-existent element 100:" << endl;
    avl.remove(100);
    avl.printLevelOrder();
    
    // 无需手动清理内存，析构函数会自动调用
    
    return 0;
}