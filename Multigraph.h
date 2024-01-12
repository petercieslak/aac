//
// Created by Szymon Markiewicz on 13/11/2023.
//

#include <cstring>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <numeric>
#include <tuple>
#ifndef AAC_MULTIGRAPH_H
#define AAC_MULTIGRAPH_H

using namespace std;

class Multigraph {
    // Number of vertices
    int verticesNo;

    // Adjacency matrix of a graph
    int **adjMatrix;

    // Methods
    int getSize(); // Get basic multigraph size

    int getSubsetSize(const vector<int>& vertices);

    int getEdgeWeight(vector<int> vertices);

    public:

        vector<int> maxClique;

        vector<int> maxCliqueApproximation;

        // Constructor
        explicit Multigraph(int _verticesNo);

        static Multigraph createAssociationGraph(const Multigraph& multigraph1, const Multigraph& multigraph2);

        // find maximum clique for a graph - exact solution, exponential time
        void maximumCliqueExact(vector<int> currentClique, vector<int> adjacentVertices);

        // find maximum clique for a graph - approximation, polynomial time
        void maximumCliqueApproximation();

        // find maximum common subgraph of two graphs
        static tuple<Multigraph, Multigraph, Multigraph, vector<int>, vector<int>> maximumCommonSubgraph(bool exact, const Multigraph& multigraph1, const Multigraph& multigraph2);

        static tuple<Multigraph, Multigraph, Multigraph, vector<int>, vector<int>> recoverExactGraph(const vector<int>& _maxClique, const Multigraph& multigraph1, const Multigraph& multigraph2);

        bool isSubset(vector<int> potentialSubset, vector<int> fullSet);

        int getVertexDegree(int vertex);
        // find neighbours of some vertex in the graph
        vector<int> findNeighbours(int vertex);
        
        // return all vertices
        vector<int> verticesInGraph();

        void printCliqueExact();

        void printCliqueApprox();

        void printAdjacencyMatrix();

        void printWithMissingVertices(vector<int> allowedVertices);

        //set entry of the adjacency matrix

        int setAdjMatrixEntry(int rowNum, int colNum, int value);

        // print content of the adjacency matrix

        void print();

        int getVerticesNo();

        void addEmptyVertices(int amount);

        int getVertex(int colIndex, int rowIndex);


};

#endif //AAC_MULTIGRAPH_H
