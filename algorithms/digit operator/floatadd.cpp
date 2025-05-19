#include <iostream>
using namespace std;

void copy(char* a,int* left,int* right){
    char* point=a;
    while(*point!='.') {
        point++;
    }
    char* leftcpy=point-1;
    int* leftwr=left+159;
    while(*leftcpy!='\0') {
        *leftwr=int((*leftcpy)-'0');
        leftcpy--;
        leftwr--;
    }
    char* rightcpy=point+1;
    int* rightwr=right;
    while(*rightcpy!='\0') {
        *rightwr=int((*rightcpy)-'0');
        rightcpy++;
        rightwr++;
    }
}
void add(int* left1,int* right1,int* left2,int* right2){
    for(int i=0;i<=159;i++){
        left2[i]+=left1[i];
        right2[i]+=right1[i];
    }
    for(int i=159;i>=1;i--){
        right2[i-1]+=right2[i]/10;
        right2[i]=right2[i]%10;
    }
    if (right2[0]>=10) {
        left2[159]+=right2[0]/10;
        right2[0]%=10;
    } 
    for(int i=159;i>=1;i--){
        left2[i-1]+=left2[i]/10;
        left2[i]%=10;
    }
}
void convert(int* left,int* right,char* res){
    char* write=res;
    int* leftcpy=left;
    while(*leftcpy==0&&leftcpy-left<=160) leftcpy++;
    if(leftcpy-left<160) {
        while(leftcpy-left<160) {
            *write=char(*leftcpy+'0');
            leftcpy++;
            write++;
        }
    }
    *write='.';
    write++;
    int* rightcpy=right+159;
    while(*rightcpy==0&&rightcpy>=right-1) rightcpy--;
    if(rightcpy>=right) {
        int* temp=right;
        while(temp<=rightcpy){
            *write=char(*temp+'0');
            write++;temp++;
        }
    }
}

void add_float(char* a, char* b, char* res) {
    int aleft[160]={0},aright[160]={0};
    int bleft[160]={0},bright[160]={0};
    copy(a,aleft,aright);
    copy(b,bleft,bright);
    add(aleft,aright,bleft,bright);
    convert(bleft,bright,res);
    
}


int main()
{
    char num1[160]={'\0'}, num2[160]={'\0'}, res[160]={'\0'};
    cin >> num1;
    cin >> num2;
    
    add_float(num1, num2, res);
    cout << res << endl;
    return 0;
}
