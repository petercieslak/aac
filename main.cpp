//
// Created by Szymon Markiewicz on 13/11/2023.
//

#include "main.h"
#include "Multigraph.cpp"
#include "MultigraphReader.cpp"
#include <cstdlib>
#include <list>

int main(int argc, char* argv[]) {
    MultigraphReader multigraphReader = MultigraphReader();
    std::list<Multigraph> multigraphs = multigraphReader.readMultigraphsFromFile("./multigraphs");

    for (auto & multigraph : multigraphs){
        multigraph.print();
    }

    return EXIT_SUCCESS;
}