//本关任务：5*5的格子中，每个格子代表一盏灯，
//点击一次，此格子和上下左右相邻的共5个格子中的灯的状态会发生反转，亮着的会熄灭，熄灭的会点亮。
//如何用最少的点击次数使所有的灯都点亮？（亮灯用1表示，熄灭状态用0表示）
#include <iostream>
#include <cstring>
using namespace std;

int mintries=606;
void turn(int* a,int i,int j){
    (*(a+5*i+j))++;
    if (i>0) (*(a+5*i+j-5))++;
    if (j>0) (*(a+5*i+j-1))++;
    if(i<4) (*(a+5*i+j+5))++;
    if(j<4) (*(a+5*i+j+1))++;
}

bool judge(int* lights){
    bool all=true;
     for (int i=0;i<=4;i++){
        if (lights[i]%2==0) all=false;
    }
    return all;
}
void addstep(int& i,int* first){
    for (int j=0;j<=4;j++){
        if (*(first+j)%2==0) i++;
    }
}

//递归法
//对第一层使用DFS，遍历每一个分支
//steps记录开灯次数

void rowlight(int* lights, int* first,int row){
    for (int i=0;i<=4;i++){
        if (first[i]%2==0) turn(lights-row*5,row,i);
    }
}

int recurse(int lightinit[5][5],int first[5]){
    int lights[5][5];
    int* light=&lights[0][0];
    memcpy(lights,lightinit,100);
    int step=0;
    addstep(step, first);
    rowlight(light,first,0);
    for (int i=1;i<=4;i++){
    addstep(step,light+5*i-5);
    rowlight(light+5*i,light+5*i-5,i);
    }
    if (!judge(light+20)) return -1;
    else return step;
}

    
int main()
{
    int lights[5][5];
    for (int i=0;i<=4;i++){
        string a;
        getline(cin,a);
        for (int j=0;j<=4;j++){
            if (a[j]=='0') lights[i][j]=0;
            else lights[i][j]=1;
        }
    }
    int minstep=606;
    int first[5]={0};
    for (int i=0;i<=31;i++){
        first[0]=i/16;
        first[1]=i/8%2;
        first[2]=i/4%2;
        first[3]=i/2%2;
        first[4]=i%2;
        int step=recurse(lights,first);
        if (step!=-1) minstep=min(minstep,step);
        //不是初始化到0，是原来状态
    }
    if (minstep<=24) cout<<minstep;
    else cout<<-1;
    
    return 0;
}