#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void printallbinaries(int& start,int n,vector<int> &number){
    if (start==n) {
        for (int a:number){
            cout<<a;
        }
        cout<<endl;
    }
    else {
    number.push_back(0);
    printallbinaries(++start,n,number);
    number.pop_back();
    number.push_back(1);
    printallbinaries(start,n,number);
    number.pop_back();
    start--;
    }
}

void printallbinaries(int n){
    int start=0;
    vector<int> number={};
    printallbinaries(start,n,number);
}

int main(){
    int n;
    cin>>n;
    printallbinaries(n);
}