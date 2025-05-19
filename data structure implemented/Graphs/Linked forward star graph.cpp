#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // 需要包含 sort
#include <limits>
#include <numeric> // 需要包含 iota

// --- 并查集 (DSU) 函数 ---
// 查找元素 i 的根节点（带路径压缩）
int find(std::vector<int>& DSU, int i) {
    if (DSU[i] == i)
        return i;
    // 路径压缩
    return DSU[i] = find(DSU, DSU[i]);
}

// 合并包含 x 和 y 的集合
void unite(std::vector<int>& DSU, int x, int y) {
    int rootx = find(DSU, x);
    int rooty = find(DSU, y);
    // 如果根节点不同，则合并
    if (rootx != rooty) {
        DSU[rootx] = rooty;
    }
}
// --- 并查集 (DSU) 函数结束 ---


class LinkedForwardStarGraph {
private:
    // 顶点数量
    int numVertices;

    // 边结构 (使用 int 作为类型)
    struct Edge {
        int to;         // 目标顶点
        int weight;     // 边权重
        int next;       // 从同一起点出发的下一条边的索引

        // 构造函数
        Edge(int t, int w, int n) : to(t), weight(w), next(n) {}
        // 默认构造函数
        Edge() : to(-1), weight(0), next(-1) {}
    };

    // 存储所有边的向量
    std::vector<Edge> edges;

    // 存储每个顶点的第一条出边的索引的向量
    // head[i] 存储顶点 i 的第一条出边在 edges 向量中的索引，若无则为 -1
    std::vector<int> head;

    // 当前边的数量
    int edgeCount;

    // 初始化图
    // 参数：顶点数量, 预期的最大边数 (用于 reserve)
    void init(int vertices, int maxEdgesHint) {
        this->numVertices = vertices;
        // 初始化 head 数组，所有顶点最初没有出边
        head.assign(vertices, -1);
        // 清空 edges 向量
        edges.clear();
        // 预留空间可以提高添加边时的效率
        edges.reserve(maxEdgesHint);
        edgeCount = 0;
    }

public:
    // 用于 Kruskal 算法的边结构 (使用 int 作为类型)
    struct KruskalEdge {
        int from;
        int to;
        int weight;

        // 构造函数
        KruskalEdge(int f, int t, int w) : from(f), to(t), weight(w) {}

        // 用于 std::sort 的比较运算符 <
        bool operator<(const KruskalEdge& other) const {
            return weight < other.weight;
        }
    };

    // 构造函数
    // 参数：顶点数量, 预期的最大边数
    LinkedForwardStarGraph(int vertices, int maxEdgesHint) {
        init(vertices, maxEdgesHint);
    }

    // 添加一条从 from 到 to 的有向边，权重为 weight
    void addEdge(int from, int to, int weight) {
        // 创建新边，它的 next 指向当前顶点 from 的第一条边 (head[from])
        // 将新边添加到 edges 向量的末尾
        edges.emplace_back(to, weight, head[from]); // 使用 emplace_back 更高效
        // 更新顶点 from 的 head 指针，指向新添加的边 (其索引是当前 edges 的大小减 1)
        head[from] = edges.size() - 1;
        // 边计数加一
        edgeCount++;
    }

    // 添加一条 u 和 v 之间的无向边，权重为 weight
    void addUndirectedEdge(int u, int v, int weight) {
        addEdge(u, v, weight);
        addEdge(v, u, weight);
    }

    // 获取顶点数量
    int getVertexCount() const {
        return numVertices;
    }

    // 获取（有向）边的数量
    int getEdgeCount() const {
        return edgeCount;
    }

    // Kruskal 最小生成树算法 (仅适用于无向图)
    // 返回构成最小生成树的边的列表
    std::vector<KruskalEdge> minimumSpanningTree() {
        std::vector<KruskalEdge> mstEdges; // 存储最小生成树的边
        std::vector<KruskalEdge> allEdges; // 存储图中所有的唯一无向边

        // 1. 收集所有唯一的无向边
        allEdges.reserve(edgeCount / 2); // 预估大小
        for (int u = 0; u < numVertices; ++u) {
            int current_edge_index = head[u];
            while (current_edge_index != -1) {
                const Edge& edge = edges[current_edge_index];
                int v = edge.to;
                int w = edge.weight;
                // 只在 u < v 时添加，避免重复添加无向边
                if (u < v) {
                    allEdges.emplace_back(u, v, w);
                }
                current_edge_index = edge.next;
            }
        }

        // 2. 按权重对所有边进行排序
        std::sort(allEdges.begin(), allEdges.end());

        // 3. 初始化并查集 (DSU)
        std::vector<int> DSU(numVertices);
        std::iota(DSU.begin(), DSU.end(), 0); // DSU[i] = i

        // 4. 遍历排序后的边，构建最小生成树
        int edgesInMST = 0;
        for (const auto& edge : allEdges) {
            // 如果边的两个顶点不在同一个集合中 (不成环)
            if (find(DSU, edge.from) != find(DSU, edge.to)) {
                mstEdges.push_back(edge); // 加入 MST
                unite(DSU, edge.from, edge.to); // 合并集合
                edgesInMST++;
                // 如果 MST 已包含 V-1 条边，则完成
                if (edgesInMST == numVertices - 1) {
                    break;
                }
            }
        }

        // 5. 返回 MST 边集 (如果图不连通，边数可能少于 V-1)
        return mstEdges;
    }

    // 打印图的邻接表表示
    void printGraph() const {
        std::cout << "Graph Representation (Adjacency List using Linked Forward Star):" << std::endl;
        for (int i = 0; i < numVertices; ++i) {
            std::cout << i << ": ";
            int current_edge_index = head[i];
            if (current_edge_index == -1) {
                std::cout << " (No outgoing edges)";
            }
            while (current_edge_index != -1) {
                const Edge& edge = edges[current_edge_index];
                std::cout << "-> (" << edge.to << ", " << edge.weight << ") ";
                current_edge_index = edge.next;
            }
            std::cout << std::endl;
        }
        std::cout << "-----------------------------------------" << std::endl;
    }
};

// --- 主函数 ---
int main() {
    // 创建一个有 5 个顶点（编号 0 到 4）的图
    int num_vertices = 5;
    // 预期添加 7 条无向边，即 14 条有向边。给 maxEdgesHint 一个估计值。
    int max_edges_hint = 14;
    LinkedForwardStarGraph graph(num_vertices, max_edges_hint);

    std::cout << "Adding undirected edges..." << std::endl;
    // 添加无向边 (u, v, weight)
    graph.addUndirectedEdge(0, 1, 2);
    graph.addUndirectedEdge(0, 3, 6);
    graph.addUndirectedEdge(1, 2, 3);
    graph.addUndirectedEdge(1, 3, 8);
    graph.addUndirectedEdge(1, 4, 5);
    graph.addUndirectedEdge(2, 4, 7);
    graph.addUndirectedEdge(3, 4, 9);

    // 打印图的结构
    graph.printGraph();

    std::cout << "Calculating Minimum Spanning Tree (MST) using Kruskal's algorithm..." << std::endl;
    // 计算最小生成树
    std::vector<LinkedForwardStarGraph::KruskalEdge> mst = graph.minimumSpanningTree();

    // 打印最小生成树的边和总权重
    if (mst.empty() && graph.getVertexCount() > 1 && graph.getEdgeCount() > 0) {
         std::cout << "MST could not be formed (Graph might be disconnected or no edges)." << std::endl;
    } else if (mst.size() < graph.getVertexCount() - 1 && graph.getVertexCount() > 1) {
         // 这种情况发生在图不连通时
         std::cout << "MST found (Graph is disconnected):" << std::endl;
         int totalWeight = 0;
         for (const auto& edge : mst) {
              std::cout << "Edge: (" << edge.from << " - " << edge.to << "), Weight: " << edge.weight << std::endl;
              totalWeight += edge.weight;
         }
         std::cout << "Total weight of the MST components found: " << totalWeight << std::endl;
    }
     else if (!mst.empty()){
        std::cout << "Minimum Spanning Tree Edges:" << std::endl;
        int totalWeight = 0;
        for (const auto& edge : mst) {
            std::cout << "Edge: (" << edge.from << " - " << edge.to << "), Weight: " << edge.weight << std::endl;
            totalWeight += edge.weight;
        }
        std::cout << "Total weight of the MST: " << totalWeight << std::endl;
    } else {
         // 这种情况发生在图没有边时
         std::cout << "No edges in the graph to form an MST." << std::endl;
    }

    return 0;
}