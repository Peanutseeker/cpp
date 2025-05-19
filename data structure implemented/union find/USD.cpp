#include <iostream>
#include<vector>
#include <numeric>
using namespace  std;

class DSU {
private:
    vector<int> parents={};
    vector<int> subsetsize={};
public:
    DSU(int n) {
        parents.resize(n);
        //由于初始状态下每个子节点独立，因此初始每个子节点都是根节点
        //这样parent[i]初始值都是i
        iota(parents.begin(),parents.end(),0);
        subsetsize.assign(n,1);

    }
    //带路径压缩的find函数，查找时把路径上的点的parent也设成根节点
    int find(int i) {
        //找到根节点就停止查找，根节点的标志是parent[i]=i
        if (parents[i]==i) return i;
        return parents[i]=find(parents[i]);


    }

    void unite(int x, int y) {
        int rootx=find(x);
        int rooty=find(y);
        if (rootx==rooty) return;
        if (subsetsize[rootx]<subsetsize[rooty]) {
            parents[rootx]=rooty;
            subsetsize[rooty]+=subsetsize[rootx];
        }
        else if (subsetsize[rootx]>=subsetsize[rooty]) {
            parents[rooty]=rootx;
            subsetsize[rootx]+=subsetsize[rooty];
        }
    }
    bool connected(int i,int j) {
        return find(i)==find(j);
    }
    int get_set_size(int i) {
        return subsetsize[find(i)];
    }

};



int main() {
    // Create a DSU instance with 10 elements (0 to 9)
    int num_elements = 10;
    DSU dsu(num_elements);

    std::cout << "\n--- Performing Unite Operations ---" << std::endl;
    dsu.unite(0, 1); // Merge sets containing 0 and 1
    dsu.unite(1, 2); // Merge sets containing 1 and 2 (now 0, 1, 2 are together)
    dsu.unite(3, 4); // Merge sets containing 3 and 4
    dsu.unite(5, 6); // Merge sets containing 5 and 6
    dsu.unite(7, 8); // Merge sets containing 7 and 8
    dsu.unite(5, 8); // Merge sets containing 5 and 8 (now 5, 6, 7, 8 are together)
    dsu.unite(0, 4); // Merge the set {0,1,2} with {3,4}

    std::cout << "\n--- Checking Representatives (Find Operations) ---" << std::endl;
    for (int i = 0; i < num_elements; ++i) {
        std::cout << "Find(" << i << "): Representative is " << dsu.find(i) << std::endl;
    }

    std::cout << "\n--- Checking Connectivity (Connected Operations) ---" << std::endl;
    std::cout << "Are 0 and 2 connected? " << (dsu.connected(0, 2) ? "Yes" : "No") << std::endl; // Expected: Yes
    std::cout << "Are 3 and 1 connected? " << (dsu.connected(3, 1) ? "Yes" : "No") << std::endl; // Expected: Yes
    std::cout << "Are 5 and 7 connected? " << (dsu.connected(5, 7) ? "Yes" : "No") << std::endl; // Expected: Yes
    std::cout << "Are 0 and 5 connected? " << (dsu.connected(0, 5) ? "Yes" : "No") << std::endl; // Expected: No
    std::cout << "Are 9 and 0 connected? " << (dsu.connected(9, 0) ? "Yes" : "No") << std::endl; // Expected: No (9 is isolated)

    // Optional: Test merging elements already in the same set
    std::cout << "\n--- Testing Redundant Unite ---" << std::endl;
    dsu.unite(1, 2); // Should indicate they are already connected
    dsu.unite(6, 8); // Should indicate they are already connected

    // Optional: Test set sizes (if get_set_size method exists)
    // Make sure your DSU class has a method like get_set_size(int i)
     std::cout << "\n--- Checking Set Sizes ---" << std::endl;
     std::cout << "Size of set containing 0: " << dsu.get_set_size(0) << std::endl; // Expected: 5 (0,1,2,3,4)
     std::cout << "Size of set containing 6: " << dsu.get_set_size(6) << std::endl; // Expected: 4 (5,6,7,8)
     std::cout << "Size of set containing 9: " << dsu.get_set_size(9) << std::endl; // Expected: 1 (9)

    std::cout << "\n--- Test Completed ---" << std::endl;

    return 0;
}