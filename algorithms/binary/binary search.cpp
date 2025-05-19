#include <iostream>
#include <vector>

using namespace std;

int binarysearch(const vector<int>& x,int start,int end, int a){
    if(end-start==1){
        if (x[start]==a){return start;}
        else if(x[end]==a) return end;
        else return -1;
    }
    else {
        int mid=(start+end)/2;
        if (x[mid]>a) return binarysearch(x,start,mid,a);
        else if (x[mid]==a) return mid;
        else return binarysearch(x,mid,end,a);
}
}
int main(){
    int n;
    cin>>n;
    vector<int> x;
    for (int i=0;i<n;i++){
        int temp;
        cin>>temp;
        x.push_back(temp);
    }
    int a;
    cin>>a;
    cout<<binarysearch(x,0,n-1,a);
    return 0;
}