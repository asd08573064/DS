#include <iostream>
#include <string>
using namespace std;

int preindex;

class Node
{
public:
	Node();
	Node(int key){
		val = key;
		right = NULL;
		left = NULL;
	};
	~Node();
	char val;
	Node *right;
	Node *left;
};

int search(string in, char val,int start,int end){
	for(int i = start; i <= end; i++){
		if(in[i] == val)
			return i;
	}
}

Node *build_tree(string pre, string in, int start, int end){
	if(start > end)
		return NULL;
	Node *newnode = new Node(pre[preindex++]);

	if(start == end)
		return newnode;

	int in_index = search(in,newnode->val,start,end);

	newnode->left = build_tree(pre,in,start,in_index-1);
	newnode->right = build_tree(pre,in,in_index+1,end);

	return newnode;
}

void post(Node *node){
	if(node){
		post(node->left);
		post(node->right);
		cout << node->val;
	}
}



int main(){
	string pre, in;
	while(
		){
		Node *node;
		preindex = 0;
		node = build_tree(pre,in,0,6);
		post(node);
	}
}