#include <iostream>
#include<vector>
#include<cstdint>
#include<list>
#include<map>
using namespace std;

int generation(int m,int k,const vector<int> &parent){
    int temp=k;
    int generations=0;
    while(temp!=m) {
        temp=parent[temp];
        generations++;
    }
    return generations; 
}

void LCA(int m, int k, const vector<int>& parent, vector<int>& generations){
    if(m==k) {
        generations[0]=generations[1]=0;
    }
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
    while(k_it>=0&&m_it>=0&&k_parents[k_it]==m_parents[m_it]){
        k_it--;m_it--;
    }
    generations[0]=k_it+1;
    generations[1]=m_it+1;
}

//说明：GPT指示我用数组实现这个二叉树更方便
//用两个数组，一个左分支节点，一个右分支节点
int main(){
    int n;
    cin>>n;
    
    vector<int> parent(n+1,0);
    vector<int> depths(n+1,0);
    depths[1]=1;
    vector<int> depthhash(n+1,0);
    depthhash[1]=1;
    int breadth=1;int depth=1;
    //数组构造树的办法：存三个数组，一个left，一个right，一个parent
    parent[1]=527;parent[0]=527;
    int parentnode,childnode;
    for(int i=0;i<n-1;i++){
        cin>>parentnode>>childnode;
        parent[childnode]=parentnode;
        depths[childnode]=depths[parentnode]+1;
        if(depths[childnode]>depth) depth=depths[childnode];
        depthhash[depths[childnode]]++;
        if(depthhash[depths[childnode]]>breadth) breadth=depthhash[depths[childnode]];
    }

    int m,k;
    cin>>m>>k;
    vector<int> generations={-1,-1};
    LCA(m,k,parent,generations);
    cout<<depth<<endl<<breadth<<endl<<generations[0]+generations[1]*2;

    return 0;
}