#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <list>

using namespace std;

struct Node {
	int n;
	int cost;
};

inline bool operator>(const Node& lhs, const Node& rhs) {
  return lhs.cost > rhs.cost;
}

vector<vector<int>> result;
vector<vector<int>> path;

vector<vector<struct Node>> matrix;
list<int> cycle;

int nNodes, nEdges, firstNode;
int nNodesCycle = 0;
int tourLength = 0;
bool foundInitial = false;

void dijsktra(int n) {
	priority_queue< struct Node, vector <struct Node> , greater<struct Node> > pq;

    vector<int> dist(nNodes, -1);
    vector<bool> visited(nNodes, false);
    pq.push({n,0});
    dist[n] = 0;
 	
    while (!pq.empty()) {
        int u = pq.top().n;
        pq.pop();

        if (visited[u])
        	continue;

        for (auto & node: matrix[u]) {
            int v = node.n;
            int weight = node.cost;

            if (dist[v] == -1 || dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                path[n][v] = u;
                pq.push({v,dist[v]});
            }
        }
        visited[u] = true;
    }
	
	for (int i = 0; i < nNodes; ++i)
       	result[n][i] = dist[i];
}


void getPath(int x, int y){
	nNodesCycle++;

	if (x == y)
		cout << "Error repeated node" << endl;
	else if (y == -1 || path[x][y] == x) {
		tourLength = tourLength + result[x][y];

		if (!foundInitial)
			foundInitial = (x == firstNode);

		if (!foundInitial)
			cycle.push_back(x);
		else
			cout << x << endl;
	}
	else {
		tourLength = tourLength + result[x][path[x][y]];
		getPath(x,path[x][y]);
		if (!foundInitial)
			foundInitial = (path[x][y] == firstNode);

		if (!foundInitial)
			cycle.push_back(path[x][y]);
		else
			cout << path[x][y] << endl;
	}
}

int main(int argc, char * argv[]) {
	if (argc == 2) {
		if (strcmp(argv[1],"matrix") != 0 && strcmp(argv[1],"path") != 0) {
			cerr << "USE: ./tsp.out [matrix|path]" << endl;
			return -1;
		}
	}
	else{
		cerr << "USE: ./tsp.out [matrix|path]" << endl;
		return -1;
	}

	//Read matrix of the given graph
	cin >> nNodes >> nEdges >> firstNode;

	result.resize(nNodes,vector<int>(nNodes,0));
	path.resize(nNodes,vector<int>(nNodes,0));
	matrix.resize(nNodes,vector<struct Node>());

	int u,v,c;

	for (int i = 0; i < nEdges; i++) {
		cin >> u >> v >> c;
		matrix[u].push_back({v,c});
		matrix[v].push_back({u,c});
	}

	for (int i = 0; i < nNodes; i++)
		dijsktra(i);

	//Return complete matrix
	if (strcmp(argv[1],"matrix") == 0) {
		cout << nNodes << endl;
		for (int i = 0; i < nNodes; i++) {
			for (int j = 0; j < /*i+i*/nNodes ; j++)
				cout << result[i][j] << " ";
			
			cout << endl;
		}
	}
	//Return reconstructed path
	else {
		cin >> nNodes;
		cin >> u;

		//Real tours
		for (int i = 0; i < nNodes - 1; i++ ) {
			cin >> v;
			getPath(u,v);
			u = v;
		}

		for (auto &y : cycle)
			cout << y << endl;
		cout << firstNode << endl;

		//Number of nodes of the tour
		cout << nNodesCycle << endl;
		//Weight of the tour
		cout << tourLength << endl;
	}
	return 0;
}

