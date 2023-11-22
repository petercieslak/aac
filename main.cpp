//
// Created by Szymon Markiewicz on 13/11/2023.
//

#include "main.h"
#include "Multigraph.cpp"
#include "MultigraphReader.cpp"
#include "MultigraphMetricService.cpp"
#include <cstdlib>
#include <list>

int main(int argc, char* argv[]) {
    MultigraphReader multigraphReader = MultigraphReader();
    std::list<Multigraph> multigraphs = multigraphReader.readMultigraphsFromFile("./multigraphs");

    // for (auto & multigraph : multigraphs){
    //     multigraph.print();
    // }

    MultigraphMetricService mms = MultigraphMetricService();

    Multigraph multigraph1 = multigraphs.front();
    multigraphs.pop_front();
    Multigraph multigraph2 = multigraphs.front();
    mms.calculateGraphEditDistance(multigraph1, multigraph2);

    return EXIT_SUCCESS;
}