#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


int maxsubarray(vector<int> arr){
    int maxsum=arr[0];
    int sum=arr[0];
    for(int i=1;i<arr.size();i++){
        sum+=arr[i];
    }
}

void cinarr(vector<int> &test){
    string input;
    cout << "Enter numbers separated by spaces: ";
    getline(cin, input);
    stringstream ssin(input);
    int num;
    
    while (ssin >> num) {
        test.push_back(num);
    }
}

int main(){
    vector<int> arr;
    cinarr(arr);
    int sum=maxsubarray(arr);
    cout<<sum;
    return 0;
}
