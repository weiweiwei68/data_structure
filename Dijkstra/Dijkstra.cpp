#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <iomanip>

#define v 8 // Number of vertices (vertexNum)
#define maxV INT_MAX
using namespace std;

// Function to translate tupleList into a 2D array
void translateTo2DArray(const vector<pair<char, int>> tupleList[],  int array2D[v][v]) {
    for (int i = 0; i < v; ++i) {
        for (int j = 0; j < v; ++j) {
                array2D[i][j] = maxV;
        }
    }

    for (int i = 0; i < v; ++i) {
        for (int j = 0; j < v; ++j) {
            if (j < tupleList[i].size()) { // Check if the vector has an element at the current index
                int adj_v = tupleList[i][j].first - 'A';
                int adj_w = tupleList[i][j].second;
                array2D[i][adj_v] = adj_w; // Store the weight in the 2D array
            }
        }
    }
}

char mapIndexToLetter(int i) { return 'A' + i; }

// Function to find the vertex with the minimum distance value,
// from the set of vertices not yet included in the shortest path tree
int miniDist(int dist[], bool isVisit[]) {
    int minIndex = -1; // Indicates that a valid unvisited node is not found
    int minValue = maxV;
    for (int i = 0; i < v; i++) {
        if (!isVisit[i] && dist[i] < minValue) {
            minValue = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

// Function to initialize distance array and isVisit array
void init(int dist[], bool isVisit[], int parent[]) {
    for (int i = 0; i < v; i++) {
        dist[i] = INT_MAX;
        isVisit[i] = false;
        parent[i] = i;
    }
}

// Dijkstra's algorithm to find the shortest paths from a source vertex to all
// other vertices
void DijkstraAlgo(int graph[v][v], int src) {
    int dist[v], parent[v];
    bool isVisit[v];
    init(dist, isVisit, parent);

    // Set the distance of the source vertex to 0
    dist[src] = 0;

    while (true) {
        // Get the current node with the minimum distance value
        int vertex = miniDist(dist, isVisit);
        if (vertex == -1) {
            break; // All nodes have been visited, exit the loop
        }

        isVisit[vertex] = true;

        // Relaxation step
        for (int i = 0; i < v; i++) {
            if (!isVisit[i] && graph[vertex][i] != INT_MAX &&
                dist[i] > dist[vertex] + graph[vertex][i]) {
                dist[i] = dist[vertex] + graph[vertex][i];
                parent[i] = vertex;
            }
        }
        cout << mapIndexToLetter(vertex) << "|";
        for (int i = 0; i < v; ++i) {
            if (dist[i] != maxV) {
                cout << " " << dist[i];
            } else {
                cout << " X";
            }
        }
        cout << endl;
    }
}

void hashfunc (string personlist[], int num, int num_bucket) {
    string* table = new string[num_bucket];
    for (int i = 0; i < num; ++i) {
        int key = personlist[i][0] % 26;
        if (table[key].empty()) {
            table[key] = personlist[i];
        } else {
            key = 0;
            for (char character : personlist[i]) {
                key += character;
            }
            key = key % 26;
            table[key] = personlist[i];
        }
    }
    for (int i = 0; i < num_bucket; ++i) {
        if (i%5 == 0) {cout << endl;}
        cout << setw(2) << i << ":" << setw(8) << table[i] << " | ";
    }
}

int main() {
    // Create a vector of pairs
    vector<pair<char, int>> tupleList[v];

    // Add elements to the vector at each index
    tupleList[0].push_back({'B', 7});
    tupleList[0].push_back({'C', 3});
    tupleList[0].push_back({'D', 1});

    tupleList[1].push_back({'A', 7});
    tupleList[1].push_back({'F', 7});

    tupleList[2].push_back({'A', 3});
    tupleList[2].push_back({'E', 7});

    tupleList[3].push_back({'A', 1});
    tupleList[3].push_back({'E', 6});
    tupleList[3].push_back({'G', 7});

    tupleList[4].push_back({'C', 7});
    tupleList[4].push_back({'D', 6});
    tupleList[4].push_back({'F', 6});
    tupleList[4].push_back({'G', 5});
    tupleList[4].push_back({'H', 2});

    tupleList[5].push_back({'B', 7});
    tupleList[5].push_back({'E', 6});
    tupleList[5].push_back({'H', 5});

    tupleList[6].push_back({'D', 7});
    tupleList[6].push_back({'E', 5});
    tupleList[6].push_back({'H', 4});

    tupleList[7].push_back({'E', 2});
    tupleList[7].push_back({'F', 5});
    tupleList[7].push_back({'G', 4});


    cout << "Q1:" << endl;
    // Access and print the elements
    for (int i = 0; i < v; ++i) {
        cout << mapIndexToLetter(i) << ":";
        for (const auto& tuple : tupleList[i]) {
            cout << " " << tuple.first << "(" << tuple.second << ")";
        }
        cout << endl;
    }
    cout << "-----------------------" << endl;

    cout << "Q2:" << endl;
    int graph[v][v];
    translateTo2DArray(tupleList, graph);
    DijkstraAlgo(graph, 0);
    cout << "-----------------------" << endl;

    cout << "Q3:" << endl;
    string personList[10] = {"Amy","Jim", "Olivia","Noah", "Ava" ,"Roger", "Sophie", "Jackson", "Lucas", "Mia"};
    hashfunc(personList, 10, 26);

    return 0;
}
