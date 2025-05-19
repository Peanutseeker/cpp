#include <iostream>
using namespace std;
#include<vector>
#include <stack>

//说明：这里用minstack代指单调递减栈，因为栈顶元素就是最小值

vector<int> larger(vector<int>& num){
    stack<int> minstack;
    int n=num.size();
    vector<int> ans(n,0);
    for(int i=0;i<n;i++){
        while(!minstack.empty()&&num[minstack.top()]<num[i]) {
            ans[minstack.top()]=i+1;
            minstack.pop();
        }
        minstack.push(i);
    }
    return ans;
}

int main(){
    int n;
    cin>>n;
    vector<int> input(n,0);
    for(int i=0;i<n;i++){
        cin>>input[i];
    }
    vector<int> ans=larger(input);
    for(int i=0;i<n;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}