//要求：输入一个数字表示扔几个色子，然后一个数字表示和
//输出能表示出这个和的所有可能点子组合

#include <iostream>
#include <vector>
using namespace std;

ostream& operator<<(ostream& os,vector<int> dice){
    os<<'{';
    for (int i:dice){
        os<<i<<',';
    }
    os<<'}'<<endl;
    return os;
}

void diceroll(int n,int sum,vector<int>& dice,int dicesum){
    if(n==0){
        if(dicesum==sum) {
            cout<<dice;
        }
    }
    else if(dicesum>=sum){
    }
    else{
        for(int i=1;i<=6;i++){
            dice.push_back(i);
            diceroll(n-1,sum,dice,dicesum+i);
            dice.pop_back();
        }
    }
}

void diceroll(int n,int sum){
    vector<int> dice={};
    int dicesum=0;
    diceroll(n,sum,dice,dicesum);
}

int main(){
    int sum,n;
    cin>>n>>sum;
    diceroll(n,sum);
}



