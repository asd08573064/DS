#include <iostream>

using namespace std;

typedef struct node
{
	int data;
	struct node *next;
} Node;

class queue_list
{
	private:
		Node *head;
		int capacity;
	public:
		queue_list():head(NULL), capacity(5){

		};
		void Push_back(int x);
	    void Pop();
	    bool IsEmpty();
	    int getFront();
	    int getBack();
	    void print_info();
};
void queue_list::Push_back(int x){
	Node *tmp = head;
	Node *newnode = new Node;
	newnode->data = x;
	newnode->next = NULL;
	if (head == NULL){
		head = newnode;
		return;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = newnode;
}

void queue_list::Pop(){
	if (head){
		Node *tmp = head;
		head = head->next;
		delete tmp;
	}
}

bool queue_list::IsEmpty(){
	if (!head)
		return true;
	return false;
}

int queue_list::getFront(){
	if (head)
		return head->data;
	return -1;
}

int queue_list::getBack(){
	Node *tmp = head;
	if (head){
		while(tmp->next != NULL)
			tmp = tmp->next;
		return tmp->data;
	}
	return -1;
}

void queue_list::print_info(){
	printf("front = %d, back = %d\n",getFront(),getBack());
}

int main(){
	queue_list q;
	q.Push_back(1);
	q.Push_back(2);
	q.Push_back(3);
	q.Push_back(3);
	q.Push_back(3);
	q.Push_back(1);
	q.Push_back(2);
	q.Push_back(3);
	q.Push_back(3);
	q.Push_back(3);
	



	while (!q.IsEmpty()){
		printf("%d ",q.getFront());
		q.Pop();
	}

	return 0;
}