#include <iostream>
using namespace std;
#include <bits/stdc++.h>


int main() {
    int n;
    int times;
    cin>>n>>times;
    vector<int> arr(n);
    for (int i=0;i<n;i++) {
        cin>>arr[i];
    }
    auto search=[&](int q)->int {
        if (q>arr[n-1]) return n;
        int left=0;int right=n-1;
        while (left<right) {
            int mid=(left+right)/2;
            if (arr[mid]==q) return mid;
            else if (arr[mid]<q) left=mid+1;
            else right=mid;
        }
        return left;
    };
    sort(arr.begin(),arr.end());
    for (int i=1;i<=times;i++) {
        int q;
        cin>>q;
        cout<<search(q)<<endl;
    }
    return 0;
}