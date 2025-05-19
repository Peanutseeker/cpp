#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// Correct swap implementation
template <typename T>
void swap(vector<T>& arr, int i, int j) {
    T temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

template <typename T>
void print(const vector<T>& arr) {
    for (const T& element : arr) {
        cout << element << ' ';
    }
    cout << endl;
}

template <typename T>
void quicksort(vector<T>& arr, int left, int right) {
    if (left >= right) return;
    
    int i = left+1;
    int j = right;
    T pivot = arr[left]; // Using leftmost element as pivot
    
    while (i < j) {
        // Find element on right that should be on left
        while (i < j && arr[j] >= pivot) j--;
        // Find element on left that should be on right
        while (i < j && arr[i] <= pivot) i++;
        
        if (i < j) {
            swap(arr, i, j);
            //不需要移动，因为换了之后循环条件一定是成立的
        }
    }
    // Place pivot in its final position
    swap(arr, left, i);
	/*
    解释：这里由于是让右指针先动的，因此右指针在循环结束时所指向的元素一定小于pivot
    由于左边指针i<j的限制条件，左边的指针最多动到j结束
    因此最后两个指针一定会合并，且合并处元素一定小于pivot
    */
    // Recursive calls
    quicksort(arr, left, i - 1);
    quicksort(arr, i + 1, right);
}


int main() {
    vector<int> test;
    string input;
    cout << "Enter numbers separated by spaces: ";
    getline(cin, input);
    stringstream ssin(input);
    int num;
    
    while (ssin >> num) {
        test.push_back(num);
    }
    
    cout << "Original array: ";
    print(test);
    
    quicksort(test, 0, test.size() - 1);
    
    cout << "Sorted array: ";
    print(test);
    
    return 0;
}