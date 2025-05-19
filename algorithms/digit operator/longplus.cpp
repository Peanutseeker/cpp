/*------------------------------------------------------
注意：仅在标有"Begin"和"End"的注释行之间补充填写代码，
      请勿改动任何已有内容。
------------------------------------------------------*/
#include <iostream>
#include <cstring>
using namespace std;

#define MAX_LENGTH 100

//相关函数的原型
/********* Begin *********/

int char2int(char a){
    return int(a-'0');
}
char int2char(int a){
    return char(a+'0');
}
void fill(int* a,string b,int blength){
    for (int i=0;i<blength;i++){
        *(a+100-i)=char2int(b[blength-1-i]);
    }
}
void plusint(int* result,int* a, int* b){
    int temp=0;
    for (int i=100;i>=0;i--){
        temp=temp+a[i]+b[i];
        result[i]=temp%10;
        temp=temp/10;
    }
}

void minusint(int* result, int* a, int* b){
    int temp=0;
    for(int i=100;i>=1;i--){
        if (i==100) {temp+=10-b[i]+a[i];}
        else {temp+=9-b[i] + a[i];}
        result[i]=temp%10;
        temp=temp/10;
    }
    result[0]=temp-1;
}

void print(int* a){
    if (a[0]==-1) {
        cout<<'-';
        int i=1;
        while(*(a+i)==9) i++;
        while(i<=99){cout<<9-a[i];i++;}
        cout<<10-a[i];
    }
    else{
    int i=1;
    while(*(a+i)==0){
        i++;
    }
    while(i<=100){
        cout<<a[i];
        i++;
    }
    }
    cout<<endl;
}

/*********  End  *********/

int main()
{
	/********* Begin *********/
	string a,b;char c;
    int adig[101]={0};int bdig[101]={0};//多一个当符号位
    cin>>a>>c>>b;
    int result[101]={0};
    fill(adig,a,a.length());
    fill(bdig,b,b.length());
    if (c=='+') {plusint(result,adig,bdig);}
    if (c=='-') {minusint(result,adig,bdig);}
    print(result);



	//联系：计算机里减法是用反码算的！
	/*********  End  *********/
	return 0;
}

//相关函数的具体定义
/********* Begin *********/



/*********  End  *********/