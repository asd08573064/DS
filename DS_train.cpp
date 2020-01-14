#include <iostream>
using namespace std;
class Stack
{
    private:
        int array[1000000];
        int top;
    public:
        Stack(){
            top = -1;
        };
        bool Isempty();
        void Pop();
        void Push(int x);
        int Gettop();
};

bool Stack::Isempty(){
    if(top == -1)
        return true;
    return false;
}

void Stack::Pop(){
    if(Isempty()){
        return;
    }
    else
        top--;
}

void Stack::Push(int x){
    top++;
    array[top] = x;
}

int Stack::Gettop(){
    if(Isempty())
        return -1;
    return array[top];
}

int main(){
    int n;
    while(scanf("%d",&n) != EOF){
    	Stack s;
        int index = 1;
        int index_t = 1;
        int arr[100000];
        int target[100000];
        for(int i = 1; i <= n; i++)
            arr[i] = i;
        for(int i = 1; i <= n; i++)
            scanf("%d",&target[i]);
        while(index_t <= n){
        	//printf("d = %d t = %d\n",index,index_t );
           if (s.Gettop() == target[index_t]){
           	   //printf("1, top = %d\n",s.Gettop() );
               s.Pop();
               index_t++;
           }
          else if(index <= n && arr[index] != target[index_t]){
          	  //printf("2, push %d\n",arr[index]);
              s.Push(arr[index]);
              index++;
           }
           else if(arr[index] == target[index_t]){
           	   //printf("3\n");
               index++;
               index_t++;
           }
           else
           	break;
        }
        if (s.Isempty())
            printf("YES\n");
        else{
        	while(!s.Isempty()){
        		//printf("%d\n",s.Gettop());
        		s.Pop();
        	}
            printf("NO\n");
        }
    }
}
