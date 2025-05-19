#include<iostream>
using namespace std;
#include<vector>
#include<queue>
#include <bits/stdc++.h>

int vercnt,edgecnt;
int dis[int(6E6+27)];
int head[int(6E6+27)];//对应节点出发第一条边的编号
int nxt[int(11E6+27)];//对应边的下一条边的编号
int to[int(11E6+27)];//对应边的终点
int curedge=0;
bool samedisedge[int(6E6+27)]={0};
int indegree[int(6E6+27)]={0};
int bfs[int(11E6+27)]={0};
int start=0;
int last=-1;

void push(int k) {
    ++last;
    bfs[last]=k;
}
void pop() {
    bfs[start]=0;
    start++;
}
int front() {
    return bfs[start];
}
bool empty() {
    return start-last==1;
}


//说明：这段代码来自AI，我不会写快速输入
inline int read() {
    int x=0;
    char ch=getchar();
    while (ch < '0' || ch > '9') ch=getchar();
    while (ch>='0'&&ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}

void add(int u,int v) {
    //设定：第一条边是1
    //curedge是新边对应编号
    curedge++;//现有边数量加1
    to[curedge]=v;
    nxt[curedge]=head[u];
    head[u]=curedge;
}


int main() {
    int vertexcnt,edgecnt;
    vertexcnt=read();
    edgecnt=read();
    for (int i=1;i<=edgecnt;i++) {
        int x=read();
        int y=read();
        add(x,y);
        add(y,x);
    }


    push(1);
    for (int i=1;i<=vertexcnt;i++) {
        dis[i]=INT_MAX;
    }
    dis[1]=0;
    while (!empty()) {
        int cur=front();
        pop();
        int edge=head[cur];
        while (edge!=0) {
            int neighbor=to[edge];
            if (dis[neighbor]==INT_MAX) {
                dis[neighbor]=dis[cur]+1;
                push(neighbor);
            }
            edge=nxt[edge];

        }
    }
    int undeleted=0;
    //通过BFS把点按照距离分层
    //这样边可以被划分成同层边和异层边
    //所有同层边都可以删掉，异层边只要能找到一个同层边+自己+另一条同样的异层边就可以删
    //进一步简化:不能被删掉的边，既没有同层边，而且只被一条异层边指着（入度为1）

    //第一步：查找同层边
    //用布尔数组标记节点有没有同层边

    for (int i=1;i<=vertexcnt;i++) {
        int edge=head[i];
        while (edge!=0) {
            int ori=i;
            int des=to[edge];
            if (dis[ori]==dis[des]) {
                samedisedge[ori]=true;
                samedisedge[des]=true;
            }
            edge=nxt[edge];
        }
    }
    //第二步：标记每个节点异层边入度
    //
    for (int i=1;i<=vertexcnt;i++) {
        int edge=head[i];
        while (edge!=0) {
            int ori=i;
            int des=to[edge];
            if (dis[ori]<dis[des]) {
                indegree[des]++;
            }
            edge=nxt[edge];
        }
    }
    for (int i=1;i<=vertexcnt;i++) {
        int edge=head[i];
        if (samedisedge[i]==false&&indegree[i]==1) undeleted++;
    }
    printf("%d",edgecnt-undeleted);
    return 0;
}