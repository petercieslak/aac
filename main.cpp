#include "main.h"
#include "Multigraph.cpp"
#include "MultigraphReader.cpp"
#include "MultigraphMetricService.cpp"
#include <cstdlib>
#include <list>
#include <iostream> // Include iostream for console output

int main() {
    std::string filePath = "./multigraphs"; // Hardcoded file path

    MultigraphReader reader; // Create an instance of MultigraphReader

    std::list<Multigraph> multigraphs = reader.readMultigraphsFromFile(filePath); // Read multigraphs from file

    std::vector<Multigraph> multigraphsVectorList;
    // Print the multigraphs to the console
    for (Multigraph multigraph : multigraphs) {
        // Implement a function in Multigraph class to print the graph details
        multigraph.print(); // Assuming a function called print() exists in Multigraph class
        vector<int> startingClique;


        multigraph.maximumCliqueExact(startingClique, multigraph.verticesInGraph());
        multigraph.printClique();

        multigraphsVectorList.push_back(multigraph);
    }

    cout << "----MAXIMUM COMMON SUBGRAPH----" << endl;

    cout << "Graphs being considered: " << endl;
    multigraphsVectorList[0].printAdjacencyGraph();
    multigraphsVectorList[1].printAdjacencyGraph();

    cout << "Computing association graph..." << endl;
    Multigraph associationGraph = Multigraph::createAssociationGraph(multigraphsVectorList[0], multigraphsVectorList[1]);
    associationGraph.printAdjacencyGraph();

    vector<int> startingClique;
    associationGraph.maximumCliqueExact(startingClique, associationGraph.verticesInGraph());
    cout << "Computing max common subgraph..." << endl;
    associationGraph.printClique();

    cout << "----------METRIC-----------" << endl;

    MultigraphMetricService mms = MultigraphMetricService();

    Multigraph multigraph1 = multigraphs.front();
    multigraphs.pop_front();
    Multigraph multigraph2 = multigraphs.front();
    mms.calculateGraphEditDistance(multigraph1, multigraph2);

    return EXIT_SUCCESS;
}
