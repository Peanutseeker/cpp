#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector<int> a={};

void permutation(int n,int* used,int step){
    for (int i=1;i<=n;i++){
        if (used[i]==0){
            used[i]=1;
            a.push_back(i);
            if(step==n){
                for(vector<int>::iterator it=a.begin();it!=a.end();it++){
                    cout<<*it<<' ';
                }
                cout<<endl;
                a.pop_back();
                used[i]=0;
            }
            else {
                permutation(n,used,step+1);
                a.pop_back();
                used[i]=0;
            }
            
        }
    }
}
int main(){
    int n;
    cin>>n;
    int used[n+1]={0};
    permutation(n,used,1);
    return 0;
}