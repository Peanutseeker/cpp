#include <iostream>
using namespace std;
#include <bits/stdc++.h>

int main() {
    int n,m;
    cin>>n>>m;
    vector<int> truster(n+1,0);
    vector<int> trusted(n+1,0);
    for (int i=1;i<=m;i++) {
        int k,l;
        cin>>k>>l;
        truster[k]++;
        trusted[l]++;
    }
    int res=-1;
    for (int i=1;i<=n;i++) {
        if (truster[i]==0&&trusted[i]==n-1) {
            res=i;break;
        }
    }
    cout<<res;
    return 0;
}