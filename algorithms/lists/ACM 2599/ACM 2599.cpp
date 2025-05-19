#include <iostream>
using namespace std;

struct node{
    int val;
    node* next;
    node(int x){
        val=x;next=nullptr;
    }
};

void print(node* head){
    node* printer=head;
    while(printer){
        cout<<printer->val<<' ';
        printer=printer->next;
    }
}

int main(){
    node* head1=new node(527);node* head2=new node(527);
    node* bridge1=head1;node* bridge2=head2;
    int m,n;
    cin>>m;
    int temp;
    for (int i=0;i<m;i++){
        cin>>temp;
        node* newnode=new node(temp);
        bridge1->next=newnode;
        bridge1=newnode;
    }
    cin>>n;
    for(int j=0;j<n;j++){
        cin>>temp;
        node* newnode=new node(temp);
        bridge2->next=newnode;
        bridge2=newnode;
    }
    head1=head1->next;
    head2=head2->next;

    node* head=new node(527);
    node* it=head;
    bridge1=head1;bridge2=head2;
    while(bridge1&&bridge2){
        if(bridge1->val<bridge2->val) {
            it->next=bridge1;
            bridge1=bridge1->next;
            it=it->next;
        }
        else{
            it->next=bridge2;
            bridge2=bridge2->next;
            it=it->next;
        }
        it->next=bridge1?bridge1:bridge2;
    }

    print(head->next);

    return 0;
}