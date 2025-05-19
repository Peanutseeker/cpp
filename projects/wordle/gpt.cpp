
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

    string check(word b){
        string res="";
        string guess=b.wordstr;
        for (int i=0;i<=4;i++){
            if (guess[i]==wordstr[i]) res+='G';
            else if(count[guess[i]]>=b.count[guess[i]]) res+='Y';
            else res+='R';
        }
        return res;
    }
    
    private:
    map<char,int> count;
    string wordstr;
    
};

void update(char status[],string wordstatus,string guess){
    int key=0;
    for(int i=0;i<=4;i++){
        key=guess[i]-'a';
        if (status[key]=='X'||status[key]=='R') status[key]=wordstatus[i];
        else if(status[key]=='Y'||wordstatus[i]=='G') status[key]='G';
    }
}



void toupper(string a){
    for (char alpha:a){
        cout<<char(toupper(alpha));
    }
}


int main() {
    int rounds;
    WordSet wordbank;
    cin >> rounds;
    
    for (int i = 1; i <= rounds; i++) {
        // Game initialization
        string answer;
        char status[26];
        memset(status, 'X', 26 * sizeof(char));
        
        // Get valid answer
        while (1) {
            getline(cin >> ws, answer);
            if (wordbank.in_final_set(answer)) break;
            cout << "INVALID" << endl;
        }
        word ans(answer);

        int tries = 6;
        bool win = false;
        
        // Main game loop
        while (tries--) {
            string guess;
            while (1) {
                getline(cin >> ws, guess);
                if (wordbank.in_acceptable_set(guess)) break;
                cout << "INVALID" << endl;
            }
            word gue(guess);

            string res = ans.check(gue);
            update(status, res, guess);
            
            // Print result and status (all uppercase)
            cout << res << " ";
            for (int i = 0; i < 26; i++) {
                cout << (char)toupper(status[i]);
            }
            cout << endl;

            if (res == "GGGGG") {
                win = true;
                cout << "CORRECT " << 6 - tries << endl;
                break;
            }
        }
        
        if (!win) {
            cout << "FAILED ";
            for (char c : answer) {
                cout << (char)toupper(c);
            }
            cout << endl;
        }
    }
    return 0;
}