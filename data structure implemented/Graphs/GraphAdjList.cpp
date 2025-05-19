#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <limits>
#include <algorithm>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#endif

template <typename VertexType, typename WeightType = int>
class Graph
{
public:
    // 构造函数
    Graph(bool isDirected = false)
    {
        adjacencyList = {};
        numEdges = 0;
        directed = isDirected;
    }

    // 公共接口
    void addVertex(const VertexType &vertex)
    {
        // 检查out of bounds！增加鲁棒性
        if (!hasVertex(vertex))
            adjacencyList[vertex] = {};
    }
    void removeVertex(const VertexType &vertex)
    {
        if (!hasVertex(vertex))
        {
            return;
        }

        // 删除所有指向该顶点的边
        for (auto &pair : adjacencyList)
        {
            auto &neighbors = pair.second;
            auto it = findEdge(neighbors, vertex);
            if (it != neighbors.end())
            {
                neighbors.erase(it);
                numEdges--;
            }
        }

        // 删除该顶点的所有出边
        numEdges -= adjacencyList[vertex].size();

        // 删除顶点
        adjacencyList.erase(vertex);
    }
    void addEdge(const VertexType &from, 
        const VertexType &to, 
        const WeightType &weight = WeightType())
    {
        // 首先确保这条边的两个顶点都在图里面
        addVertex(from);
        addVertex(to);

        // 接着检查是否有重复边
        auto &neighbors = adjacencyList[from];
        auto it = findEdge(neighbors, to);
        if (it != neighbors.end())
        {
            it->weight = weight;
            return;
        }

        Edge new_Edge(to, weight);
        adjacencyList[from].push_back(new_Edge);
        numEdges++;

        // 如果是无向图，添加反向边
        if (!directed)
        {
            auto itReverse = findEdge(adjacencyList[to], from);
            if (itReverse == adjacencyList[to].end())
            {
                adjacencyList[to].push_back(Edge(from, weight));
                // 不增加numEdges，因为在无向图中这是同一条边
            }
        }
    }
    void removeEdge(const VertexType &from, const VertexType &to)
    {
        if (!hasEdge(from, to))
            return;
        auto &neighbors = adjacencyList.at(from);
        auto it = findEdge(neighbors, to);
        if (it != neighbors.end())
        {
            neighbors.erase(it);
            numEdges--;
        }
        if (!directed)
        {
            auto &reverse = adjacencyList.at(to);
            reverse.erase(findEdge(reverse, from));
        }
    }
    bool hasVertex(const VertexType &vertex) const
    {
        return adjacencyList.find(vertex) != adjacencyList.end();
    }
    bool hasEdge(const VertexType &from, const VertexType &to) const
    {
        // 先判断有没有顶点
        if (!hasVertex(from) || !hasVertex(to))
            return false;

        // 接着判断边存在性，注意要用at函数，而不是方括号
        // 因为方括号在map里键值对不存在时会插入新的键值对，不能用来判断元素存在性
        // at函数在元素不存在时会报错

        auto neighbors = adjacencyList.at(from);
        auto it = findEdge(neighbors, to);
        return it != neighbors.end();
    }
    WeightType getEdgeWeight(const VertexType &from, 
        const VertexType &to) const
    {
        // 出现异常要报错
        if (!hasVertex(from) || !hasVertex(to))
        {
            throw std::runtime_error("Vertex not found");
        }

        const auto &neighbors = adjacencyList.at(from);
        auto it = findEdge(neighbors, to);
        if (it == neighbors.end())
        {
            throw std::runtime_error("Edge not found");
        }

        return it->weight;
    }
    std::vector<VertexType> getVertices() const
    {
        std::vector<VertexType> vertices = {};
        for (const auto &pair : adjacencyList)
        {
            vertices.push_back(pair.first);
        }
        return vertices;
    }
    std::vector<VertexType> getNeighbors(const VertexType &vertex) const
    {
        if (!hasVertex(vertex))
            return std::vector<VertexType>();

        std::vector<VertexType> neighbors;
        const auto &edgeList = adjacencyList.at(vertex);
        neighbors.reserve(edgeList.size());
        for (const auto &i : adjacencyList.at(vertex))
        {
            neighbors.push_back(i.destination);
        }
        return neighbors;
    }
    size_t vertexCount() const
    {
        return adjacencyList.size();
    }
    size_t edgeCount() const
    {
        return numEdges;
    }

    // 图算法接口
    void depthFirstTraversal(const VertexType &startVertex,
         void (*visit)(const VertexType &))
    {
        if (!hasVertex(startVertex))
            return;

        std::unordered_set<VertexType> visited; // 使用哈希表
        std::stack<VertexType> dfs_stack;
        dfs_stack.push(startVertex);
        while (!dfs_stack.empty())
        {
            auto current = dfs_stack.top();
            dfs_stack.pop();
            if (visited.find(current) == visited.end())
            {
                visit(current);
                visited.insert(current);
            }

            auto neighbors = getNeighbors(current);
            for (auto it = neighbors.rbegin(); it != neighbors.rend(); it++)
            {
                if (visited.find(*it) == visited.end())
                {
                    dfs_stack.push(*it);
                }
            }
        }
    }
    void breadthFirstTraversal(const VertexType &startVertex, 
        void (*visit)(const VertexType &))
    {
        if (!hasVertex(startVertex))
            return;

        std::unordered_set<VertexType> visited;
        std::queue<VertexType> bfs_queue;
        bfs_queue.push(startVertex);
        while (!bfs_queue.empty())
        {
            auto current = bfs_queue.front();
            bfs_queue.pop();
            if (visited.find(current) == visited.end())
            {
                visit(current);
                visited.insert(current);
            }

            auto neighbor = getNeighbors(current);
            for (auto it = neighbor.begin(); it != neighbor.end(); it++)
            {
                if (visited.find(*(it)) == visited.end())
                {
                    bfs_queue.push(*it);
                }
            }
        }
    }
    std::vector<VertexType> shortestPath(
        const VertexType &source, const VertexType &destination)
    {
        auto predecessors=dijk_path(source,destination).second;
        auto it=destination;
        std::vector<VertexType> path={destination};
        while (it!=source) {
            if (predecessors.find(it)==predecessors.end()) return {};
            it=predecessors[it];
            path.push_back(it);
        }
        std::reverse(path.begin(),path.end());
        return path;
    }
    std::unordered_map<VertexType, WeightType> dijkstra(const VertexType &source)
    {
        std::unordered_map<VertexType, WeightType> res = {};
        std::unordered_set<VertexType> visited = {};
        using DistVertexPair = std::pair<VertexType, WeightType>;
        struct Comparedist
        // 由于priority queue默认为maxheap，即默认用小于号构造heap
        // 因此这里定义比较器的时候要用大于号
        {
            bool operator()(const DistVertexPair &a, const DistVertexPair &b)
            {
                return a.second > b.second;
            }
        };

        std::priority_queue<DistVertexPair, 
        std::vector<DistVertexPair>, Comparedist> pq = {};
        for (const auto &i : adjacencyList)
        {
            res[i.first] = std::numeric_limits<WeightType>::max();
        }
        res[source] = 0;
        pq.push({source, 0});
        while (!pq.empty())
        {
            VertexType curVertex = pq.top().first;
            WeightType curDist = pq.top().second;
            pq.pop();
            if (visited.find(curVertex) == visited.end())
            {
                visited.insert(curVertex);
                VertexType neighbor;
                for (auto i : adjacencyList[curVertex])
                {
                    neighbor = i.destination;
                    res[neighbor] = std::min(res[neighbor], curDist + i.weight);
                    pq.push({neighbor, i.weight + curDist});
                }
            }
        }
        return res;
    }

    std::pair<std::unordered_map<VertexType, WeightType>, 
    std::unordered_map<VertexType, VertexType>> 
    dijk_path(const VertexType &source, 
        const VertexType &destination)
    {
        std::unordered_map<VertexType, WeightType> res = {};
        std::unordered_set<VertexType> visited = {};
        std::unordered_map<VertexType, VertexType> predecessors = {};
        using DistVertexPair = std::pair<VertexType, WeightType>;
        struct Comparedist
        // 由于priority queue默认为maxheap，即默认用小于号构造heap
        // 因此这里定义比较器的时候要用大于号
        {
            bool operator()(const DistVertexPair &a, const DistVertexPair &b)
            {
                return a.second > b.second;
            }
        };

        std::priority_queue<DistVertexPair,
        std::vector<DistVertexPair>, Comparedist> pq = {};
        for (const auto &i : adjacencyList)
        {
            res[i.first] = std::numeric_limits<WeightType>::max();
        }
        res[source] = 0;
        pq.push({source, 0});
        while (!pq.empty())
        {
            VertexType curVertex = pq.top().first;
            WeightType newDist = pq.top().second;
            pq.pop();
            if (visited.find(curVertex)!=visited.end()) continue;
            if (curVertex==destination) break;
            visited.insert(curVertex);
            VertexType neighbor;
            for (auto i : adjacencyList[curVertex])
                {
                neighbor = i.destination;
                WeightType curDist=res[neighbor];
                if (curDist>newDist + i.weight) {
                    predecessors[neighbor]=curVertex;
                    res[neighbor]=newDist+i.weight;
                    pq.push({neighbor,newDist+i.weight});
                }
            }
        }
        return {res,predecessors};
    }

private:
    // 边的定义
    struct Edge
    {
        VertexType destination;
        WeightType weight;

        Edge(const VertexType &dest, const WeightType &w = WeightType())
            : destination(dest), weight(w) {}

        // 用于查找特定目标顶点的边
        bool operator==(const VertexType &vertex) const
        {
            return destination == vertex;
        }
    };

    // 存储结构：顶点到邻接表的映射
    std::unordered_map<VertexType, std::list<Edge>> adjacencyList;

    // 图的属性
    bool directed;
    size_t numEdges;

    // 辅助函数
    typename std::list<Edge>::iterator findEdge(std::list<Edge> &edges, const VertexType &destination)
    {
        return std::find(edges.begin(), edges.end(), destination);
        // 善用库函数，不要造轮子！
    }
    typename std::list<Edge>::const_iterator findEdge(const std::list<Edge> &edges, const VertexType &destination) const
    {
        return std::find(edges.begin(), edges.end(), destination);
    }
};

#include <string>
#include <iomanip>
#include <functional>

// 包含上面的Graph类定义

void printVertex(const std::string &vertex)
{
    std::cout << vertex << " ";
}

int main()
{
    #ifdef _WIN32
    // Set console output code page to UTF-8 on Windows
    SetConsoleOutputCP(CP_UTF8);
    // Optional: Set console input code page to UTF-8 as well
    // SetConsoleCP(CP_UTF8);
    #endif
    // 创建无向图
    std::cout << "===== 测试无向图 =====" << std::endl;
    Graph<std::string, double> undirectedGraph(false);

    // 添加顶点
    undirectedGraph.addVertex("A");
    undirectedGraph.addVertex("B");
    undirectedGraph.addVertex("C");
    undirectedGraph.addVertex("D");
    undirectedGraph.addVertex("E");

    // 添加边
    undirectedGraph.addEdge("A", "B", 1.5);
    undirectedGraph.addEdge("A", "C", 2.0);
    undirectedGraph.addEdge("B", "D", 3.5);
    undirectedGraph.addEdge("C", "D", 1.0);
    undirectedGraph.addEdge("D", "E", 2.5);

    // 打印图的基本信息
    std::cout << "顶点数: " << undirectedGraph.vertexCount() << std::endl;
    std::cout << "边数: " << undirectedGraph.edgeCount() << std::endl;

    // 打印所有顶点
    std::cout << "所有顶点: ";
    std::vector<std::string> vertices = undirectedGraph.getVertices();
    for (const auto &v : vertices)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    // 测试邻居获取
    std::cout << "A的邻居: ";
    std::vector<std::string> neighbors = undirectedGraph.getNeighbors("A");
    for (const auto &n : neighbors)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // 测试边权重
    std::cout << "边(A,B)的权重: " << undirectedGraph.getEdgeWeight("A", "B") << std::endl;

    // 测试深度优先遍历
    std::cout << "DFS遍历(从A开始): ";
    undirectedGraph.depthFirstTraversal("A", printVertex);
    std::cout << std::endl;

    // 测试广度优先遍历
    std::cout << "BFS遍历(从A开始): ";
    undirectedGraph.breadthFirstTraversal("A", printVertex);
    std::cout << std::endl;

    // 测试最短路径
    std::cout << "从A到E的最短路径: ";
    std::vector<std::string> path = undirectedGraph.shortestPath("A", "E");
    for (const auto &v : path)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    // 测试Dijkstra算法
    std::cout << "从A到所有顶点的最短距离:" << std::endl;
    auto distances = undirectedGraph.dijkstra("A");
    for (const auto &pair : distances)
    {
        std::cout << "A到" << pair.first << ": ";
        if (pair.second == std::numeric_limits<double>::max())
        {
            std::cout << "不可达";
        }
        else
        {
            std::cout << pair.second;
        }
        std::cout << std::endl;
    }

    // 测试删除边和顶点
    std::cout << "\n===== 测试删除操作 =====" << std::endl;
    std::cout << "删除边(A,C)后:" << std::endl;
    undirectedGraph.removeEdge("A", "C");
    std::cout << "边数: " << undirectedGraph.edgeCount() << std::endl;
    std::cout << "A的邻居: ";
    neighbors = undirectedGraph.getNeighbors("A");
    for (const auto &n : neighbors)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    std::cout << "删除顶点C后:" << std::endl;
    undirectedGraph.removeVertex("C");
    std::cout << "顶点数: " << undirectedGraph.vertexCount() << std::endl;
    std::cout << "边数: " << undirectedGraph.edgeCount() << std::endl;
    std::cout << "所有顶点: ";
    vertices = undirectedGraph.getVertices();
    for (const auto &v : vertices)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    // 创建有向图
    std::cout << "\n===== 测试有向图 =====" << std::endl;
    Graph<char, int> directedGraph(true);

    // 添加顶点
    directedGraph.addVertex('A');
    directedGraph.addVertex('B');
    directedGraph.addVertex('C');
    directedGraph.addVertex('D');

    // 添加边
    directedGraph.addEdge('A', 'B', 5);
    directedGraph.addEdge('A', 'C', 3);
    directedGraph.addEdge('B', 'C', 2);
    directedGraph.addEdge('C', 'D', 4);
    directedGraph.addEdge('D', 'A', 8);

    // 打印图的基本信息
    std::cout << "顶点数: " << directedGraph.vertexCount() << std::endl;
    std::cout << "边数: " << directedGraph.edgeCount() << std::endl;

    // 测试有向图的邻居获取
    std::cout << "A的邻居: ";
    auto charNeighbors = directedGraph.getNeighbors('A');
    for (const auto &n : charNeighbors)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // 测试有向图中的Dijkstra算法
    std::cout << "从A到所有顶点的最短距离:" << std::endl;
    auto charDistances = directedGraph.dijkstra('A');
    for (const auto &pair : charDistances)
    {
        std::cout << "A到" << pair.first << ": ";
        if (pair.second == std::numeric_limits<int>::max())
        {
            std::cout << "不可达";
        }
        else
        {
            std::cout << pair.second;
        }
        std::cout << std::endl;
    }

    return 0;
}