#include<iostream>
using namespace std;
#include<vector>

struct node{
    int val;
    node* next;
    node(int x):val(x),next(nullptr){}
};

void print(node* head){
    node* printer=head;
    while(printer){
        cout<<printer->val<<' ';
        printer=printer->next;
    }
}


int main(){
    int n;
    cin>>n;
    node* head=new node(527);
    node* bridge=head;
    int input;
    for(int i=0;i<n;i++){
        cin>>input;
        node* newnode=new node(input);
        bridge->next=newnode;
        bridge=newnode;
    }
    head=head->next;

    int k; cin>>k;

    print(head);
    return 0;
}