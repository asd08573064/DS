#include <iostream>

using namespace std;

class Node
{
public:
	int Q;
	int val;
	Node *next;
	Node *pre;
	Node();
	Node(int val){
		this->next = NULL;
		this->pre = NULL;
		this->Q = 0;
		this->val = val;
	}
};

class Chain
{

public:
	Chain(){
		head = NULL;
		tail = head;
	}
	int opreation(int start);
	void insert(int a);
	void insert_Q(int num);
	Node *head;
	Node *tail;

};

int Chain::opreation(int start){
	while(head->val != start)
            head = head->next;
        while(head->next != head){
            int Q = head->Q;
            Node *tmp = head;
            head->next->pre = head->pre;
            head->pre->next = head->next;
            if(Q > 0){
                for(int i = 0; i < Q; i++)
                    head = head->next;
            }
            else{
				Q = -Q;
                for(int i = 0; i < Q; i++)
                    head = head->pre;
            }
            delete tmp;

        }
        return head->val;
}

void Chain::insert(int num){
	for(int i = 1; i <= num; i++){
		if(!head){
			head = new Node(i);
			tail = head;
		}
		else{
			tail->next = new Node(i);
			tail->next->pre = tail;
			tail = tail->next;
		}
	}
	tail->next = head;
	head->pre = tail;
	Node *tmp = head;
}

void Chain::insert_Q(int num){
	Node *node = head;
	int q;
	for(int i = 0; i < num; i++){
		cin >> q;
		node->Q = q;
		node = node->next;
	}
}
int main(void){
	int num;
	int start;
	while(cin >> num){
		Chain list;
		list.insert(num);
		list.insert_Q(num);
		cin >> start;
		cout << list.opreation(start) << '\n';
	}
}

