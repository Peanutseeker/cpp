struct node{
    int val;
    node* next;
    node* pre;
    node(int x) {
        val=x;next=nullptr;pre=nullptr;
    }
};
class MyLinkedList {
public:
    MyLinkedList() {
        head=nullptr;
        tail=nullptr;
        length=0;
    }
    
    int get(int index) {
        if(index>=length ||index<0) return -1;
        node* it=head;
        for(int i=0;i<index;i++){
            it=it->next;
        }
        return it->val;
    }
    
    void addAtHead(int val) {
        node* newhead=new node(val);
        if(length==0) {
            head=newhead;
            tail=newhead;
            length++;
            return;
        }
        newhead->next=head;
        head->pre=newhead;
        head=newhead;
        length++;
    }
    
    void addAtTail(int val) {
        node* newtail=new node(val);
        if(length==0) {
            head=newtail;
            tail=newtail;
            length++;
            return;
        }
        newtail->pre=tail;
        tail->next=newtail;
        tail=newtail;
        length++;
    }
    
    void addAtIndex(int index, int val) {
        if(index<0||index>length) return;
        if(index==length) {
            addAtTail(val);
            return;
        } 
        if(index==0) {
            addAtHead(val);
            return;
        }
        node* newnode=new node(val);
        node* it=head;
        for(int i=0;i<index-1;i++){
            it=it->next;
        }
        newnode->next=it->next;
        it->next->pre=newnode;
        it->next=newnode;
        newnode->pre=it;
        length++;
    }
    
    void deleteAtIndex(int index) {
        if(index<0||index>=length) return; 
        node* it=head;
        if(index==0){
            node* trash=head;
            head=head->next;
            delete trash;
            length--;
            return;
        }
        for(int i=0;i<index-1;i++){
            it=it->next;
        }
        node* trash=it->next;
        it->next=it->next->next;
        if(it->next) it->next->pre=it;
        delete trash;
        if(index==length-1) tail=it;
        length--;
    }
    private:
    node* head;
    node* tail;
    int length;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */