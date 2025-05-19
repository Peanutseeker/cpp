//a-z represents 0-25
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
using namespace std;
void str2int(string chars, int length,int* int26){
    for (int i=length-1;i>=0;i--){
        *int26=chars[i]-'a';
        int26++;
    }
}

void int2str(int result[],int end){
    for (int i=end;i>=0;i--){
        cout<<char(result[i]+'a');
    }
}

int main(){
    //string to int 0-25
    string a1,a2;
    cin>>a1>>a2;
    int* array1=new int[a1.size()];
    int* array2=new int[a2.size()];
    str2int(a1,a1.size(),array1);
    str2int(a2,a2.size(),array2);
    //multiplication
    int* result=new int[a1.size()+a2.size()];//结果位数小于两因子位数之和
    int end=0;
    memset(result,0,8*(a1.size()+a2.size()));

    for (int pt2=0;pt2<a2.size();pt2++){//the digits of the second factor
        for (int pt1=0;pt1<a1.size();pt1++){//digits of the first factor
            result[pt1+pt2]+=array2[pt2]*array1[pt1];
    }
    }
    //先全加，再处理进位

    for (int i=0;i<(a1.size()+a2.size());i++){
        result[i+1]+=result[i]/26;
        result[i]%=26;
        if (result[i]!=0){end++;}
    }


    int2str(result,end-1);

    return 0;
}