#include <iostream>
using namespace std;
#include <vector>
int main(){
    int n;
    cin>>n;
    vector<int> arr={};
    vector<int> order={};
    int input;
    for (int i=0;i<n;i++){
        cin>>input;
        arr.push_back(input);
    }
    int k;
    cin>>k;
    for (int i=0;i<n;i++){
        if(arr[i]<k) cout<<arr[i]<<' ';
        else order.push_back(i);
    }
    for(int j:order){
        cout<<arr[j]<<' ';
    }
}