#include <iostream>

using namespace std;

class queue_array
{
	private:
		int front, back, capacity;
		int *queue;
	public:
		queue_array():front(0),back(-1),capacity(5){
			queue = new int[capacity];
		};
		void Push_back(int x);
	    void Pop();
	    bool IsEmpty();
	    bool IsFull();
	    int getFront();
	    int getBack();
	    int getSize();
	    void print_info();
};
void queue_array::print_info(){
	printf("front = %d, back = %d\n",getFront(),getBack());
}

void queue_array::Push_back(int x){
	if (IsFull()){
		int *tmp = new int [capacity * 2];
		for(int i = front; i <= back; i++)
			tmp[i] = queue[i];
		tmp[back + 1] = x;
		delete queue;
		queue = tmp;
		back++;
	}
	else{
		queue[back + 1] = x;
		back++;
	}
}

void queue_array::Pop(){
	if(!IsEmpty()){
		for(int i = front + 1; i <= back; i++){
			queue[i-1] = queue[i];
		}
		back--;
	}
	else{
		printf("error\n");
	}
}

bool queue_array::IsEmpty(){
	if (front - 1 == back){
		return true;
	}
	return false;
}

bool queue_array::IsFull(){
	if (back - front + 1 == capacity){
		return true;
	}
	return false;
}

int queue_array::getFront(){
	if (IsEmpty()){
		printf("error.\n");
		return -1;
	}
	return queue[front];
}

int queue_array::getBack(){
	if (IsEmpty()){
		printf("error.\n");
		return -1;
	}
	return queue[back];
}

int queue_array::getSize(){
	return back - front + 1;
}

int main(){
	queue_array q;
	q.Push_back(1);
	q.Push_back(2);
	q.Push_back(3);
	q.Push_back(3);
	q.Push_back(3);
	q.Push_back(1);
	q.Push_back(2);
	q.Pop();
	q.Push_back(3);
	q.Pop();
	q.Push_back(3);
	q.Pop();
	q.Push_back(3);
	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();
	q.Pop();



	while (!q.IsEmpty()){
		printf("%d ",q.getFront());
		q.Pop();
	}

	return 0;
}
