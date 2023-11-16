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
                    // Isomorphism condition (altered for multigraphs) - check whether there are any outgoing edges from checked vertex in second graph,
                    // if so take minimum and store it in association graph
                    if (multigraph2.adjMatrix[j][k] >= 1)
                        // Store the edges and their count
                        associationMultigraph.adjMatrix[j][k] = std::min(multigraph1.adjMatrix[i][j], multigraph2.adjMatrix[j][k]);
                }
        }
    }

    return associationMultigraph;
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



