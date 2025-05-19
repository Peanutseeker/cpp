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
    
    int i = left;
    int j = right;
    int mid = (right + left) / 2;  // Safer way to calculate midpoint
    T pivot = arr[mid];
    
    while (i <= j) {
        // Find element on left that should be on right
        while (i <= right && arr[i] < pivot) i++;
        // Find element on right that should be on left
        while (j >= left && arr[j] > pivot) j--;
        
        if (i <= j) {
            swap(arr, i, j);  // Using our new swap function
            i++;
            j--;
        }
    }
    
    // Recursive calls
    if (left < j) quicksort(arr, left, j);
    if (i < right) quicksort(arr, i, right);
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