#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
using namespace std;
int m_pre = 0;
int m_pos = 1;

typedef struct stack 
{
    struct stack *next;
    long long int val;
} Stack;

class array_stack
{
    private:
        int top,capacity;
        Stack *head;
    public:
        array_stack():top(-1),capacity(5){
            head = NULL;
        }
        void Push(long long int x);
        void Pop();
        bool IsEmpty();
        long long int get_top();
        int get_size();
};


void array_stack::Push(long long int x){
    Stack *newnode = new Stack;
    newnode->val = x;
    newnode->next = NULL;
    Stack *tmp = head;
    if (head == NULL){
        head = newnode;
        return;
    }
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = newnode;
}

void array_stack::Pop(){
    Stack *tmp = head;
    if (tmp && !tmp->next){
        head = NULL;
        delete tmp;
        return;
    }
    if (tmp){
        while (tmp->next->next != NULL)
            tmp = tmp->next;
        Stack *tail = tmp->next;
        tmp->next = NULL;
        delete tail;
    }
}

bool array_stack::IsEmpty(){
    if (head == NULL){
        return true;
    }
    return false; 
}


long long int array_stack::get_top(){
    Stack *tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    return tmp->val;
}

int prior(char check){
    if (check == '*' || check == '/')
        return 2;
    else if (check == '+' || check == '-')
        return 1;
    else
        return -1;
}

string creat_postfix(string s,int mode){
    string num;
    array_stack op;
    for (auto i : s){
        if (iswalnum(i))
            num += i;
        else if(i == '(')
            op.Push(i);
        else if (i == ')'){
            while (!op.IsEmpty() && op.get_top() != '('){
                num += op.get_top();
                op.Pop();
            }
            op.Pop();
        }
        else{
        	if(mode == 1){
	            while (!op.IsEmpty() && (prior(i) <= prior(op.get_top()))){
	                num += op.get_top();
	                op.Pop();
	            }
	        }
	        else{
	        	while (!op.IsEmpty() && (prior(i) < prior(op.get_top()))){
	                num += op.get_top();
	                op.Pop();
	            }
	        }
            op.Push(i);
        }
    }
    while(!op.IsEmpty()){
        num += op.get_top();
        op.Pop();
    }
    return num;
}

long long int operation(char op, long long int x, long long int y){
    if (op == '+')
        return x + y;
    if (op == '-')
        return x - y;
    if (op == '*')
        return x * y;
    if (op == '/')
        return x / y;
    return -1;
}

long long int calculate(string s){
    array_stack st;
    long long int oprand1,oprand2;
    for(auto i : s){
        if (isalnum(i))
            st.Push(i-'0');
        else{
            oprand2 = st.get_top();
            st.Pop();
            oprand1 = st.get_top();
            st.Pop();
            st.Push(operation(i, oprand1, oprand2));
        }
    }
    return st.get_top();
}

int main(void){
    string post_s;
    string s;
    string prefix;
    string tr_infix;
    while(cin >> s){
	    tr_infix = s;
	    reverse(tr_infix.begin(), tr_infix.end());
	    for(int i = 0; i < tr_infix.length(); i++){
	        if (tr_infix[i] == '(')
	            tr_infix[i] = ')';
	        else if (tr_infix[i] == ')')
	            tr_infix[i] = '(';
	    }
	    prefix = creat_postfix(tr_infix,m_pre);
	    post_s = creat_postfix(s,m_pos);
	    reverse(prefix.begin(),prefix.end());
	    cout << post_s << '\n';
	    cout << prefix << '\n';
	    cout << calculate(post_s) << '\n';
	}
    
}
