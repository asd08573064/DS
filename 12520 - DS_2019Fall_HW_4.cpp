

#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

int max_credit = 0;
bool check_credit2[1001][1001];

class info {
public:
    int W;
    double R;

    info(){}

    info(int w, double r){
        this->R = r;
        this->W = w;
    }
};

class Graph
{
public:
    Graph() {}
    int size;
    void Add(int v1,int v2,int w, double r);
    void Delete(int v1, int v2);
    void shortest(int v1, int v2);
    void credit(int v1, int v2, int score);
    void map();
    void DFS(int index,int check[]);
    int find_min(int i[], bool sp[]);
    int find_max(int dist[],bool sp[]);
    void credit2(int v1,int v2, int score, int limit);
    void important_bus();
    void credit2_DFS(int start,int goal,int score,int limit, int times);
    info edges[1001][1001];
};



void Graph::Delete(int v1,int v2){
    edges[v1][v2].W = INT_MAX;
    edges[v2][v1].W = INT_MAX;
    edges[v1][v2].R = 0;
    edges[v2][v1].R = 0;
}



void Graph::Add(int v1, int v2, int w, double r){
    edges[v1][v2].W = w;
    edges[v2][v1].W = w;
    edges[v1][v2].R = r;
    edges[v2][v1].R = r;
}

void Graph::DFS(int index,int check[]){
    for(int i = 0; i < size; i++){
        if(!check[i] && index != i && edges[index][i].W != INT_MAX){
            check[i] = true;
            DFS(i,check);
        }
    }
}

void Graph::important_bus(){
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            int check[1001] = {0};
            int tmp = edges[i][j].W;
            edges[i][j].W = INT_MAX;
            edges[j][i].W = INT_MAX;
            DFS(0,check);
            edges[i][j].W = tmp;
            for(int k = 0; k < size; k++){
                if(!check[i]){
                    cout << "Yes\n";
                    return;
                }
            }
        }
    }
    cout << "No\n";
}

void Graph::shortest(int v1, int v2){
    int dist[size];
    bool sp_set[size];
    int pi[size];
    for(int i = 0; i < size; i++){
        sp_set[i] = false;
        dist[i] = edges[v1][i].W;
        pi[i] = v1;
    }
    dist[v1] = 0;  
    for(int i = 0; i < size - 1; i++){

        int index = find_min(dist,sp_set);

        sp_set[index] = true;

        for(int w=0; w < size; w++){
            if(!sp_set[w] && edges[index][w].W != INT_MAX && dist[index] + edges[index][w].W < dist[w]){
                dist[w] = dist[index] + edges[index][w].W;
                pi[w] = index;
            }
        }
    }
    if(dist[v2] == INT_MAX)
        cout << "Error\n";
    else
        cout << dist[v2] << endl;
}

void Graph::credit2_DFS(int start,int goal,int score,int limit,int times){
    if(start == goal && score > max_credit && times <= limit){
        max_credit = score;
    }
    for(int i = 0; i < size; i++){
        if(!check_credit2[start][i] && start != i && edges[start][i].W != INT_MAX){
            int tmp = score;
            score = (int)(score * edges[start][i].R);
            check_credit2[start][i] = true;
            check_credit2[i][start] = true;
            credit2_DFS(i,goal,score,limit, times+1);
            check_credit2[start][i] = false;
            check_credit2[i][start] = false;
        }
    }
    
}


void Graph::credit2(int v1,int v2,int score, int limit){
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            check_credit2[i][j] = false;
            check_credit2[j][i] = false;
        }
    }
    credit2_DFS(v1,v2,score,limit,0);
}

void Graph::credit(int v1, int v2,int score){
    int new_credit[size+1];
    bool sp_set[size+1];
    for(int i = 0; i < size; i++){
        sp_set[i] = false;
        new_credit[i] = edges[v1][i].R * score;
    }

    new_credit[v1] = 0;

    for(int i = 0; i < size-1; i++){
        int index = find_max(new_credit,sp_set);
        sp_set[index] = true;
        for(int w=0; w < size; w++){
            if(!sp_set[w] && new_credit[index] * edges[index][w].R > new_credit[w]){
                new_credit[w] = (int)(new_credit[index] * edges[index][w].R);
            }
        }
    }
    cout << new_credit[v2] << endl;
}

int Graph::find_min(int dist[],bool sp[]){
    int min = INT_MAX - 1;
    int index = 0;
    for(int j = 0; j < size; j ++){
        if(sp[j] == false && dist[j] < min){
            min = dist[j];
            index = j;
        }
    }
    return index;
}

int Graph::find_max(int dist[],bool sp[]){
    double max =  -1;
    int index = 0;
    for(int j = 0; j < size; j ++){
        if(sp[j] == false && dist[j] > max){
            max = dist[j];
            index = j;
        }
    }
    return index;
}

void Graph::map(){
    int ans = 0;
    int dist[size+1];
    int parent[size+1];
    bool sp_set[size+1];
    for(int i = 0; i < size; i++){
        sp_set[i] = false;
        dist[i] = INT_MAX;
        parent[i] = INT_MAX;
    }
    sp_set[0] = true;
    dist[0] = 0;
    parent[0] = 0;
    for(int i = 0; i < size; i++){
        int index = find_min(dist,sp_set);
        sp_set[index] = true;
        for(int w = 0; w < size; w++){
            if(!sp_set[w] && edges[index][w].W < dist[w]){
                dist[w] = edges[index][w].W;
                parent[w] = index;
            }
        }
    }
    for(int i = 0; i < size; i++){
        if(sp_set[i] == false){
            cout << "Error\n";
            return;
        }
    }
    for(int i = 1; i < size; i++){
        ans += edges[parent[i]][i].W;
    }
    cout <<ans << endl;
}

int main(void){
    Graph g;
    int size;
    string cmd;
    cin >> size;
    g.size = size;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            g.edges[i][j].W = INT_MAX; 
            g.edges[i][j].R = 0;
        }
    }
    while(cin >> cmd){
        int v1,v2,w,score,limit;
        double r;
        if(cmd[0] == 'A'){
            cin >> v1 >> v2 >> w >> r;
            g.Add(v1, v2, w, r);
        }
        else if(cmd[0] == 'D'){
            cin >> v1 >> v2;
            g.Delete(v1,v2);
        }
        else if(cmd[0] == 'S'){
            cin >> v1 >> v2;
            g.shortest(v1,v2);
        }
        else if(cmd[0] == 'M'){
            g.map();
        }
        else if(cmd == "CreditExchange"){
            cin >> v1 >> v2 >> score;
            g.credit(v1, v2, score);
        }
        else if(cmd == "CreditExchange2"){
            cin >> v1 >> v2 >> score >> limit;
            max_credit = 0;
            g.credit2(v1, v2, score,limit);
            cout << max_credit << '\n';
        }
        else if(cmd[0] == 'I'){
            g.important_bus();
        }
    }
}
