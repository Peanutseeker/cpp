#include <iostream>
#include <stack>
#include <map>
using namespace std;

bool symmetry(string s){
    stack<char> brackets={};
    map<char,char> sym={{'(',')'},{'[',']'},{'{','}'}};
    for (char a: s){
        if(a=='{' || a=='('|| a=='[') {
            brackets.push(a);
        }
        else if(a=='}'||a==']'||a==')'){
            //同学提醒，读取top的时候可能栈是空的（右括号多于左括号时）不一定有元素
            //因此要讨论一下空栈
            //经验：碰到segmentation fault的时候检查一下空容器
            if(brackets.empty()) return false;
            else 
            {
                char b=brackets.top();
                if (sym[b]!=a) return false;
                else brackets.pop();
            }
        }
    }
    return brackets.empty();
}

int main(){
    int n;
    cin>>n;
    string s;
    cin>>s;
    cout<< symmetry(s);
}