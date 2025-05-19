#include <iostream>
#include<vector>
using namespace std;

int depth(int x,const vector<int>& left,const vector<int>& right){
    if(x==0) return 0;
    return max(depth(left[x-1],left,right)+1,depth(right[x-1],left,right)+1);
}

//说明：GPT指示我用数组实现这个二叉树更方便
//用两个数组，一个左分支节点，一个右分支节点
int main(){
    int n;
    cin>>n;
    vector<int> lefttree={};
    vector<int> righttree={};
    int left,right;
    for(int i=0;i<n;i++){
        cin>>left>>right;
        lefttree.push_back(left);
        righttree.push_back(right);
    }
    int a=1;
    cout<<depth(a,lefttree,righttree);

}