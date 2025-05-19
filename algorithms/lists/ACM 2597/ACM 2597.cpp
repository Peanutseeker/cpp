#include<iostream>
using namespace std;
#include<vector>
void reverse(vector<int>& arr, int left,int right){
    int temp;
    for (int m=left;m<=(left+right)/2;m++){
        temp=arr[m];
        arr[m]=arr[left+right-m];
        arr[left+right-m]=temp;
    }
}
//注意：这种反转只做一半
int main(){
    int n;
    cin>>n;
    vector<int> arr={};
    int input;
    for(int i=0;i<n;i++){
        cin>>input;
        arr.push_back(input);
    }
    int k;
    cin>>k;
    int left,right;
    for (int j=0;j<k;j++){
        cin>>left>>right;
        reverse(arr,left-1,right-1);
    }
    for (int i=0;i<n;i++){
        cout<<arr[i]<<' ';
    }
    return 0;
}