//
// Created by Szymon Markiewicz on 13/11/2023.
//

#include "Multigraph.h"
/*
 * Initialize empty adjacency matrix for a graph.
 *
 * Parameters:
 *      _verticesNo - number of vertices in a graph
 * */
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
 * Function to create association graph of two directed multigraphs. We can use this to obtain the maximum common
 * subgraph of two graphs - it will be the maximum clique of this association graph (Durand-Pasari algorithm)
 *
 * Parameters:
 *      multigraph1 - first directed multigraph
 *      multigraph2 - second directed multigraph
 * */
Multigraph Multigraph::createAssociationGraph(Multigraph multigraph1, Multigraph multigraph2) {
    // Vertices number of new multigraph will be the multiplication of |V1| and |V2|
    Multigraph associationMultigraph = Multigraph(multigraph1.verticesNo * multigraph2.verticesNo);

    for (int i = 0; i < multigraph1.verticesNo; i++) {
        for (int j = 0; j < multigraph1.verticesNo; j++) {
            // Bound to begin checking - if there are no outgoing edges we are not checking
            if (multigraph1.adjMatrix[i][j] >= 1)
                for (int k = 0; k < multigraph2.verticesNo; k++){
                    // Isomorphism condition - check whether the number of outgoing edges is equal, else graphs are not
                    // isomorphic
                    if (multigraph1.adjMatrix[i][j] == multigraph2.adjMatrix[j][k])
                        // Store the edges and their count
                        associationMultigraph.adjMatrix[j][k] = multigraph1.adjMatrix[i][j];
                }
        }
    }

    return associationMultigraph;
}

void Multigraph::maximumCliqueExact(vector<int> currentClique, vector<int> adjacentVertices) {
    
    if(currentClique.size() > maxClique.size() || ((currentClique.size() == maxClique.size()) && (getEdgeWeight(currentClique) > getEdgeWeight(maxClique)))) {
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



