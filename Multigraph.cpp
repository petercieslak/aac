//
// Created by Szymon Markiewicz on 13/11/2023.
//

#include <cstring>
#include <fstream>
#include <string>
#include "Multigraph.h"

class Multigraph {
    // Number of vertices
    int verticesNo;

    // Adjacency matrix of a graph
    int **adjMatrix;

    // File from which to generate the graph
    std::ifstream multigraphFile;

    // Constructor
    explicit Multigraph(int _verticesNo);

    // Methods
    int getSize(); // Get basic multigraph size

    public:
        Multigraph generateGraphFromFile(std::string _filePath);

        static Multigraph createAssociationGraph(Multigraph multigraph1, Multigraph multigraph2);


};

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
 * Create an adjacency graph by reading a local file.
 *
 * Parameters:
 *      _filePath - path to the file containing graph data
 * */
Multigraph Multigraph::generateGraphFromFile(std::string _filePath) {
    multigraphFile.open(_filePath);

//    ...
//    Czytanie grafu here, zapisujemy do verticesNo i adjMatrix
//    ...

    return Multigraph(0);
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



