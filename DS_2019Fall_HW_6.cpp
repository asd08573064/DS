#include <iostream>
#include <string>
#include <climits>
using namespace std;

class Graph
{
public:
	void Add(int v1, int v2, int w);
	void Delete(int v1, int v2);
	void MDST(string cmd);
	void SOSPD();
	void floyd();
	void initialize();
	void sort();
	int find_min(double dist[],bool sp[]);
	int edges[101][101];
	int dist[101][101];
	int dist_for_check[101][101];
	int preprocess[101][101];
	int R[101][101];
	bool check[101];
	int size;

};

void Graph::initialize(){
	for(int i = 0; i < size; i++){
		check[i] = false;
		for(int j = 0; j < size; j++){
			R[i][j] = j;
			edges[i][j] = INT_MAX;
			dist[i][j] = INT_MAX;
			if(i == j){
				edges[i][j] = 0;
				dist[i][j] = 0;
			}
		}
	}
}

void Graph::floyd(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			dist[i][j] = edges[i][j];
		}
	}
	for(int k = 0; k < size; k++){
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				if(dist[i][j] > dist[i][k]+dist[k][j] && (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)){
					dist[i][j] = dist[i][k]+dist[k][j];
				}
			}
		}
	}
}

void Graph::sort(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			dist_for_check[i][j] = dist[i][j];
			R[i][j] = j;
		}
	}
	for(int k = 0; k < size; k++){
		for(int i = 0; i < size-1; i++){
			for(int j = 0; j < size-1-i; j++){
				if(dist[i][j] != INT_MAX && dist_for_check[k][j] < dist_for_check[k][j+1]){
					int tmp = dist_for_check[k][j];
					dist_for_check[k][j] = dist_for_check[k][j+1];
					dist_for_check[k][j+1] = tmp;
					tmp = R[k][j];
					R[k][j] = R[k][j+1];
					R[k][j+1] = tmp;
				}
			}
		}
	}
}

void Graph::Add(int v1, int v2, int w){
	edges[v1][v2] = edges[v2][v1] = w;
}

void Graph::Delete(int v1, int v2){
	edges[v1][v2] = edges[v2][v1] = INT_MAX;
}

int Graph::find_min(double dist[],bool sp[]){
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


void Graph::MDST(string cmd){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(dist[i][j] == INT_MAX){
				cout << "Not connected graph\n";
				return;
			}
		}
	}
	double min_ecc = INT_MAX;
	int ans_x;
	int ans_y;
	double x,y;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(min_ecc > dist[i][R[i][0]]){
				min_ecc = dist[i][R[i][0]];
				ans_x = ans_y = i;
			}
			if(min_ecc > dist[j][R[j][0]]){
				min_ecc = dist[j][R[j][0]];
				ans_y = ans_x = j;
			}
			for(int a = 0, b = 1; b < size; b++){
				if(dist[j][R[i][b]] > dist[j][R[i][a]]){
					if(((double)dist[i][R[i][b]] + (double)dist[j][R[i][a]] + (double)edges[i][j])/2 < min_ecc){
						min_ecc = ((double)dist[i][R[i][b]] + (double)dist[j][R[i][a]] + (double)edges[i][j]) /2;
						x = min_ecc - dist[i][R[i][b]];
						y = min_ecc - dist[j][R[i][a]];
						ans_x = i;
						ans_y = j;
					}
					a = b;
				}
			}
		}
	}
	if(cmd == "AC"){
		if(ans_y == ans_x){
			cout << ans_x << endl;
		}
		else{
			if(ans_y > ans_x)
				cout << ans_x << ' ' << ans_y << endl;
			else
				cout << ans_y << ' ' << ans_x << endl;
		}
	}
	else if(cmd == "Diameter"){
		cout << 2*min_ecc << endl;
	}
	else{
		double sum = 0;
		double dist_dij[size];
	    bool sp_set[size];
	    for(int i = 0; i < size; i++){
	        sp_set[i] = false;
	        dist_dij[i] = INT_MAX;
	    }
	    dist_dij[ans_x] = x;
	    dist_dij[ans_y] = y;  
	    for(int i = 0; i < size; i++){
	        int index = find_min(dist_dij,sp_set);
	        sp_set[index] = true;
	        for(int w=0; w < size; w++){
	            if(!sp_set[w] && edges[index][w] != INT_MAX && dist_dij[index] + edges[index][w] < dist_dij[w]){
	                dist_dij[w] = dist_dij[index] + edges[index][w];
	            }
	        }
	    }
	    for(int i = 0; i < size; i++){
	    	sum += dist_dij[i];
	    } 
	    cout << sum << endl; 
	}
		
}

int main(void){
	int V;
	Graph G;
	cin >> V;
	string cmd;
	G.size = V;
	G.initialize();
	while(cin >> cmd){
		if(cmd == "Add"){
			int v1,v2,w;
			cin >> v1 >> v2 >> w;
			G.Add(v1,v2,w);
		}
		else if(cmd == "Delete"){
			int v1,v2;
			cin >> v1 >> v2;
			G.Delete(v1,v2);
		}
		else{
			G.floyd();
			G.sort();
			G.MDST(cmd);
		}

	}

}