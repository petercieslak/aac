#include "Multigraph.h"
/*
 * Initialize empty adjacency matrix for a graph.
 *
 * Parameters:
 *      _verticesNo - number of vertices in a graph
 * */

using namespace std;

Multigraph::Multigraph(int _verticesNo)
{
    verticesNo = _verticesNo;
    adjMatrix = new int*[_verticesNo];

    for (int i = 0; i < _verticesNo; i++) {
        adjMatrix[i] = new int[_verticesNo];
        memset(adjMatrix[i], 0, _verticesNo * sizeof(int));
    }
}

/*
 * Get any graph size. We define it as the sum of the number of vertices and the number of all edges.
 * */
int Multigraph::getSize() {
    int noOfEdges = 0;
    for (int i = 0; i < verticesNo; i++) {
        for (int j = 0; j < verticesNo; j++) {
            noOfEdges += adjMatrix[i][j];
        }
    }

    return verticesNo + noOfEdges;
}

int Multigraph::getSubsetSize(const vector<int>& vertices) {
    int noOfEdges = 0;
    for (auto i : vertices) {
        for (auto j: vertices) {
            noOfEdges += adjMatrix[i][j];
        }
    }

    return vertices.size() + noOfEdges;
}

/*
 * Get weight of edges for given subgraph 
 * */
int Multigraph::getEdgeWeight(vector<int> vertices) {
    int result = 0;
    
    for (int i = 0; i < verticesNo; i++) {
        for (int j = 0; j < verticesNo; j++) {
            for(int v:vertices) {
                if((v == i || v == j) && i != j) {
                    result += adjMatrix[i][j];
                }
            }
            
        }
    }
    return result;
}

/*
 * Function to create association graph of two directed multigraphs3x3. We can use this to obtain the maximum common
 * subgraph of two graphs - it will be the maximum clique of this association graph (Durand-Pasari algorithm)
 *
 * Parameters:
 *      multigraph1 - first directed multigraph
 *      multigraph2 - second directed multigraph
 * */
Multigraph Multigraph::createAssociationGraph(const Multigraph& multigraph1, const Multigraph& multigraph2) {
    // Vertices number of new multigraph will be the multiplication of |V1| and |V2|
    int V1 = multigraph1.verticesNo;
    int V2 = multigraph2.verticesNo;

    Multigraph associationMultigraph = Multigraph(V1 * V2);

    for (int i = 0; i < V1; i++) {
        for (int j = 0; j < V2; j++) {
            for (int x = 0; x < V1; x++) {
                if (multigraph1.adjMatrix[i][x] >= 1){
                    for (int y = 0; y < V2; y++){
                        if (multigraph2.adjMatrix[j][y] >= 1){
                            associationMultigraph.adjMatrix[i*multigraph2.verticesNo + j][x*multigraph2.verticesNo + y] =
                                    std::min(multigraph1.adjMatrix[i][x], multigraph2.adjMatrix[j][y]);
                        }
                    }
                }
            }
        }
    }

    return associationMultigraph;
}

Multigraph Multigraph::maximumCommonSubgraph(bool exact, const Multigraph& multigraph1, const Multigraph& multigraph2) {
    Multigraph associationGraph = Multigraph::createAssociationGraph(multigraph1, multigraph2);

    vector<int> startingClique;
    if (exact)
        associationGraph.maximumCliqueExact(startingClique, associationGraph.verticesInGraph());
    else
        associationGraph.maximumCliqueApproximation();

    return associationGraph;
}

void Multigraph::maximumCliqueExact(vector<int> currentClique, vector<int> adjacentVertices) {
    if(getSubsetSize(currentClique) > getSubsetSize(maxClique)) {
        maxClique = currentClique;
    }

    if((currentClique.size() + adjacentVertices.size()) >= maxClique.size()) {
        for(int v:adjacentVertices) {
            // delete v from adjacentVertices
            auto it = find(adjacentVertices.begin(), adjacentVertices.end(), v);
            if (it != adjacentVertices.end()) {
                adjacentVertices.erase(it);
            }

            // add v to current clique
            vector<int> tempCurrentClique = currentClique;
            tempCurrentClique.push_back(v);
    
            // intersection between adjacent vertices and neighbours of v
            vector<int> vNeighbours = findNeighbours(v);
            vector<int> tempAdjacentVertices;
            sort(adjacentVertices.begin(), adjacentVertices.end());
            sort(vNeighbours.begin(), vNeighbours.end());
            set_intersection(adjacentVertices.begin(), adjacentVertices.end(), vNeighbours.begin(), vNeighbours.end(), back_inserter(tempAdjacentVertices));

            // recurrence
            maximumCliqueExact(tempCurrentClique, tempAdjacentVertices);

        }
    }
}

void Multigraph::maximumCliqueApproximation() {
    vector<int> verticesOfMultigraph(this->getVerticesNo());
    iota(verticesOfMultigraph.begin(), verticesOfMultigraph.end(), 0);

    sort(verticesOfMultigraph.begin(), verticesOfMultigraph.end(), [this](int a, int b) {
        return getVertexDegree(a) < getVertexDegree(b);
    });

    vector<int> maxClique;
    while(verticesOfMultigraph.size() != 0){
        vector<int> currentClique;

        for(int v: verticesOfMultigraph){
            if(isSubset(currentClique, findNeighbours(v))) {
                currentClique.push_back(v);
            }
        }

        if (currentClique.size() > maxClique.size() || ((currentClique.size() == maxClique.size()) && (getEdgeWeight(currentClique) > getEdgeWeight(maxClique)))){
            maxClique = currentClique;
        }

        verticesOfMultigraph.erase(std::remove_if(verticesOfMultigraph.begin(), verticesOfMultigraph.end(), [&currentClique](int x) {
            return std::find(currentClique.begin(), currentClique.end(), x) != currentClique.end();
        }), verticesOfMultigraph.end());
    }

    maxCliqueApproximation = maxClique;
}

bool Multigraph::isSubset(vector<int> potentialSubset, vector<int> fullSet) {
    for (int element : potentialSubset) {
        if (find(fullSet.begin(), fullSet.end(), element) == fullSet.end()) {
            return false;
        }
    }
    return true;
}

int Multigraph::getVertexDegree(int vertex) {
    return findNeighbours(vertex).size();
}

vector<int> Multigraph::findNeighbours(int vertex) {
    vector<int> neighbours;

    for(int i=0; i<verticesNo; i++) {
        // for directed graph neighbour needs to have connection in both ways
        if(vertex != i && adjMatrix[vertex][i] != 0 && adjMatrix[i][vertex] != 0) {
            neighbours.push_back(i);
        }
    }

    return neighbours;
}

vector<int> Multigraph::verticesInGraph() {
    vector<int> result;
    for(int i=0; i<verticesNo; i++) {
        result.push_back(i);
    }
    return result;
}

void Multigraph::printClique(){
    sort(maxClique.begin(), maxClique.end()); 
    cout<<"Maximum clique:" <<endl;
    cout << "  ";
    for(int v1: maxClique) {
        cout<<v1<<" ";
    }
    cout << endl;

    for(int v1: maxClique){
        cout << v1 << " ";
        for (int v2: maxClique){
            cout << adjMatrix[v1][v2] << " ";
        }
        cout<<endl;
    }
    cout << "Size: " << getSubsetSize(maxClique) << endl;

    cout << "-------------------------------------" << endl;

    sort(maxCliqueApproximation.begin(), maxCliqueApproximation.end());
    cout<<"Maximum clique approximation:" <<endl;
    cout << "  ";
    for(int v1: maxCliqueApproximation) {
        cout<<v1<<" ";
    }
    cout << endl;

    for(int v1: maxCliqueApproximation){
        cout << v1 << " ";
        for (int v2: maxCliqueApproximation){
            cout << adjMatrix[v1][v2] << " ";
        }
        cout<<endl;
    }
    cout << "Size: " << getSubsetSize(maxCliqueApproximation) << endl;
    cout << endl;
}

void Multigraph::printAdjacencyMatrix(){
    cout << "Adjacency matrix of a graph:" << endl;
    cout << "  ";
    for (int i=0; i<verticesNo; i++) {
        cout << i << " ";
    }
    cout << endl;
    for (int i=0; i<verticesNo; i++){
        cout << i << " ";
        for (int j=0; j<verticesNo; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Size: " << getSize() << endl;
    cout << endl;
}

int Multigraph::setAdjMatrixEntry(int rowNum, int colNum, int value) {
    adjMatrix[rowNum][colNum] = value;
    // std::cout << "row: " << rowNum << " col: " << colNum << " val: " << value << std::endl;
    return 1;
}

void Multigraph::print() {
    for(int i = 0; i < this->verticesNo; i++) {
        for(int j = 0; j < this->verticesNo; j++) {
            std::cout << "row: " << i << " col: " << j << " val: " << this->adjMatrix[i][j] << std::endl;
        }
    }
}

int Multigraph::getVerticesNo() {
    return this->verticesNo;
}

void Multigraph::addEmptyVertices(int amount) {
    int **resizedAdjMatrix;
    int newSize = amount + verticesNo;
    resizedAdjMatrix = new int*[newSize];

    for (int i = 0; i < newSize; i++) {
        resizedAdjMatrix[i] = new int[newSize];
        memset(resizedAdjMatrix[i], 0, newSize * sizeof(int));
    }

    for (int i = 0; i < verticesNo; i++) {
        for(int j = 0; j < verticesNo; j++) {
            resizedAdjMatrix[i][j] = adjMatrix[i][j];
        }
    }

    for (int i = verticesNo; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            resizedAdjMatrix[i][j] = 0;
            resizedAdjMatrix[j][i] = 0;
        }
    }

    this->adjMatrix = resizedAdjMatrix;
    this->verticesNo = newSize;
}

int Multigraph::getVertex(int colIndex, int rowIndex) {
    return this->adjMatrix[colIndex][rowIndex];
}



