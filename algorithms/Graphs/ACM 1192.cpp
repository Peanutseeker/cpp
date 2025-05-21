//
// Created by howard_xu on 5/20/25.
//

#include<iostream>
using namespace std;
#include<bits/stdc++.h>
#include<climits>

int main() {
    int m,n;
    cin>>m>>n;
    //两个可能要用的转换器，写了lambda表达式
    //写pair时用了structure binding省去make_pair操作
    auto pair2int=[=](pair<int,int> a)->int {
        return (a.first)*m+a.second;
    };
    auto int2pair=[=](int k)->pair<int,int> {
        return {k/m,k%m};
    };
    //先存储颜色信息
    vector<vector<int>> grid(m,vector<int>(m,-1));
    for (int i=0;i<n;i++) {
        int x,y,c;
        cin>>x>>y>>c;
        grid[x-1][y-1]=c;
    }

    //靠颜色信息建图
    vector<vector<pair<int,int>>> graph;
    graph.resize(2*m*m);
    int moveX[4]={1,0,-1,0};
    int moveY[4]={0,1,0,-1};
    /*解释：第一个m2是所有红色节点，无色节点染成红色(0)
     *第二个m2是把无色节点染成黄色的，加上原来的黄色节点(1)
     */
    for (int x=0;x<m;x++) {
        for (int y=0;y<m;y++) {
            int index=pair2int({x,y});
            int curColor=grid[x][y];
            if (curColor==1) index+=m*m;
            for (int k=0;k<=3;k++) {
                int neighborX=x+moveX[k];
                int neighborY=y+moveY[k];
                if (neighborX<0||neighborX>=m) continue;
                if (neighborY<0||neighborY>=m) continue;

                int neighbor=pair2int({neighborX,neighborY});
                int neighborColor=grid[neighborX][neighborY];

                //为了还原要求，规定有色节点向无色节点建立边，分类讨论染色，两条边需要在原有基础上增加2的代价
                //由于我们的graph中设定的都是染了色的节点，因此无色节点向有色节点建边不需要2的代价

                if (neighborColor==1) neighbor+=m*m;
                if (curColor!=-1) {
                    //不是无色节点
                    if (neighborColor==-1) {
                        //邻居是无色节点，这时分类讨论建立边
                        graph[index].emplace_back(neighbor,(curColor==1)+2);
                        graph[index].emplace_back(neighbor+m*m,(curColor==0)+2);
                    }
                    else if (neighborColor==curColor) {
                        graph[index].emplace_back(neighbor,0);
                    }
                    else {
                        graph[index].emplace_back(neighbor,1);
                    }
                }
                else {
                    int indexR=index;
                    int indexY=index+m*m;
                    if (neighborColor==-1) continue;
                    graph[indexR].emplace_back(neighbor,neighborColor==1);
                    graph[indexY].emplace_back(neighbor,neighborColor==0);
                }

            }
        }
    }

    vector<vector<int>> costBucket;
    costBucket.resize(2*m*m+1,{});
    vector<int> dist(2*m*m,INT32_MAX);
    int start=grid[0][0]==0?0:m*m;
    costBucket[0].push_back(start);
    dist[start]=0;
    vector<bool> visited(2*m*m,false);
    //一边加步数，一边拓展
    bool reached=false;
    int final=m*m-1;
    for (int s=0;s<costBucket.size();s++) {
        for(int it=0;it<costBucket[s].size();it++) {
            int curNode=costBucket[s][it];
            if (curNode==final||curNode==final+m*m) {
                reached=true;//由于从小到大遍历桶，因此碰到其中一个就可以退出
                break;
            }
            //注意，只要取出过的节点就是已经确定最短路径的节点
            if (s>dist[curNode]) continue;//这里要写大于号，不然不会执行循环
            else {
                for (auto i:graph[curNode]) {
                    int node=i.first;int w=i.second;
                    if (dist[node]>w+s) {
                        costBucket[w+s].push_back(node);
                    }
                    dist[node]=min(w+s,dist[node]);
                }
            }
        }
        if (reached==true) break;//因为要跳两层，所以需要标记
    }
    if (reached==false) cout<<-1;
    else cout<<min(dist[final],dist[final+m*m]);


    return 0;
}