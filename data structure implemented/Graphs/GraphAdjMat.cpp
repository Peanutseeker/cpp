#include <iostream>
using namespace std;
#include<vector>
typedef vector<vector<int>> matrix;
#include <queue>

class GraphAdjMat{
    private:
    vector<int> vertices;
    matrix adjMat;
    public:
    GraphAdjMat(const vector<int>& point, matrix& edges ){
        //说明：边的形式是节点数对
        //这里使用后面写到的添加函数来构造，节省代码
        for(int val:point){
            addVertex(val);
        }
        for(const vector<int> & edge: edges){
            int i=findVertexIndex(edge[0]);
            int j=findVertexIndex(edge[1]);
            addEdge(i,j);
        }
    }
    int size(){
        return vertices.size();
    }
    int findVertexIndex(int val) {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i] == val) return i;
        }
        return -1;
    }
    void addVertex(int val){
        int n=size();
        vertices.push_back(val);
        adjMat.emplace_back(vector<int> (n,0));
        //emplace_back省掉了拷贝复制品的过程，直接内部构造，效率更高且适合大对象使用
        for (vector<int> &row : adjMat) {
            row.push_back(0);
        }
    }
    void removeVertex(int index) {
        if (index >= size()) {
            throw out_of_range("顶点不存在");
        }
        // 在顶点列表中移除索引 index 的顶点
        vertices.erase(vertices.begin() + index);
        // 在邻接矩阵中删除索引 index 的行
        adjMat.erase(adjMat.begin() + index);
        // 在邻接矩阵中删除索引 index 的列
        for (vector<int> &row : adjMat) {
            row.erase(row.begin() + index);
        }
    }
    /* 添加边 */
    // 参数 i, j 对应 vertices 元素索引
    void addEdge(int i, int j) {
        // 索引越界与相等处理
        if (i < 0 || j < 0 || i >= size() || j >= size() || i == j) {
            throw out_of_range("顶点不存在");
        }
        // 在无向图中，邻接矩阵关于主对角线对称，即满足 (i, j) == (j, i)
        adjMat[i][j] = 1;
        adjMat[j][i] = 1;
    }

    /* 删除边 */
    // 参数 i, j 对应 vertices 元素索引
    void removeEdge(int i, int j) {
        // 索引越界与相等处理
        if (i < 0 || j < 0 || i >= size() || j >= size() || i == j) {
            throw out_of_range("顶点不存在");
        }
        adjMat[i][j] = 0;
        adjMat[j][i] = 0;
    }
    vector<int> DFS(int index){
        vector<bool> visited(size(),false);
        vector<int> res={};
        DFShelper(index,res,visited);
        return res;
    }
    void DFShelper(int index,vector<int> &res,vector<bool>& visited){
        visited[index]=true;
        res.push_back(vertices[index]);
        for(int j=0;j<size();j++){
            if (adjMat[index][j]==1&&!visited[j]){
                DFShelper(j,res,visited);
            }
        }
    }
    vector<int> BFS(int index ){
        vector<int> res={};
        int n=vertices.size();
        vector<bool> visited(n,false);
        queue<int> BFSqueue;
        BFSqueue.push(index);
        visited[index]=true;
        while(!BFSqueue.empty()){
            int times=BFSqueue.size();
            int cur_index;
            for(int j=0;j<times;j++){
                cur_index=BFSqueue.front();
                BFSqueue.pop();
                visited[cur_index]=true;
                res.push_back(vertices[cur_index]);
                for(int m=0;m<n;m++){
                    if(adjMat[cur_index][m]==1&&!visited[m]){
                        visited[m]=true;
                        BFSqueue.push(m);
                    }
                }
            }
        }
        return res;
    }


    // Print the adjacency matrix
    void printAdjMatrix() {
        cout << "Adjacency Matrix:" << endl;
        cout << "    ";
        for (int val : vertices) {
            cout << val << " ";
        }
        cout << endl;
        
        for (int i = 0; i < size(); i++) {
            cout << vertices[i] << " | ";
            for (int j = 0; j < size(); j++) {
                cout << adjMat[i][j] << " ";
            }
            cout << endl;
        }
    }
};


int main() {
    // Create test vertices and edges
    vector<int> vertices = {1, 2, 3, 4, 5};
    matrix edges = {{1, 2}, {1, 3}, {2, 4}, {3, 4}, {4, 5}};
    
    // Create the graph
    GraphAdjMat graph(vertices, edges);
    
    // Print the adjacency matrix
    cout << "Graph with " << graph.size() << " vertices created." << endl;
    graph.printAdjMatrix();
    
    // Test DFS starting from vertex 0 (value 1)
    cout << "\nDFS traversal starting from vertex with value 1:" << endl;
    vector<int> dfsResult = graph.DFS(0);
    for (int val : dfsResult) {
        cout << val << " ";
    }
    cout << endl;
    
    // Test BFS starting from vertex 0 (value 1)
    cout << "\nBFS traversal starting from vertex with value 1:" << endl;
    vector<int> bfsResult = graph.BFS(0);
    for (int val : bfsResult) {
        cout << val << " ";
    }
    cout << endl;
    
    // Test vertex removal
    cout << "\nRemoving vertex with value 3 (index 2)..." << endl;
    graph.removeVertex(2);
    cout << "Graph after removal:" << endl;
    graph.printAdjMatrix();
    
    // Test adding a new vertex and edge
    cout << "\nAdding vertex with value 6..." << endl;
    graph.addVertex(6);
    cout << "Adding edge between vertex 4 (index 2) and 6 (index 4)..." << endl;
    graph.addEdge(2, 4);
    cout << "Updated graph:" << endl;
    graph.printAdjMatrix();
    
    // Test traversals after modifications
    cout << "\nDFS traversal after modifications, starting from vertex with value 1:" << endl;
    dfsResult = graph.DFS(0);
    for (int val : dfsResult) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "\nBFS traversal after modifications, starting from vertex with value 1:" << endl;
    bfsResult = graph.BFS(0);
    for (int val : bfsResult) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
}