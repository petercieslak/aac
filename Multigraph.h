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

    int getEdgeWeight(vector<int> vertices);

    public:

        vector<int> maxClique;

        // Constructor
        explicit Multigraph(int _verticesNo);

        // Multigraph generateGraphFromFile(std::string _filePath);

        static Multigraph createAssociationGraph(Multigraph multigraph1, Multigraph multigraph2);

        // find maximum clique for a graph - exact solution, exponential time
        void maximumCliqueExact(vector<int> currentClique, vector<int> adjacentVertices);

        // find neighbours of some vertex in the graph
        vector<int> findNeighbours(int vertex);
        
        // return all vertices
        vector<int> verticesInGraph();

        void printClique();

        void printAdjacencyGraph();

        //set entry of the adjacency matrix

        int setAdjMatrixEntry(int rowNum, int colNum, int value);

        // print content of the adjacency matrix

        void print();


};

#endif //AAC_MULTIGRAPH_H
