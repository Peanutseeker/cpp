#include <iostream>
using namespace std;
#include <queue>

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    int height=0;
    TreeNode()=default;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){};
};

int height(TreeNode* node) {
    if (node) {
        return node->height;
    } else {
        return -1;
    }
}

void updateheight(TreeNode* node){
    node->height=max(height(node->left),height(node->right))+1;
}

int balance(TreeNode* node){
    return node?height(node->left)-height(node->right):0;
}

//右旋
//把旋转函数写成返回形式，可以直接返回修改后的子树，赋值方便
TreeNode* rightrotate(TreeNode* node){
    TreeNode* root=node;
    TreeNode* child=node->left;
    TreeNode* grandchild=child->right;
    //修改节点指针来左旋右旋
    child->right=root;
    root->left=grandchild;
    //更新节点高度,注意从下到上！
    updateheight(child);
    updateheight(node);
    return child;
}

TreeNode* leftrotate(TreeNode* node){
    TreeNode* root=node;
    TreeNode* child=node->right;
    TreeNode* grandchild=child->left;
    //修改节点指针来左旋右旋
    child->left=root;
    root->right=grandchild;
    //更新节点高度
    updateheight(child);
    updateheight(node);
    return child;
}

TreeNode* rotate(TreeNode* node){
    if(balance(node)>1){//左偏树右旋
        if(balance(node->left)<0) node->left=leftrotate(node->left);
            //左偏且子节点右偏，子节点左旋，然后该节点右旋
        return rightrotate(node);
    }
    else if(balance(node)<-1){//镜像
        if(balance(node->right)>0) node->right=rightrotate(node->right);
        return leftrotate(node);
    }
    else return node;
}

//AVL树的插入
//插入后从该节点开始从下到上旋转平衡
//用递归实现由后到前，先开栈再在回收时执行旋转操作，注意要用节点指针return
TreeNode* insert(TreeNode* root, int x){
    if(root){
        if(root->val<x) root->right= insert(root->right,x);
        else if(root->val>x)  root->left=insert(root->left,x);
        else return root;
    } 
    else {
        return new TreeNode(x);
    }
    updateheight(root);
    return rotate(root);
}

//删除操作
//删除后一样从底端到顶端执行旋转操作

//为了递归和修改方便,直接在子树上处理数据，全部改成返回树节点而不是void


TreeNode* remove(TreeNode* root, int x){
    if(!root) return nullptr;
    else if(root->val<x){
        root->right=remove(root->right,x);
    }
    else if(root->val>x) root->left=remove(root->left,x);
    else {
        if(!root->left&&!root->right) {
            delete root;
            return nullptr;
        }
        else if(root->left||root->right){
            TreeNode* child=root->left?root->left:root->right;
            delete root;
            return child;
        }
        else {
            TreeNode* successor=root->right;
            while(successor->left){
                successor=successor->left;
            }
            root->val=successor->val;
            root->right=remove(root->right, successor->val);
            //调用单子树的删除函数，注意由于要对右子树做旋转操作
            //不能直接删除successor子节点，要对右边的树全部做一次平衡旋转
        }
    }
    updateheight(root);//修改完节点不要忘了修改高度！
    
    return rotate(root);
}

//Level order traversal, in essence BFS
//BFS模版：先设一个队列，把初始节点塞进队列，后续每碰到一个节点，把节点塞进队列
//处理完这个节点把它的下面几个子节点塞进队列，然后把这个节点弹出去
//直至全部处理完成为止
void printLevelOrder(TreeNode* root){
    if(!root){
        cout<<"Empty Tree"<<endl;
        return;//直接结束函数
    }
    else{
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int level=q.size();
            for(int i=0;i<level;i++){
                //Note: you need this to record what level you're at
                TreeNode* temp=q.front();
                cout<<temp->val<<"("<<balance(temp)<<")"<<" ";
                if(temp->left) q.push(temp->left);
                if(temp->right) q.push(temp->right);
                q.pop();
        }
        cout<<endl;
        }
    }
}

bool isBalanced(TreeNode* root){
    if(!root) return true;
    if(balance(root)<=-2 || balance(root)>=2) return false;
    else return isBalanced(root->left) &&isBalanced(root->right);
}

bool isBST(TreeNode* root, TreeNode* min = nullptr, TreeNode* max = nullptr) {
    if (!root) return true;
    
    if ((min && root->val <= min->val) || (max && root->val >= max->val))
        return false;
    
    return isBST(root->left, min, root) && isBST(root->right, root, max);
}

// Free memory
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}


int main() {
    TreeNode* root = nullptr;
    
    cout << "=== Testing AVL insertion ===" << endl;
    
    // Test 1: Simple insertions
    vector<int> values = {10, 20, 30, 15, 5, 25};
    for (int val : values) {
        root = insert(root, val);
        cout << "Inserted " << val << " - Tree structure:" << endl;
        printLevelOrder(root);
        cout << "Is AVL balanced? " << (isBalanced(root) ? "Yes" : "No") << endl;
        cout << "Is BST? " << (isBST(root) ? "Yes" : "No") << endl;
        cout << endl;
    }
    
    // Test 2: Sequential insertions (worst case for BST)
    cout << "=== Testing sequential insertions ===" << endl;
    TreeNode* root2 = nullptr;
    for (int i = 1; i <= 10; i++) {
        root2 = insert(root2, i);
    }
    cout << "Sequential insertion 1-10 - Tree structure:" << endl;
    printLevelOrder(root2);
    cout << "Is AVL balanced? " << (isBalanced(root2) ? "Yes" : "No") << endl;
    cout << "Is BST? " << (isBST(root2) ? "Yes" : "No") << endl;
    cout << endl;
    
    // Test 3: Testing deletions
    cout << "=== Testing AVL deletion ===" << endl;
    
    vector<int> to_delete = {20, 10, 25};
    for (int val : to_delete) {
        cout << "Deleting " << val << endl;
        root = remove(root, val);
        cout << "After deletion - Tree structure:" << endl;
        printLevelOrder(root);
        cout << "Is AVL balanced? " << (isBalanced(root) ? "Yes" : "No") << endl;
        cout << "Is BST? " << (isBST(root) ? "Yes" : "No") << endl;
        cout << endl;
    }
    
    // Test 4: Delete non-existent element
    cout << "Deleting non-existent element 100:" << endl;
    root = remove(root, 100);
    printLevelOrder(root);
    
    // Clean up
    deleteTree(root);
    deleteTree(root2);
    
    return 0;
}
