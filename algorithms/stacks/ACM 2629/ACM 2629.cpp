#include<iostream>
#include<vector>
using namespace std;
#include<stack>

int main(){
    int n;
    cin>>n;
    vector<vector<int>> mat(n,vector<int> (n,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>mat[i][j];
        }
    }
}
