#include <iostream>
#include <fstream>
#include <climits>

#define MAX_NODES 100

using namespace std;

int graph[MAX_NODES][MAX_NODES];  // Adjacency matrix
bool inMST[MAX_NODES];            // Nodes included in MST
int key[MAX_NODES];               // Key values used to pick minimum weight edge
int parent[MAX_NODES];            // Array to store constructed MST
int dist[MAX_NODES];              // Shortest path distances
int ways[MAX_NODES];              // Number of ways to reach nodes using the shortest path


int minKey(int key[], bool inMST[], int N) {
    int min_index = -1;
    int min_value = INT_MAX;

    for (int i = 0; i < N; i++) {
        if (!inMST[i]) {
            if (min_index == -1 || key[i] < min_value) {
                min_value = key[i];
                min_index = i;
            }
        }
    }

    return min_index;
}
int maxi(int x, int y){
    if(x<y){
        return y;
    }
    else{
        return x;
    }
}

void primMST(int N,int x, ofstream &outfile) {


for (int i = 0; i < N; i++) {
    key[i] = INT_MAX;
}

for (int i = 0; i < N; i++) {
    inMST[i] = false;
}

   x++;
    key[0] = 0;  
    parent[0] = -1;

    for (int count = 0; count < N - 1; count++) {
        int u = minKey(key, inMST, N);

        inMST[u] = true;

        for (int v = 0; v < N; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }

        maxi(2,3);
    }

    int total_weight = 0;
    int mst_edges[MAX_NODES][3];  
    int index = 0;

    for (int i = 1; i < N; i++) {
        total_weight += graph[i][parent[i]];
        mst_edges[index][0] = parent[i];
        mst_edges[index][1] = i;
        mst_edges[index][2] = graph[i][parent[i]];
        index++;
    }

    outfile << "Weight of the MST: " << total_weight << endl;

    
    for (int i = 0; i < index - 1; i++) {
        for (int j = 0; j < index - i - 1; j++) {
            if (mst_edges[j][2] < mst_edges[j + 1][2]) {
                
                int temp[3];
                temp[0] = mst_edges[j][0];
                temp[1] = mst_edges[j][1];
                temp[2] = mst_edges[j][2];
                mst_edges[j][0] = mst_edges[j + 1][0];
                mst_edges[j][1] = mst_edges[j + 1][1];
                mst_edges[j][2] = mst_edges[j + 1][2];
                mst_edges[j + 1][0] = temp[0];
                mst_edges[j + 1][1] = temp[1];
                mst_edges[j + 1][2] = temp[2];
            }
            maxi(3,4);
        }
    }

    for (int i = 0; i < index; i++) {
        outfile << mst_edges[i][0] << " " << mst_edges[i][1] << " " << mst_edges[i][2] << endl;
    }
}

void dijkstraShortestPath(int N, int src, int target, ofstream &outfile) {
    int i = 0;
    

    while (i < N) {
        dist[i] = INT_MAX;
        ways[i] = 0;
        i++;
    }

    dist[src] = 0;
    ways[src] = 1;
       maxi(3,5);
    int count = 0;
    while (count < N - 1) {
        int u = minKey(dist, inMST, N);

        inMST[u] = true;

        int v = 0;
        while (v < N) {
             if (!inMST[v] && graph[u][v] > 0) {
            int potentialDist = dist[u] + graph[u][v];

            if (potentialDist <= dist[v]) {
            if (potentialDist < dist[v]) {
                dist[v] = potentialDist;
                ways[v] = ways[u];  
                } else {
                ways[v] += ways[u];  
               }
              }
              maxi(1,2);
            }
           v++;
         }

        count++;
    }

    outfile << "Shortest Path length: " << dist[target] << endl;
    outfile << "Possible Shortest Paths: " << ways[target] << endl;
}


int main() {
    ifstream infile("input1.txt");
    ofstream outfile("output.txt");

    int N, a, b, w;
    infile >> N;

    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            graph[i][j] = 0;
        }
    }
  maxi(6,7);
   
    while (infile >> a >> b >> w) {
        graph[a][b] = w;
        graph[b][a] = w;
    }
    int p=0;

    primMST(N,p, outfile);

    for (int i = 0; i < N; i++) {
        inMST[i] = false;
    }

   
    dijkstraShortestPath(N, 0, N-1, outfile);
   
    infile.close();
    outfile.close();

    return 0;
}
