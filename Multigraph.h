//
// Created by Szymon Markiewicz on 13/11/2023.
//

#include <cstring>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#ifndef AAC_MULTIGRAPH_H
#define AAC_MULTIGRAPH_H

class Multigraph {
    // Number of vertices
    int verticesNo;

    // Adjacency matrix of a graph
    int **adjMatrix;

    // Methods
    int getSize(); // Get basic multigraph size

    public:
        // Constructor
        explicit Multigraph(int _verticesNo);

        // Multigraph generateGraphFromFile(std::string _filePath);

        static Multigraph createAssociationGraph(Multigraph multigraph1, Multigraph multigraph2);

        //set entry of the adjacency matrix

        int setAdjMatrixEntry(int rowNum, int colNum, int value);

        // print content of the adjacency matrix

        void print();


};

#endif //AAC_MULTIGRAPH_H
