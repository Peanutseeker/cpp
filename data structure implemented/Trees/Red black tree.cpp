
#include <iostream>
using namespace std;
enum Color { RED, BLACK };

template <typename T>
class RedBlackTree {
private:
    // 节点结构
    struct Node {
        T key;
        Color color;
        Node* left;
        Node* right;
        Node* parent;
        
        Node(T k) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;  // 根节点
    Node* NIL;   // 哨兵节点，可以indicate某些节点是否是叶子结点
    //初始情况下，NIL是黑色的，这样可以避免很多分类讨论

    // 左旋转操作
    void leftRotate(Node* x) {
        // 实现左旋转
        //核心：x变成x右边子树的左节点，然后右节点左子树变成x右子树，由于做了标记所以顺序不影响
        //和AVL不同点：要更新parent，记得讨论空节点
        Node* y=x->right;
        Node* beta=y->left;
        Node* parent=x->parent;
        x->right=beta;//先把x跟y关系剪断，嫁接到beta上
        //beta可能是空，不一定有parent
        if(beta!=NIL){
            beta->parent=x;
        }
        y->parent=x->parent;
        //讨论：parent是否存在
        if(!parent) root=y;
        else if(parent->left==x) parent->left=y;
        else parent->right=y;
        y->left=x;
        x->parent=y;
    }



    // 右旋转操作
    // 右旋转操作
    void rightRotate(Node* y) {
        Node* x = y->left;      // x is y's left child (cannot be NIL for rightRotate)
        y->left = x->right;     // Turn x's right subtree into y's left subtree

        if (x->right != NIL) {
            x->right->parent = y; // Update parent of x's right child
        }

        x->parent = y->parent;  // Link x's parent to y's parent

        if (y->parent == nullptr) { // y was root
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }

        x->right = y;           // Put y on x's right
        y->parent = x;          // Make x y's parent
    }

    // 插入后的修复操作
    void insertFixup(Node*& z) {
        Node* y=z->parent;
        if (y->color==RED) {
            Node* x=y->parent;
            Node* u=x->left==y?x->right:x->left;
            if (u->color==BLACK) {
                if (y==x->left&&z==y->left) {
                    rightRotate(y);
                    y->color=BLACK;
                    y->right->color=RED;
                }
                else if (y==x->right&&z==y->right) {
                    leftRotate(y);
                    y->color=BLACK;
                    y->left->color=RED;
                }
                else if (y==x->left&&z==y->right) {
                    leftRotate(z);
                    rightRotate(y);
                    y->color=BLACK;
                    y->right->color=RED;
                }
                else {
                    rightRotate(z);
                    leftRotate(y);
                    y->color=BLACK;
                    y->left->color=RED;
                }
            }
            else {
                x->color=RED;
                u->color=BLACK;
                y->color=BLACK;
            }
        }
    }

    // 删除后的修复操作
    void deleteFixup(Node*& x) {
        // 实现删除修复
    }


    // 替换子树
    //注意parent的修改
    void transplant(Node* u, Node* v) {
        // 实现子树替换,用v的子树替换u的子树,原来的子树消失
        if (u==root) root=v;
        else {
            if (u->parent->left==u) {
                u->parent->left=v;
            }
            else u->parent->right=v;
        }
        if (v!=NIL) v->parent=u->parent;
    }

    // 查找指定键的节点
    Node* searchNode(T key) const {
        // 实现查找
        Node* cur=root;
        while(cur!=NIL){
            if(key==cur->key) return cur;
            else if(key<cur->key) cur=cur->left;
            else cur=cur->right;
        }
        return nullptr;
    }

    // 查找最小键的节点
    Node* minimum(Node* node) const {
        // 实现查找最小键
        Node* cur=root;
        while(cur->left!=NIL) {
            cur=cur->left;
        }
        return cur;
    }

    // 中序遍历辅助函数
    void inorderHelper(Node* node) const {
        if (node==NIL) return;
        cout<<node->key<<' ';
        if (node->left!=NIL) inorder(node->left);
        if (node->right!=NIL) inorder(node->right);
    }

    // 递归销毁树
    void destroyTree(Node*& node) {
        // 实现销毁树
        if(node!=NIL){
            if(node->left) destroyTree(node->left);
            if(node->right) destroyTree(node->right);
            delete node;
        }
    }

public:
    // Constructor
    RedBlackTree() {
        NIL = new Node(T()); // Or some default value for T if T() is not valid
        NIL->color = BLACK;
        NIL->left = nullptr; // Or NIL
        NIL->right = nullptr; // Or NIL
        NIL->parent = nullptr; // Or NIL
        root = NIL;   // Tree starts empty, root is NIL
    }

    // Destructor
    ~RedBlackTree() {
        destroyTree(root);
        delete NIL; // Don't forget to delete the sentinel
    }

    // 插入操作
    void insert(T key) {
        Node* added=new Node(key);
        Node* it=root;
        while(it!=NIL) {
            if (it->key==key) return;
            else if (it->key<key) it=it->right;
            else it=it->left;
        }
        it=added;
        insertFixup(added);
        // 实现插入
    }

    // 删除操作
    //重点：学会用trash标记节点
    bool remove(T key) {
        // 实现删除
        Node* it=root;
        while (it!=NIL && it->key!=key) {
            if (it->key<key) it=it->right;
            else it=it->left;
        }
        if (it==NIL) return false;
        else {
            if (it->left==NIL&& it->right==NIL) {
                it=NIL;
            }
            else if (it->left==NIL) {
                Node* trash=it;
                it=it->right;
                delete trash;
            }
            else if (it->right==NIL) {
                Node* trash=it;
                it=it->left;
                delete trash;
            }
            else {
                Node* replica=minimum(it->right);
                replica->key=it->key;
                replica=NIL;
            }
            return true;
        }
    }

    // 查找操作
    bool search(T key) const {
        Node* it=root;
        while (it!=NIL) {
            if (it->key==key) return true;
            else if (it->key<key) it=it->right;
            else it=it->left;
        }
        return false;
    }

    // 中序遍历
    void inorderTraversal() const {
        // 实现中序遍历
        inorderHelper(root);
    }

    // 判断树是否为空
    bool isEmpty() const {
        // 实现判空
        return root==NIL;
    }
};

