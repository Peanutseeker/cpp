#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void SlidingWindow(vector<int>& mins, vector<int>& maxs, const vector<int>& arr, int k) {
    deque<int> min_queue;
    deque<int> max_queue;

    for (int i = 0; i < arr.size(); i++) {
        // Maintain min_queue
        while (!min_queue.empty() && arr[min_queue.back()] >= arr[i]) {
            min_queue.pop_back();
        }
        while (!min_queue.empty() && min_queue.front() <= i - k) {
            min_queue.pop_front();
        }
        min_queue.push_back(i);

        // Maintain max_queue
        while (!max_queue.empty() && arr[max_queue.back()] <= arr[i]) {
            max_queue.pop_back();
        }
        while (!max_queue.empty() && max_queue.front() <= i - k) {
            max_queue.pop_front();
        }
        max_queue.push_back(i);

        // Start recording mins and maxs once the window size is reached
        if (i >= k - 1) {
            mins.push_back(arr[min_queue.front()]);
            maxs.push_back(arr[max_queue.front()]);

            // Debug output to check the current mins and maxs
            cout << "Window [" << i - k + 1 << ", " << i << "]: ";
            cout << "min: " << arr[min_queue.front()] << ", max: " << arr[max_queue.front()] << endl;
        }
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> mins;
    vector<int> maxs;
    SlidingWindow(mins, maxs, arr, k);

    // Output the mins and maxs
    cout << "Min values: ";
    for (int i = 0; i < mins.size(); i++) {
        cout << mins[i] << ' ';
    }
    cout << endl;

    cout << "Max values: ";
    for (int i = 0; i < maxs.size(); i++) {
        cout << maxs[i] << ' ';
    }

    return 0;
}
