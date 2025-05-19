//本关任务：5*5的格子中，每个格子代表一盏灯，
//点击一次，此格子和上下左右相邻的共5个格子中的灯的状态会发生反转，亮着的会熄灭，熄灭的会点亮。
//如何用最少的点击次数使所有的灯都点亮？（亮灯用1表示，熄灭状态用0表示）
#include <iostream>
using namespace std;

int mintries=606;
bool succeed=false;
void turn(int a[5][5],int i,int j){
    a[i][j]++;
    if (i>0) a[i-1][j]++;
    if (j>0) a[i][j-1]++;
    if(i<4) a[i+1][j]++;
    if(j<4) a[i][j+1]++;
}

bool judge(int lights[5][5]){
    
    bool all=true;
     for (int i=0;i<5;i++){
        for (int j=0;j<5;j++){
            if (lights[i][j]%2==0) all=false;
        }
    }
    return all;
}

//二叉树搜索
//思路：每个节点开灯或者不开灯，一共25个，每次搜到底，搜索完回到上一级
//pos记录搜索到了第几个节点
void DFS(int lights[5][5],int pos,int step){
    //判断边界
    if (judge(lights)) {
        mintries=min(mintries,step);
        succeed=true;
        return;//返回上一级，继续搜索
    }//判断与目标是否吻合
    if(pos>24) return; //搜索到底，返回上一级
    if(step>mintries) return;//搜索步数超过最优，可停止深度搜索返回上一级
    
    int rol=pos/5;
    int col=pos%5;
    DFS(lights,pos+1,step);//当前节点不开灯搜索
    turn(lights,rol,col);
    DFS(lights,pos+1,step+1);//当前节点开灯搜索
    turn(lights,rol,col);//把灯关了，让灯回到上一级状态
    return;
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

    DFS(lights,0,0);
    if(!succeed)cout<<-1;
    else cout<<mintries;
    return 0;
}