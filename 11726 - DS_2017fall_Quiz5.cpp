#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;
int invr = 0;

class check
{
public:
	check(){};
	~check(){};
	int invert;
	int entry;
};

void merge(vector<int> &arr,int front, int mid, int end){
	vector<int> left(arr.begin() + front, arr.begin() + (mid + 1));
	vector<int> right(arr.begin() + (mid + 1), arr.begin() + end + 1);
	int right_index = 0;
	int left_index = 0;

	for(int i = front; i <= end; i++){
		if(right_index == right.size()){
			arr[i] = left[left_index];
			left_index++;
		}
		else if(left_index == left.size()){
			arr[i] = right[right_index];
			right_index++;
		}
		else if(right[right_index] >= left[left_index]){
			arr[i] = left[left_index];
			left_index++;
		}
		else{
			invr += ((mid + 1) - (left_index + front)); 
			arr[i] = right[right_index];
			right_index++;
		}
	}
}

void merge_sort(vector<int> &arr,int front, int end){
	if(front < end){
		int mid = (front + end)/2;
		merge_sort(arr,front,mid);
		merge_sort(arr,mid+1,end);
		merge(arr,front,mid,end);
	}
}

int main(void){
	int num;
	cin >> num;
	for(int k = 0; k < num; k++){
		int n,testcase;
		int store[1010][60];
		cin >> n >> testcase;
		check checking[n];
		for(int j = 0; j < testcase; j++){
			invr = 0;
			vector<int> arr;
			for(int i = 0; i < n; i++){
				int tmp;
				cin >> tmp;
				arr.push_back(tmp);
				store[j][i] = tmp;
			}
			merge_sort(arr,0,n-1);
			checking[j].invert = invr;
			checking[j].entry = j;
		}
		for (int i = 0; i < testcase - 1; i++){
			for (int j = 0; j < testcase - 1 - i; j++){
				if (checking[j].invert > checking[j + 1].invert){
					check tmp = checking[j];
					checking[j] = checking[j+1];
					checking[j+1] = tmp;
				}
			}
		}
		for (int i = 0; i < testcase; i++){
			for(int j = 0; j < n; j++){
				if(j == n - 1)
					cout << store[checking[i].entry][j] << ", ";
				else
					cout << store[checking[i].entry][j] << ' ';
			}
			cout << "NTHUnum:" << checking[i].invert << endl;
		}
		cout << endl;
	}
}

