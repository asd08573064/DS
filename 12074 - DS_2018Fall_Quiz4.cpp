#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

class Node {
public:
    int val;
    vector<int> neighbors;

    Node() {}

    Node(int _val) {
        val = _val;
    }
};

int main(void){
	queue <Node*> q;
    bool check[501] = {0};
    Node *table[501];
    int num;
    string s1;
    int source, destination;
    cin >> num;
    while(cin >> s1){
        int a,b;
        if(s1[0] != 's')
            break;
        while(cin >> s1){
            if(isdigit(s1[0])){
                a = stoi(s1);
                break;
            }
        }
        while(cin >> s1){
            if(isdigit(s1[0])){
                b = stoi(s1);
                break;
            }
        }
        if(!check[a]){
        	check[a] = true;
	        Node *newnode = new Node(a);
	        newnode->neighbors.push_back(b);
	        table[a] = newnode;
	    }
	    else{
	    	table[a]->neighbors.push_back(b);
	    } 
    }
    while(cin >> s1){
    	bool flag = false;
    	bool check_bfs[501] = {0};
        while(cin >> s1){
            if(isdigit(s1[0])){
                source = stoi(s1);
                break;
            }
        }
        while(cin >> s1){
            if(isdigit(s1[0])){
                destination = stoi(s1);
                break;
            }
        }
        if(!check[source]){
        	cout << "NO\n";
        	continue;
        }
        q.push(table[source]);
        while(!q.empty()){
        	Node *current = q.front();
        	q.pop();
        	for(auto i : current->neighbors){
        		if(!check_bfs[i]){
	        		if(i == destination){
	        			flag = true;
	        			break;
	        		}
	        		else{
	        			check_bfs[i] = true;
	        			if(check[i])
	        				q.push(table[i]);
	        		}
	        	}
        	}
        }
        if(flag)
        	cout << "YES\n";
        else
        	cout << "NO\n";
    }
}
