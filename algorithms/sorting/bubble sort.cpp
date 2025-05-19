#include <iostream>
#include <cmath>
#include <iomanip>
#include<algorithm>
#include <cstdio>

using namespace std;
void swap(int &a,int &b){
    int c=a;
    a=b;
    b=c;
}
int main(){
    int size;
    cin>>size;
    int array[size];
    for (int i=0;i<size;i++){
        cin>>array[i];
    }
    for (int i=size-2;i>=0;i--){
        for (int j=0;j<=i;j++){
            if (array[j]>array[j+1]){
                swap(array[j],array[j+1]);
            }
        } 
    }
    for (int i=0;i<size;i++){
        cout<<array[i]<<' ';
    }
    return 0;
}