#include <iostream>
#include <string>
using namespace std;
string pre_without_leaf;
string in_without_leaf;
string pos_without_leaf;
int max_height = 0;
int max_index = 1;
int node_num = 0;

typedef struct _Pair {
	_Pair (){
		first = 0;
		second = 0;
	}
	_Pair (int f, int s){
		first = f;
		second = s;
	}
	long long int first;
	long long int second;
} Pair;

template <class Elem>
class Stack
{
  public:
    Stack(int MaxSize=500);
    Stack(const Stack<Elem> &OtherStack);
    ~Stack(void);
 
    inline void        Push(const Elem &Item); 
    inline Elem        Pop(void);              
    inline const Elem &Peek() const;  
 
  protected:
    Elem     *Data;           
    int       CurrElemNum;   
    const int MAX_NUM;       
};
 

template <class Elem>
Stack<Elem>::Stack(int MaxSize) :
    MAX_NUM( MaxSize )    
{
  Data = new Elem[MAX_NUM];
  CurrElemNum = 0;
}
 

template <class Elem>
Stack<Elem>::~Stack(void)
{
  delete[] Data;
}
 
// Push() function
template <class Elem>
inline void Stack<Elem>::Push(const Elem &Item)
{

  Data[CurrElemNum++] = Item;
}
 

template <class Elem>
inline Elem Stack<Elem>::Pop(void)
{
  return Data[--CurrElemNum];
}
 
// Peek() function
template <class Elem>
inline const Elem &Stack<Elem>::Peek() const
{ 
  return Data[ CurrElemNum - (1) ];
}

class Node
{
public:
    Node(){
       right = NULL;
       left = NULL;
       val = 0;       
    }
    Node(int val){
        this->val = val;
        right = NULL;
        left = NULL;
        val = 0;
    }
    ~Node(){
        left = NULL;
        right = NULL;
    }
    friend class tree;
    Node *right, *left;
    int val;
};

void post_order(Node *node){
    if(node){
        post_order(node->left);
        post_order(node->right);
        if(node->right || node->left){
        	pos_without_leaf += to_string(node->val);
        	pos_without_leaf += ' ';
        }
        cout << node->val << ' ';
    }
}

void inorder(Node *node,unsigned long long height){
    if(node){
        if(height > max_height)
            max_height = height;
        inorder(node->left,height+1);
        cout << node->val << ' ';
        if(node->right || node->left){
        	in_without_leaf += to_string(node->val);
        	in_without_leaf += ' ';
        }
        inorder(node->right,height+1);
    }
}

void preorder(Node *node,int index){
    if(node){
        if(index > max_index)
            max_index = index;
        cout << node->val << ' ';
        if(node->right || node->left){
        	pre_without_leaf += to_string(node->val);
        	pre_without_leaf += ' ';
        }
        preorder(node->left,2*index);
        preorder(node->right,2*index + 1);
    }
}

Node *build_tree(string str){
    int len = str.length();
    int index = 0;
    Stack<Node *> S;
    while(index < len){
        if(str[index] == '('){
            if(str[index + 1] == ')'){
                    index += 2;
                    S.Push(NULL);
               }
            else
                index++;
        }
        else if(str[index] == ')'){
            Node *left, *right, *newnode;
            right = S.Peek();
            S.Pop();
            left = S.Peek();
            S.Pop();
            newnode = S.Peek();
            S.Pop();
            newnode->left = left;
            newnode->right = right;
            S.Push(newnode);
            index++;
        }
        else{
            node_num++;
            int start = index;
            int to_insert;
            string to_int;
            while(str[index] != '(') index++;
            to_int = str.substr(start,index - start);
            to_insert = stoi(to_int);
            Node *newnode = new Node(to_insert);
            S.Push(newnode);
        }
    }
    return S.Peek();
}

Pair find_max(Node *root) 
{ 
    if (root==NULL) 
    { 
        Pair sum;
        sum.first = 0;
        sum.second = 0;
        return sum; 
    } 
    Pair left = find_max(root->left); 
    Pair right = find_max(root->right); 
    Pair sum; 
  
    sum.first = left.second + right.second + root->val; 
  
    sum.second = max(left.first, left.second) + 
                 max(right.first, right.second); 
  
    return sum; 
} 
  
long long int maxSum(Node *root) 
{ 
    Pair res = find_max(root); 
    return max(res.first, res.second); 
}

bool IsFoldableUtil(Node* n1, Node* n2) 
{ 

    if (n1 == NULL && n2 == NULL)   return true; 
    if (n1 == NULL || n2 == NULL)   return false; 
    return IsFoldableUtil(n1->left, n2->right) && IsFoldableUtil(n1->right, n2->left); 
} 

bool IsFoldable(Node* root) 
{ 
    if (root == NULL)   return true;  
    return IsFoldableUtil(root->left, root->right); 
}

int main(void){
    string s;
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    while(cin >> s){
        max_height = 0;
        max_index = 1;
        node_num = 0;
        pre_without_leaf.clear();
        in_without_leaf.clear();
        pos_without_leaf.clear();
        Node *root = build_tree(s);
        preorder(root,1);
        cout << '\n';
        inorder(root,1);
        cout << '\n';
        post_order(root);
        cout << '\n';
        cout << max_height << '\n';
        if(node_num != max_index && root != NULL)
            cout << "Not complete\n";
        else
            cout << "Complete\n";
        if (IsFoldable(root))
            cout << "Foldable\n";
        else
            cout << "Not foldable\n";
        cout << maxSum(root) << '\n';
        cout << pre_without_leaf << '\n' << in_without_leaf << '\n' << pos_without_leaf << '\n';
    }
}
