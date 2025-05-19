#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <cctype>
using namespace std;
// 此类读入并存储了候选词和可用词集合
// 调用此类的两个成员函数可以判断一个单词是否属于候选词/可用词集合
class WordSet {
  public:
    // 在构造时，从文件读入候选集和可用集。
    // 你需要在代码中实例化一个 WordSet 类型变量。
    WordSet() {
        std::ifstream FINAL_FILE;
        FINAL_FILE.open("./FINAL.txt", std::ifstream::in);
        if (!FINAL_FILE) {
            std::cerr << "Error: cannot open FINAL.txt" << std::endl;
            exit(1);
        }
        while (!FINAL_FILE.eof()) {
            std::string str;
            FINAL_FILE >> str;
            final_set.insert(str);
        }

        std::ifstream ACCEPTABLE_FILE;
        ACCEPTABLE_FILE.open("./ACC.txt", std::ifstream::in);
        if (!ACCEPTABLE_FILE) {
            std::cerr << "Error: cannot open ACC.txt" << std::endl;
            exit(1);
        }
        while (!ACCEPTABLE_FILE.eof()) {
            std::string str;
            ACCEPTABLE_FILE >> str;
            acceptable_set.insert(str);
        }
    }

    // 判断输入参数 word 是否属于候选集合
    bool in_final_set(std::string word) { return final_set.find(word) != final_set.end(); }

    // 判断输入参数 word 是否属于可用集合
    bool in_acceptable_set(std::string word) { return acceptable_set.find(word) != acceptable_set.end(); }

  private:
    std::set<std::string> final_set;
    std::set<std::string> acceptable_set;
};

// TODO：你可以添加类或者函数

class word{
    public:
    word(string a){
        wordstr=a;
        for (char a='a';a<='z';a++){
            count[a]=0;
        }
        for(char alphabet:a){
            count[alphabet]++;
        }
    }

    string check(word b) {
        string res = "RRRRR";
        string guess = b.wordstr;
        map<char, int> remaining = count;
        
       
        for (int i = 0; i < 5; i++) {
            if (guess[i] == wordstr[i]) {
                res[i] = 'G';
                remaining[guess[i]]--; 
            }
        }
        

        for (int i = 0; i < 5; i++) {
            if (res[i] != 'G' && remaining[guess[i]] > 0) {
                res[i] = 'Y';
                remaining[guess[i]]--;
            }
        }
        
        return res;
    }
    
    
    private:
    map<char,int> count;
    string wordstr;
    
};



void update(char status[],string wordstatus,string guess,map<char,int> &Gchars,set<char> &Ychars){
    int key=0;
    for(int i=0;i<=4;i++){
        key=guess[i]-'a';
        if (status[key]=='X'||status[key]=='R') status[key]=wordstatus[i];
        else if(status[key]=='Y'||wordstatus[i]=='G') status[key]='G';
    }
    for(int i=0;i<=4;i++){
        if(wordstatus[i]=='G') Gchars[guess[i]]=i;
        else if(wordstatus[i]=='Y') Ychars.insert(guess[i]);
    }

}

void toupper(string a){
    for (char alpha:a){
        cout<<char(toupper(alpha));
    }
}

int main() {
    // TODO：程序从这里开始运行

    //step 1:整轮游戏初始化
    int mode;
    WordSet wordbank;
    while(1){
        cin>>mode;
        if(mode>=1&&mode<=4 ) break;
        else cout<<"INVALID"<<endl;
    }
    
    while(1){

        
        //单轮游戏初始化
        string answer;
        char status[26];
        memset(status,'X',26*sizeof(status[0]));
        while(1){
            getline(cin>>ws,answer);
            if(wordbank.in_final_set(answer)) break;
            else cout<<"INVALID"<<endl;
        }
        word ans(answer);

        int tries=6;
        string guess;
        bool win=false;
        string input;
        map <char,int> Gchars={};
        set<char> Ychars={};
        while(tries--){
            while(1){
            getline(cin>>ws,input);
            bool valid=wordbank.in_acceptable_set(input);
            if(valid){
                 if(mode>=3&&tries!=6){
                    for(pair<char,int> it:Gchars){
                        if(input[it.second]!=it.first) valid=false;
                    }
                    for(char i:Ychars){
                        if(input.find(i)==-1) valid=false;
                    }
                }
            }

            if(!valid){
                cout<<"INVALID"<<endl;
                continue;}
            else{
                guess=input;break;
            }
            
        }
        word gue(guess);

        string res;
        res=ans.check(gue);
        update(status,res,guess,Gchars,Ychars);

        cout<<res<<' ';
        for(int i=0;i<=25;i++){
            cout<<status[i];
        }
        cout<<endl;
        if(res=="GGGGG") {
            win=true;
            cout<<"CORRECT "<<6-tries<<endl;
            break;
        }

    }
    if (!win) {
        cout<<"FAILED ";
    toupper(answer);
    cout<<endl;
    }

    if(mode==1) break;
    else{
        char proceed;
        proceed=cin.get();
        
    if(proceed==EOF||proceed=='N') break;
    }
    }
    return 0;
}
