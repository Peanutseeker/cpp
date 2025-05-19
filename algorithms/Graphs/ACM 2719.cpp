#include <iostream>
using namespace std;
#include <bits/stdc++.h>



int main() {

    int ver,edge;
    cin>>ver>>edge;
    vector<int> nxt(2*edge+2,-1);
    vector<int> to(2*edge+2,-1);
    vector<int> head(ver+1,0);
    int current=1;
    auto addEdge = [&](int u, int v) {
        // 添加从 u 到 v 的边
        to[current] = v;          // 当前边的终点是 v
        nxt[current] = head[u];   // 当前边的下一条边指向原来u的第一条边
        head[u] = current;        // 更新u的第一条边为当前这条边
        current++;                // 移动到下一个可用的边槽
    };

    auto BFS=[&](int start)->vector<int> {
        vector<int> dist(ver+1,INT_MAX);
        dist[start]=0;
        queue<int> q;
        q.push(start);
        while (!q.empty()) {
            int cur=q.front();
            q.pop();
            int edge_it=head[cur];
            while (edge_it!=-1) {
                int neigh=to[edge_it];
                if (dist[neigh]==INT_MAX) {
                    dist[neigh]=dist[cur]+1;
                    q.push(neigh);
                }
                edge_it=nxt[edge_it];
            }
        }
        return dist;
    };


    int start,end1,end2;
    cin>>start>>end1>>end2;

    for (int i=1;i<=edge;i++) {
        int u,v;
        cin>>u>>v;
        addEdge(u,v);
        addEdge(v,u);
    }

    vector<int> startDist=BFS(start);
    vector<int> end1Dist=BFS(end1);
    vector<int> end2Dist=BFS(end2);
    int res=-1;
    int disA=startDist[end1];
    int disB=startDist[end2];
    //重点：只要AB最短距离+BC最短距离=AC最短距离，B就在AC的最短路径上
    for (int i=1;i<=ver;i++) {
        if (disA==startDist[i]+end1Dist[i]&&disB==startDist[i]+end2Dist[i]) {
            res=max(res,startDist[i]);
        }
    }
    cout<<res;
    return 0;


}