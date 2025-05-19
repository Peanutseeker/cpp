#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>

using namespace std;

typedef vector<vector<int>> matrix;

class GraphAdjMat {
private:
    vector<int> vertices;
    matrix adjMat;

public:
    GraphAdjMat(const vector<int>& points, const matrix& edges) {
        // Add all vertices first
        for (int val : points) {
            addVertex(val);
        }
        
        // Then add all edges by looking up vertex indices
        for (const vector<int>& edge : edges) {
            // Find indices of the vertices with these values
            int i = findVertexIndex(edge[0]);
            int j = findVertexIndex(edge[1]);
            if (i != -1 && j != -1) {
                addEdge(i, j);
            } else {
                cout << "Edge vertices not found: " << edge[0] << " - " << edge[1] << endl;
            }
        }
    }

    // Helper to find index of a vertex value
    int findVertexIndex(int val) {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i] == val) return i;
        }
        return -1;
    }

    int size() {
        return vertices.size();
    }

    void addVertex(int val) {
        int n = size();
        vertices.push_back(val);
        
        // Add a new row to the adjacency matrix
        adjMat.emplace_back(vector<int>(n + 1, 0));
        
        // Extend each existing row with a new column
        for (int i = 0; i < n; i++) {
            adjMat[i].push_back(0);
        }
    }

    void removeVertex(int index) {
        if (index >= size()) {
            throw out_of_range("Vertex doesn't exist");
        }
        // Remove the vertex from the vertex list
        vertices.erase(vertices.begin() + index);
        // Remove the corresponding row from the adjacency matrix
        adjMat.erase(adjMat.begin() + index);
        // Remove the corresponding column from each row
        for (vector<int>& row : adjMat) {
            row.erase(row.begin() + index);
        }
    }

    /* Add edge */
    void addEdge(int i, int j) {
        // Check for invalid indices
        if (i < 0 || j < 0 || i >= size() || j >= size() || i == j) {
            throw out_of_range("Vertex doesn't exist");
        }
        // For undirected graph, make symmetric entries
        adjMat[i][j] = 1;
        adjMat[j][i] = 1;
    }

    /* Remove edge */
    void removeEdge(int i, int j) {
        // Check for invalid indices
        if (i < 0 || j < 0 || i >= size() || j >= size() || i == j) {
            throw out_of_range("Vertex doesn't exist");
        }
        adjMat[i][j] = 0;
        adjMat[j][i] = 0;
    }

    // Corrected DFS implementation
    vector<int> DFS(int startIndex) {
        vector<int> result;
        vector<bool> visited(size(), false);
        DFSUtil(startIndex, result, visited);
        return result;
    }

    void DFSUtil(int index, vector<int>& result, vector<bool>& visited) {
        // Mark current node as visited first
        visited[index] = true;
        // Add to result
        result.push_back(vertices[index]);
        
        // Visit all adjacent vertices
        for (int j = 0; j < size(); j++) {
            if (adjMat[index][j] == 1 && !visited[j]) {
                DFSUtil(j, result, visited);
            }
        }
    }

    // Corrected BFS implementation
    vector<int> BFS(int startIndex) {
        vector<int> result;
        vector<bool> visited(size(), false);
        queue<int> q;
        
        // Mark the start vertex as visited and enqueue it
        visited[startIndex] = true;
        q.push(startIndex);
        result.push_back(vertices[startIndex]);
        
        while (!q.empty()) {
            // Dequeue a vertex
            int currentIndex = q.front();
            q.pop();
            
            // Get all adjacent vertices of the dequeued vertex
            for (int j = 0; j < size(); j++) {
                // If adjacent vertex hasn't been visited yet, mark it and enqueue it
                if (adjMat[currentIndex][j] == 1 && !visited[j]) {
                    visited[j] = true;
                    q.push(j);
                    result.push_back(vertices[j]);
                }
            }
        }
        
        return result;
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
    
    // Get vertex value at index
    int getVertex(int index) {
        if (index < 0 || index >= size()) {
            throw out_of_range("Invalid vertex index");
        }
        return vertices[index];
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