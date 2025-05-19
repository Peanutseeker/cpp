#include <iostream>
using namespace std;
#include <vector>
#include <queue>

template<typename weighttype=int>
struct PrimEdge {
    int from;
    int to;
    weighttype weight;
};

template<typename weighttype=int>
typedef vector<vector<weighttype>> Graph;
void Prim(const Graph& graph,int k) {
    int n=graph.size();
    vector<int> dist={};
    dist.reserve(n);
    for (int i=0;i<n;i++) {
        dist[i]=INT_MAX;
    }

}
