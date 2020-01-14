#include <iostream>
#include <vector>
using namespace std;


class priority_queue
{
public:
	priority_queue(){};
	void swap(int *a, int *b);
	void max_heap(int index, int length);
	void build_heap(int n);
	void push(int element);
	int pop();
	vector<int> arr;	
};

void priority_queue::swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void priority_queue::max_heap(int index, int length){
	int root = index;
	int right = index * 2 + 1;
	int left = index *2;
	int newroot = index;
	if(left <= length && arr[newroot] < arr[left]){
		newroot = left;
	}
	if(right <= length && arr[newroot] < arr[right]){
		newroot = right;
	}
	if(newroot != root){
		swap(&arr[root],&arr[newroot]);
		max_heap(newroot,length);
	}
}

void priority_queue::build_heap(int n){
	for(int i = n/2; i >= 1 ; i--){
		max_heap(i,n-1);
	}
}


int priority_queue::pop(){
	int max = arr[1];
	arr[1] = arr[arr.size()];
	arr.erase(arr.end() - 1);
	build_heap(arr.size());
	cout << "pop:" << endl;
	for(int i = 1; i <= arr.size(); i++){
		cout << arr[i] << ' ';
	}
	cout << endl;
	return max;
}
void priority_queue::push(int element){
	cout << "element = " << element << endl;
	arr.push_back(element);
	build_heap(arr.size());
	cout << "push:" << endl;
	for(int i = 1; i <= arr.size(); i++){
		cout << arr[i] << ' ';
	}
	cout << endl;
}

int main(void){
	int m;
	cin >> m;
	for(int j = 0; j < m; j++){
		int n;
		cin >> n;
		priority_queue q;
		q.arr.insert(q.arr.begin(),0); 
		for(int i = 0; i < n; i++){
			int tmp;
			cin >> tmp;
			q.push(tmp);
		}
		int len = q.arr.size();
		for(int i = 1; i < len; i++){
			cout << q.pop() <<  ' ';
		}
		cout << endl;
	}
}