#include <iostream>
using namespace std;

void swap(int* a, int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void insertsort(int* array,int n){
    if (n==0) {}
    else {
        insertsort(array,n-1);
        int tail=*(array+n);
        for (int i=n-1;i>=0;i--){
            if (tail<*(array+i)) swap(array+i+1,array+i);
            else break;
        }
    }
}

int main()
{
    int n;
    cin>>n;
    int* array =new int[n];
    for (int i=0;i<n;i++){
        cin>>*(array+i);
    }
    insertsort(array,n-1);
    for (int i=0;i<n;i++){
        cout<<*(array+i)<<' ';
    }
    
    return 0;
}