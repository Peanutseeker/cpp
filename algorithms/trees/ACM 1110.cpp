#include<iostream>
using namespace std;
#include<bits/stdc++.h>

inline int lch(int k) {
    return 2*k+1;
}
inline int rch(int k) {
    return 2*k+2;
}
inline int parent(int k) {
    return (k-1)/2;
}

//实现功能：查询区间和、修改区间
int main() {
    int n,times;
    cin>>n>>times;
    vector<int> arr(n);
    for (int i=0;i<=n;i++) {
        cin>>arr[i];
    }
    vector<int> segment(4*n);
    auto build=[&](int root,int left,int right)->void {
        //说明：root表示把这个区间信息存在segment数组的index位置
        if (left==right) segment[left]=arr[left];
        else {
            int mid=left+(right-left)/2;
            build(lch(root),left,mid);
            build(rch(root),mid+1,right);
            segment[root]=segment[lch(root)]+segment[rch(root)];
        }
    };
    build(0,0,n-1);

    auto query=[&] (int node,int nleft,int nright,int qleft,int qright) ->int {
        if (nleft>qright||nright<qleft) return 0;
        else if (nleft>=qleft&&nright<=qright) {
            return segment[node];
        }
        else {
            int mid=nleft+(nright-nleft)/2;
            return query(lch(node),nleft,mid,qleft,qright)
            +query(rch(node),mid+1,nright,qleft,qright);
        }
    };



}