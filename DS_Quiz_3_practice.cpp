#include <iostream>
#include <string>
using namespace std;
int max_height = 0;
class Node{
public:
    Node();

    Node(int val){
        this->val = val;
        this->right = NULL;
        this->left = NULL;
        this->parent = NULL;
    }
    Node *right;
    Node *left;
    Node *parent;
    int val;
};
 Node *root_ = NULL;
void insert(Node *root,int val){
    if(val > root->val){
        if(root->right)
            insert(root->right,val);
        else{
            root->right = new Node(val);
        }
    }
    else if(val < root->val){
        if(root->left)
            insert(root->left,val);
        else{
            root->left = new Node(val);
        }
    }
    else
        return;
}

void count_height(Node *root, int height){
	if(root){
		if(height > max_height)
			max_height = height;
		count_height(root->left,height+1);
		count_height(root->right,height+1);
	}
}

void find(Node *root,int val){
    if(!root){
        printf("Find %d: No\n",val);
        return;
    }
    if(val > root->val){
        if(root->right)
            find(root->right,val);
        else
            printf("Find %d: No\n",val);
    }
    else if(val < root->val){
        if(root->left)
            find(root->left,val);
        else
            printf("Find %d: No\n",val);
    }
    else{
        printf("Find %d: Yes\n",val);
        return;
    }
}

Node *del(Node *root, int val){
	if(!root)
		return NULL;
	if(val > root->val){
		root->right = del(root->right,val);
	}
	else if(val < root->val){
		root->left = del(root->left,val);
	}
	else{
		if (root->left == NULL) 
        { 
            Node *temp = root->right; 
            free(root); 
            return temp; 
        } 
        else if (root->right == NULL) 
        { 
            Node *temp = root->left; 
            free(root); 
            return temp; 
        } 
		Node *tmp = root->right;
		while(tmp->left)
			tmp = tmp->left;
		root->val = tmp->val;
		root->right = del(root->right,root->val);
	}
	return root;
}

int main(){
    string s;
    int val;
   
    while(cin >> s){
        if(s[0] == 'I' || s[0] == 'F' || s[0] == 'D')
            cin >> val;
        if(s[0] == 'I'){
            if(!root_)
                root_ = new Node(val);
            else
                insert(root_,val);
        }
        else if(s[0] == 'F'){
            find(root_,val);
        }
        else if(s[0] == 'D'){
            root_ = del(root_,val);
        }
        else if(s[0] == 'C'){
             root_ = NULL;
        }

        else{
        	max_height = 0;
        	count_height(root_,1);
            cout << max_height << '\n';
        }
    }
}
