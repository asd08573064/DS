#include <iostream>

using namespace std;

class array_stack
{
	private:
		int top,capacity;
		int *stack;
	public:
		array_stack():top(-1),capacity(5){
			stack = new int[capacityå];
		}
		void Push(int x);
	    void Pop();
	    bool IsEmpty();
	    int get_top();
	   	int get_size();
	    void print_info();
};
void array_stack::print_info(){
	printf("top = %d, size = %d\n",get_top(),get_size());
}

void array_stack::Push(int x){
	if (top ==  capacity - 1){
		int *tmp = new int[capacity * 2];
		capacity *= 2;
		for(int i = 0; i <= top; i++)
			tmp[i] = stack[i];
		delete [] stack;
		stack = tmp;
	}
	stack[top+1] = x;
	top++;
}

void array_stack::Pop(){
	if(!IsEmpty()){
		top--;
	}
	else{
		printf("error\n");
	}
}

bool array_stack::IsEmpty(){
	if (top == -1){
		return true;
	}
	return false;
}


int array_stack::get_top(){
	if (IsEmpty()){
		printf("error.\n");
		return -1;
	}
	return stack[top];
}

int array_stack::get_size(){
	return top;
}

int main(){
	array_stack s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.Push(6);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.Push(6);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.Push(6);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.Push(6);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.Push(6);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.Push(6);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.Push(6);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.Push(6);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.Push(6);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.Push(6);
	s.Push(6);


	while (!s.IsEmpty()){
		printf("%d ",s.get_top());
		s.Pop();
	}

	return 0;
}
