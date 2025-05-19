#include <iostream>
#include <vector>
using namespace std;

class List{
    private:
    
    //Note: you can initialize the values in the private section 
    //simultaneously with declarations

    int* arr;
    int capacity=50;
    int length=0;
    int extend=2;

    public:
    List(){
        arr=new int[capacity];
    }
    List(int a){
        length=a;arr=new int[a];
    }
    ~List(){
        delete[] arr;
    }
    int size(){
        return length;
    }

    int get(int i){
        if(i>=length ||i<0) throw out_of_range("out of range!");
        else return arr[i];
    }

    void set(int i,int a){
        if(i>=length ||i<0) throw out_of_range("out of range!");
        else arr[i]=a;
    }

    void extendlist(){
        int newcap=capacity*extend;
        int* tmp=arr;
        arr=new int[newcap];
        for (int i=0;i<length;i++){
            arr[i]=tmp[i];
        }
        delete[] tmp;
        capacity=newcap;
    }

    vector<int> tovect(){
        vector<int> vect={};
        for (int i=0;i<length;i++){
            vect.push_back(arr[i]);
        }
        return vect;
    }
    void show(){
        cout<<"capacity:"<<capacity<<endl;
        cout<<"length:"<<length<<endl;
        cout<<"List:{";
        for (int i=0;i<length;i++){
           cout<<arr[i]<<' ';
        }
        cout<<"}"<<endl;
    }

    void insert(int i, int a){
        if(i>=length ||i<0) throw out_of_range("out of range!");
        if(length==capacity) extendlist();
        for(int j=length;j>=i;j--){
            arr[j+1]=arr[j];
        }
        arr[i]=a;
        length++;
    }
    void pushback(int a){
        if(length==capacity) extendlist();
        arr[++length]=a;
    }
    void remove(int i){
        if(i>=length ||i<0) throw out_of_range("out of range!");
        else for(int j=i+1;j<length;j++){
            arr[j-1]=arr[j];
        }
        arr[length--]=0;
    }
    void popback(){
        arr[length--]=0;
    }

};

int main(){
    List test(7);
    for (int i=0;i<=6;i++){
        int a;
        cin>>a;
        test.set(i,a);
    }
    test.insert(3,5);
    test.show();
    test.insert(4,9);
    test.show();
    test.extendlist();
    test.show();
    test.remove(2);
    test.show();
    test.pushback(11);
    test.show();
    test.popback();
    test.show();

    return 0;
}