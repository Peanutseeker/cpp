#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int main(){
    int a;
    cin>>a;
    int digit=10000;
    int digits[digit];
    memset(digits,0,digit*4);
    digits[1]=1;
    int n;
    cin>>n;
    while(n>0){
        for (int i=1;i<sizeof(digits)/sizeof(digits[0]);i++){
            digits[i]=digits[i]*a+digits[i-1]/10;
        }
        for (int i=1;i<sizeof(digits)/sizeof(digits[0]);i++){
            digits[i]=digits[i]%10;
        }
        n--;
    }
    int starter=digit-1;
    while(digits[starter]==0){
        starter--;
    }
    for (int j=starter;j>=1;j--){
            cout<<digits[j];
    }
    
    return 0;
}