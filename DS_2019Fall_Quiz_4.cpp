#include <iostream>
#include <climits>
#include <string>
using namespace std;
int edges[1001][1001];
class Graph
{
public:
    Graph() {}
    int size;
    void Add(int v1,int v2,int w);
    void Delete(int v1, int v2);
    void shortest(int v1, int v2);

};


void Graph::shortest(int v1, int v2){
    int dist[size+1];
    int tmp;
    int pi[size];
    for(int i = 0; i < size; i++){
        dist[i] = edges[v1][i];
        pi[i] = v1;
    }
    dist[v1] = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            for(int w = 0; w < size; w++){
                if(j != v1 && dist[j] != INT_MAX && edges[j][w] != INT_MAX && dist[j] + edges[j][w] < dist[w]){
                    dist[w] = dist[j] + edges[j][w];
                    pi[w] = j;
                }
            }
        }
    }
    tmp = dist[v2];
    for(int j = 0; j < size; j++){
        for(int w = 0; w < size; w++){
            if(j != v1 && dist[j] != INT_MAX && edges[j][w] != INT_MAX && dist[j] + edges[j][w] < dist[w]){
                dist[w] = dist[j] + edges[j][w];
            }
        }
    }
    if((dist[v2] != tmp) || dist[v2] != tmp  ||  dist[v2] == INT_MAX){
        cout << "error\n";
        return;
    }
    else{
        int i_ = 1;
        int ans[size+1];
        int find = v2;
        ans[0] = v2;
        while(find != v1){
            ans[i_] = pi[find];
            find = pi[find];
            i_++;
        }
        i_--;
        cout <<tmp << endl;
        while(i_ >= 0){
            if(i_ == 0)
                printf("%d",ans[i_]);
            else
                printf("%d,",ans[i_]);
            i_ --;
        }
        cout << endl;
    }

}

void Graph::Delete(int v1,int v2){
    edges[v1][v2] = INT_MAX;
}



void Graph::Add(int v1, int v2, int w){
    edges[v1][v2] = w;
}

int main(){
    string cmd;
    Graph g;
    int v1,v2;
    int edge;
    cin >> edge;
    g.size = edge;

    for(int i = 0;i < edge + 1; i++){
        for(int j = 0; j < edge + 1; j++){
            if(i == j)
                edges[i][j] = 0;
            else
                edges[i][j] = INT_MAX;
        }
    }
    while(cin >> cmd){
        int w;
        if(cmd[0] == 'A'){
            cin >> v1 >> v2 >> w;
            g.Add(v1,v2,w);
        }
        else if(cmd[0] == 'D'){
            cin >> v1 >> v2;
            g.Delete(v1,v2);
        }
        else if(cmd[0] == 'S'){
            cin >> v1 >> v2;
            g.shortest(v1,v2);

        }
    }
}
