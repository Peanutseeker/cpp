#include<iostream>
using namespace std;
#include<vector>
class MyCircularQueue {
    private:
        vector<int> nums;
        int front=-1;
        int end=-1;
        int capacity=0;
        int occupied=0;
    public:
        MyCircularQueue(int k) {
            nums=vector<int> (k,0);
            capacity=k;
            front=0;
            end=-1;
            occupied=0;
        }
        
        bool enQueue(int value) {
            if(occupied>=capacity) return false;
            else{
                end++;
                if(end>=capacity) end=end%capacity;
                nums[end]=value;
                occupied++;
                return true;
            }
        }
        
        bool deQueue() {
            if(occupied==0) return false;
            else{
                nums[front]=0;
                front++;
                if(front>=capacity) front%=capacity;
                occupied--;
                if(occupied==0) {
                    front=0;end=-1;
                }
                return true;
            }
        }
        
        int Front() {
            if(occupied==0) return -1;
            else return nums[front];
        }
        
        int Rear() {
            if(occupied==0) return -1;
            else return nums[end];
        }
        
        bool isEmpty() {
            return occupied==0;
        }
        
        bool isFull() {
            return capacity==occupied;
        }
    };
    
    /**
     * Your MyCircularQueue object will be instantiated and called as such:
     * MyCircularQueue* obj = new MyCircularQueue(k);
     * bool param_1 = obj->enQueue(value);
     * bool param_2 = obj->deQueue();
     * int param_3 = obj->Front();
     * int param_4 = obj->Rear();
     * bool param_5 = obj->isEmpty();
     * bool param_6 = obj->isFull();
     */