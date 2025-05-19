#include <iostream>
#include<vector>
#include<cstdint>
#include<list>
using namespace std;


int LCA(int m, int k, const vector<int>& parent){
    if(m==k) return k;
    vector<int> m_parents={};
    vector<int> k_parents={};
    int temp=m;
    while(temp!=527) {
        m_parents.push_back(temp);
        temp=parent[temp];
    }
    temp=k;
    while(temp!=527){
        k_parents.push_back(temp);
        temp=parent[temp];
    }
    int m_it=m_parents.size()-1;
    int k_it=k_parents.size()-1;
    while(k_parents[k_it]==m_parents[m_it]){
        k_it--;m_it--;
    }
    return k_parents[++k_it];
}

//说明：GPT指示我用数组实现这个二叉树更方便
//用两个数组，一个左分支节点，一个右分支节点
int main(){
    int n;
    cin>>n;
    int m,k;
    cin>>m>>k;
    
    vector<int> parent(n+1,0);
    //数组构造树的办法：存三个数组，一个left，一个right，一个parent
    parent[1]=527;parent[0]=527;
    int left,right;
    for(int i=0;i<n;i++){
        cin>>left>>right;
        if(left>0) parent[left]=i+1;
        if(right>0) parent[right]=i+1;
    }
    
    cout<<LCA(m,k,parent);
    return 0;
}