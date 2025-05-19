#include<iostream>
#include <vector>
using namespace std;

class maxheap{
    private:
        vector<int> arr;
    public: 
        inline int left(int x){ return 2*x+1;}
        inline int right(int x) {return 2*x+2;}
        inline int parent(int x) {return (x-1)/2;}
        inline int val(int x){return arr[x];}
        int size() {return arr.size();}
        int peek(){return arr[0];}
        void swap(int x,int y){
            int temp=arr[x];
            arr[x]=arr[y];
            arr[y]=temp;
        }
        //由下到上的堆化
        void siftUp(int x){
            while(true){
                int p=parent(x);
                if(arr[p]>=arr[x]||p<0) break;
                else {
                    swap(p,x);
                    x=p;
                    }
                }          
            }
        //由上到下的堆化
        void siftDown(int x){
            while(true){
                int l=left(x);
                int r=right(x);
                if(l>=size()||r>=size()||arr[l]<=arr[x]&&arr[r]<=arr[x]) break;
                else {
                    int supplant;
                    if(arr[l]<arr[r]) supplant=r;
                    else supplant=l;
                    swap(x,supplant);
                    x=supplant; 
                }
            }
        }

        //空堆判断
        bool empty(){
            return arr.empty();
        }
        //建堆
        maxheap(vector<int> b){
            arr=b;
            for(int j=parent(size()-1);j>=0;j--){
                siftDown(j);
            }
        }
        //插入元素
        void push(int x){
            arr.push_back(x);
            siftUp(size()-1);
        }
        //堆顶弹出
        void pop(){
            swap(0,size()-1);
            arr.pop_back();
            siftDown(0);
        }
        
        //层序遍历
        vector<int> levelOrder(){
            vector<int> res={};
            for(int j:arr){
                if(j!=INT32_MAX) res.push_back(j);
            }
            return res;
        }
        void dfs(int pos,string order,vector<int> &res){
            if(pos>=arr.size()||arr[pos]==INT32_MAX) return;
            else if(order=="pre"){
                res.push_back(arr[pos]);
                dfs(left(pos),"pre",res);
                dfs(right(pos),"pre",res);
            }
            else if(order=="in"){
                dfs(left(pos),"in",res);
                res.push_back(arr[pos]);
                dfs(right(pos),"in",res);
            }
            else if(order=="post"){
                dfs(left(pos),"post",res);
                dfs(right(pos),"post",res);
                res.push_back(arr[pos]);
            }
        }

        /* 前序遍历 */
        vector<int> preOrder() {
            vector<int> res;
            dfs(0, "pre", res);
            return res;
    }

    /* 中序遍历 */
        vector<int> inOrder() {
            vector<int> res;
            dfs(0, "in", res);
            return res;
        }

    /* 后序遍历 */
        vector<int> postOrder() {
            vector<int> res;
            dfs(0, "post", res);
            return res;
        }
        
        void print(){
            for(int i:arr){
                cout<<i<<' ';
            }
            cout<<endl;
        }

};

// 使用最大堆实现的优先队列
class PriorityQueue {
    private:
        maxheap heap;
    
    public:
        PriorityQueue():heap({}){}
        
        // 入队
        void enqueue(int value) {
            heap.push(value);
        }
        
        // 出队（返回最大元素）
        int dequeue() {
            if (heap.empty()) {
                cerr << "Error: Queue is empty" << endl;
                return -1; // 或者抛出异常
            }
            int top = heap.peek();
            heap.pop();
            return top;
        }
        
        // 查看队首元素（最大元素）
        int front() {
            return heap.peek();
        }
        
        // 队列是否为空
        bool empty() {
            return heap.empty();
        }
        
        // 队列大小
        int size() {
            return heap.size();
        }
    };


int main() {
    // 测试最大堆基本操作
    cout << "=== 测试最大堆 ===" << endl;
    vector<int> data = {4, 10, 3, 5, 1};
    maxheap heap(data);
    
    cout << "初始堆: ";
    heap.print();
    
    cout << "堆顶元素: " << heap.peek() << endl;
    
    cout << "前序遍历: ";
    vector<int> preResult = heap.preOrder();
    for(int val : preResult) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "插入元素 15" << endl;
    heap.push(15);
    heap.print();
    
    cout << "弹出堆顶" << endl;
    heap.pop();
    heap.print();
    
    // 测试优先队列
    cout << "\n=== 测试优先队列 ===" << endl;
    PriorityQueue pq;
    
    // 入队一些元素
    pq.enqueue(8);
    pq.enqueue(12);
    pq.enqueue(5);
    pq.enqueue(20);
    pq.enqueue(3);
    
    cout << "队列大小: " << pq.size() << endl;
    cout << "队首元素: " << pq.front() << endl;
    
    cout << "出队顺序: ";
    while (!pq.empty()) {
        cout << pq.dequeue() << " ";
    }
    cout << endl;
    
    // 测试排序功能
    cout << "\n=== 使用堆实现排序 ===" << endl;
    vector<int> unsorted = {7, 2, 9, 4, 1, 6, 8, 3};
    cout << "原始数组: ";
    for (int val : unsorted) {
        cout << val << " ";
    }
    cout << endl;
    
    // 创建最大堆并依次弹出实现排序
    maxheap sortHeap(unsorted);
    vector<int> sorted;
    
    while (!sortHeap.empty()) {
        sorted.push_back(sortHeap.peek());
        sortHeap.pop();
    }
    //注意：堆本身不一定从大到小排列
    //排序需要不断弹出堆里面的最大值，并在每次弹出最大值后重新堆化
    //堆化的复杂度是logN，因此每次排序的复杂度是NlogN
    
    cout << "排序结果（降序）: ";
    for (int val : sorted) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
}
