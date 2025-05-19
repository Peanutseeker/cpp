#include <iostream>
using namespace std;
#include <vector>
#include <stack>
//用INTMAX表示没有的元素




class ArrayBinaryTree{
    private:
        vector<int> arr;
    public: 
        ArrayBinaryTree(vector<int> b){
            arr=b;
        }
        inline int left(int x){ return 2*x+1;}
        inline int right(int x) {return 2*x+2;}
        inline int parent(int x) {return (x-1)/2;}
        inline int val(int x){return arr[x];}
        int size() {return arr.size();}
        vector<int> levelOrder(){
            vector<int> res={};
            for(int j:arr){
                if(j!=INT32_MAX) res.push_back(j);
            }
            return res;
        }
        // void dfs(int pos,string order,vector<int> &res){
        //     if(pos>=arr.size()||arr[pos]==INT32_MAX) {}
        //     else if(order=="pre"){
        //         res.push_back(arr[pos]);
        //         dfs(left(pos),"pre",res);
        //         dfs(right(pos),"pre",res);
        //     }
        //     else if(order=="in"){
        //         dfs(left(pos),"in",res);
        //         res.push_back(arr[pos]);
        //         dfs(right(pos),"in",res);
        //     }
        //     else if(order=="post"){
        //         dfs(left(pos),"post",res);
        //         dfs(right(pos),"post",res);
        //         res.push_back(arr[pos]);
        //     }
        // }
        bool legal(int x){
            return arr[x]!=INT32_MAX&&x<arr.size();
        }
        void dfs(int pos,string order,vector<int> &res){
            stack<int> dfsstack={};
            dfsstack.push(pos);
            vector<int> flag(arr.size(),0);
            while(!dfsstack.empty()){
                if(order=="pre"){
                    int cur=dfsstack.top();
                    dfsstack.pop();
                    res.push_back(arr[cur]);
                    if(legal(right(cur))) dfsstack.push(right(cur));
                    if(legal(left(cur))) dfsstack.push(left(cur));
                }
                else if(order=="in"){
                    int cur=dfsstack.top();
                    if(flag[cur]==0){
                        if(legal(left(cur))) dfsstack.push(left(cur));
                        flag[cur]++;
                    }
                    else{
                        dfsstack.pop();
                        if(legal(right(cur))) dfsstack.push(right(cur));
                        res.push_back(arr[cur]);
                    }
                }
                else if(order=="post"){
                    int cur=dfsstack.top();
                    if(flag[cur]==0){
                        if(legal(left(cur))) dfsstack.push(left(cur));
                        flag[cur]++;
                    }
                    else if(flag[cur]==1){
                        if(legal(right(cur))) dfsstack.push(right(cur));
                        flag[cur]++;
                    }
                    else {
                    dfsstack.pop();
                    res.push_back(arr[cur]);
                    }
                }
            }
        }

        /* 前序遍历 */
    vector<int> preOrder() {
        vector<int> res;
        dfs(0, "pre", res);
        return res;
    }

    /* 中序遍历 */
    vector<int> inOrder() {
        vector<int> res;
        dfs(0, "in", res);
        return res;
    }

    /* 后序遍历 */
    vector<int> postOrder() {
        vector<int> res;
        dfs(0, "post", res);
        return res;
    }
    

};


int main() {
    // 创建一个二叉树数组表示
    // 树的结构:
    //      1
    //     / \
    //    2   3
    //   / \   \
    //  4   5   6
    vector<int> treeData = {1, 2, 3, 4, 5, INT32_MAX, 6};
    ArrayBinaryTree tree(treeData);
    
    // 测试层序遍历
    cout << "层序遍历: ";
    vector<int> levelResult = tree.levelOrder();
    for(int val : levelResult) {
        cout << val << " ";
    }
    cout << endl;
    
    // 测试前序遍历
    cout << "前序遍历: ";
    vector<int> preResult = tree.preOrder();
    for(int val : preResult) {
        cout << val << " ";
    }
    cout << endl;
    
    // 测试中序遍历
    cout << "中序遍历: ";
    vector<int> inResult = tree.inOrder();
    for(int val : inResult) {
        cout << val << " ";
    }
    cout << endl;
    
    // 测试后序遍历
    cout << "后序遍历: ";
    vector<int> postResult = tree.postOrder();
    for(int val : postResult) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
}