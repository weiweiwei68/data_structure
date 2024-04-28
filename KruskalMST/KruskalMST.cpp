#include <algorithm>
#include <iomanip> // for setw()
#include <iostream>
#include <list>
#include <vector>

struct Edge {
    int weight, from, to;
    char index;
    Edge(){};
    Edge(int u, int v, char idx, int w) : from(u), to(v), index(idx), weight(w){};
};

class GraphMST {
  private:
    int numVertex;
    std::vector<std::vector<int>> adjMatrix;
    std::vector<std::vector<char>> idx_adjMatrix;

  public:
    GraphMST() : numVertex(0){};
    GraphMST(int n) : numVertex(n) {
        adjMatrix.resize(numVertex);
        idx_adjMatrix.resize(numVertex);
        for (int i = 0; i < numVertex; i++) {
            adjMatrix[i].resize(numVertex);
            idx_adjMatrix[i].resize(numVertex);
        }
    }
    void AddEdge(int from, int to, char idx, int weight);

    std::vector<struct Edge> KruskalMST();
    void GetSortedEdge(std::vector<struct Edge>& vec);
    void display_matrix();
    //void printArray(std::vector<struct Edge>& arr);
    friend int FindSetCollapsing(int* subset, int i);
    friend void UnionSet(int* subset, int x, int y);
};

// Add edges
void GraphMST::AddEdge(int from, int to, char idx, int weight) {
    adjMatrix[from][to] = weight;
    idx_adjMatrix[from][to] = idx;
}

void GraphMST::display_matrix() {
    char st = 'A';
    std::cout << "  ";
    for (int i = 0; i < numVertex; ++i) {
        char label = st + i;
        std::cout << label << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < numVertex; ++i) {
        char label = st + i;
        std::cout << label << " ";
        for(int j = 0; j < numVertex; ++j) {
                if (adjMatrix[i][j] == NULL) {
                    std::cout << "X" << " ";
                } else {
                    std::cout << adjMatrix[i][j] << " ";
                }
        }
        std::cout << "\n";
    }
}

// Use recursion for collapsing
int FindSetCollapsing(int* subset, int i) {

    // Find the root of the subset to which element i belongs
    int root;
    for (root = i; subset[root] >= 0; root = subset[root])
        ;
    // Path compression: Update the parent pointers to point directly to the
    // root
    while (i != root) {
        int parent = subset[i];
        subset[i] = root;
        i = parent;
    }

    return root;
}

void UnionSet(int* subset, int x, int y) {

    int xroot = FindSetCollapsing(subset, x),
        yroot = FindSetCollapsing(subset, y);

    // Compare by rank, more negative values indicate more elements in the set,
    // so smaller values represent more elements
    // xroot, yroot's subset[] is always negative

    // If x has more elements or equal, set x as the root
    if (subset[xroot] <= subset[yroot]) {
        subset[xroot] += subset[yroot];
        subset[yroot] = xroot;

    }
    // if (subset[xroot] > subset[yroot]), indicates y has more elements
    else {
        subset[yroot] += subset[xroot];
        subset[xroot] = yroot;
    }
}

std::vector<struct Edge> GraphMST::KruskalMST() {

    std::vector<struct Edge> increaseWeight;
    GetSortedEdge(increaseWeight);
    return increaseWeight;
}

void printMST(std::vector<struct Edge>& increaseWeight) {

    // Check if adding this edge will create a cycle,
    // if not, add this edge to edgeSetMST and handle the union of disjoint sets
    // //Initialize subset
    struct Edge* edgeSetMST = new struct Edge[sizeof(increaseWeight) - 1];
    int edgeSetCount = 0;
    int subset[sizeof(increaseWeight)];
    for (int i = 0; i < sizeof(increaseWeight); i++) {
        subset[i] = -1;
    }
    for (int i = 0; i < increaseWeight.size(); i++) {
        // your code goes here
        int root_from = FindSetCollapsing(subset, increaseWeight[i].from);
        int root_to = FindSetCollapsing(subset, increaseWeight[i].to);
        if (root_from != root_to) {
            std::cout << "(" << increaseWeight[i].index << ", " << increaseWeight[i].weight << ")" << std::endl;
            edgeSetMST[edgeSetCount++] = increaseWeight[i];
            UnionSet(subset, root_from, root_to);
        }else {
            std::cout << "(" << increaseWeight[i].index << ", " << increaseWeight[i].weight << ") is ignored" << std::endl;
        }
    }
}

void swap(Edge& a, Edge& b)
{
	Edge temp;
	temp = a;
	a = b;
	b = temp;
}
static int num_of_change = 0;
void printArray(std::vector<struct Edge>& arr) {
    std::cout << "step " << num_of_change << ":";
    for (int i = 0; i < sizeof(arr); i++) {

        std::cout << "(" << arr[i].index << ", " << arr[i].weight << ")";
    }
    ++num_of_change;
    std::cout << std::endl;
}
// Hoare partition scheme Quicksort
void quickSort(std::vector<struct Edge>& arr, int left, int right)
{
	if (left < right)
	{
	    printArray(arr);
		int pivot = arr[right].weight;//安砞pivot程竚
		int l = left - 1;
		int r = right;


		while (1)
		{
			while (l < right && arr[++l].weight <= pivot);//тpivot计竚
			while (r > 0 && arr[--r].weight >= pivot);//オтpivot计竚

			if (l >= r)//絛瞅ずpivot娩⊿Τゑpivot计,はぇョ礛
			{
				break;
			}
            //ゑpivot计簿娩ゑpivot计传オ娩
			//code
			swap(arr[l], arr[r]);
			//cout << arr[l];


		}
		//盢pivot簿い丁
    	//code
    	swap(arr[right], arr[l]);
    	//PrintArray(arr);

		quickSort(arr, left, l - 1);//オ计暗患癹
		quickSort(arr, l + 1, right);//计暗患癹

	}
}

//Get data of edges and sort
void GraphMST::GetSortedEdge(std::vector<struct Edge>& edgeArr) {

    for (int i = 0; i < numVertex - 1; i++) {
        for (int j = i + 1; j < numVertex; j++) {
            if (adjMatrix[i][j] != 0) {
                edgeArr.push_back(Edge(i, j, idx_adjMatrix[i][j], adjMatrix[i][j]));
            }
        }
    }

    quickSort(edgeArr, 0, edgeArr.size() - 1);
}

int main() {
    GraphMST chipmunk(8);
    chipmunk.AddEdge(0, 1, 'a', 7);
    chipmunk.AddEdge(1, 0, 'a', 7);
    chipmunk.AddEdge(0, 2, 'b', 3);
    chipmunk.AddEdge(2, 0, 'b', 3);
    chipmunk.AddEdge(0, 3, 'c', 1);
    chipmunk.AddEdge(3, 0, 'c', 1);
    chipmunk.AddEdge(1, 5, 'd', 7);
    chipmunk.AddEdge(5, 1, 'd', 7);
    chipmunk.AddEdge(2, 4, 'e', 7);
    chipmunk.AddEdge(4, 2, 'e', 7);
    chipmunk.AddEdge(3, 4, 'f', 6);
    chipmunk.AddEdge(4, 3, 'f', 6);
    chipmunk.AddEdge(3, 6, 'g', 7);
    chipmunk.AddEdge(6, 3, 'g', 7);
    chipmunk.AddEdge(4, 5, 'h', 6);
    chipmunk.AddEdge(5, 4, 'h', 6);
    chipmunk.AddEdge(4, 6, 'i', 5);
    chipmunk.AddEdge(6, 4, 'i', 5);
    chipmunk.AddEdge(4, 7, 'j', 2);
    chipmunk.AddEdge(7, 4, 'j', 2);
    chipmunk.AddEdge(5, 7, 'k', 5);
    chipmunk.AddEdge(7, 5, 'k', 5);
    chipmunk.AddEdge(6, 7, 'l', 4);
    chipmunk.AddEdge(7, 6, 'l', 4);
    std::cout << "Q1: \n";
    std::cout << "Adjacency matrix: \n";
    chipmunk.display_matrix();
    std::cout << "------------------------\n";

    std::cout << "Q2: \n";
    std::vector<struct Edge> IncreasingEdgeArr = chipmunk.KruskalMST();
    std::cout << "------------------------\n";

    std::cout << "Q3: \n";
    printMST(IncreasingEdgeArr);
    std::cout << "------------------------\n";

}
