#include<iostream>
using namespace std;
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<stack>

struct TreeNode{
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char x): val(x),left(nullptr),right(nullptr){}
};



TreeNode* helper(unordered_map<char,int>& inorder_map,int inleft,int inright,string levelorder){
    if(inleft>inright) return nullptr;
   
    string range_levelorder="";
    for (char a:levelorder){
        if(inorder_map[a]>=inleft&&inorder_map[a]<=inright) range_levelorder+=a;
    }
    char rootval=range_levelorder[0];
    TreeNode* root=new TreeNode(rootval);
    int root_index=inorder_map[rootval];
    int leftsize=root_index-inleft;
    
    //注意要考虑迭代范围，这里要减掉inleft
    
    root->left=helper(inorder_map,inleft,inleft+leftsize-1,levelorder);
    root->right=helper(inorder_map,root_index+1,inright,levelorder);
    return root;
}

TreeNode* buildTree(string inorder,string levelorder){
    int n=inorder.size();
    unordered_map<char,int> inorder_map;
    for(int i=0;i<n;i++){
        inorder_map[inorder[i]]=i;
    }
    return helper(inorder_map,0,n-1,levelorder);
}

string preorder(TreeNode* root){
    string res="";
    stack<TreeNode*> pre_stack;
    pre_stack.push(root);
    while(!pre_stack.empty()){
        TreeNode* temp=pre_stack.top();
        res+=temp->val;
        pre_stack.pop();
        if(temp->right) pre_stack.push(temp->right);
        if(temp->left) pre_stack.push(temp->left);
        //注意，栈是后进后出，因此先push右边的子节点
    }
    return res;
}

int main(){
    string in,level;
    cin>>in>>level;
    TreeNode* root=buildTree(in,level);
    cout<<preorder(root);
}