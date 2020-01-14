#include <iostream>

using namespace std;
typedef struct stack 
{
	struct stack *next;
	int val;
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
		void Push(int x);
	    void Pop();
	    bool IsEmpty();
	    int get_top();
	   	int get_size();
};


void array_stack::Push(int x){
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


int array_stack::get_top(){
	Stack *tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return tmp->val;
}

int main(){
	array_stack s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);


	while (!s.IsEmpty()){
		printf("%d ",s.get_top());
		s.Pop();
	}

	return 0;
}
