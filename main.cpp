#include "main.h"
#include "Multigraph.cpp"
#include "MultigraphReader.cpp"
#include "MultigraphMetricService.cpp"
#include <cstdlib>
#include <list>
#include <iostream> // Include iostream for console output
#include <chrono>
using namespace std::chrono;

int main() {
    std::string filePath = "./multigraphs6x6"; // Hardcoded file path

    MultigraphReader reader; // Create an instance of MultigraphReader

    std::list<Multigraph> multigraphs = reader.readMultigraphsFromFile(filePath); // Read multigraphs3x3 from file

    std::vector<Multigraph> multigraphsVectorList;

    cout << "----MAXIMUM CLIQUE + APPROXIMATION----" << endl;

    // Print the multigraphs3x3 to the console
    for (Multigraph multigraph : multigraphs) {
        // Implement a function in Multigraph class to print the graph details
        vector<int> startingClique;

        auto start = high_resolution_clock::now();
        multigraph.maximumCliqueExact(startingClique, multigraph.verticesInGraph());
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "[Maximum Clique Exact Algorithm] Time taken: "
            << duration.count() << " microseconds"
            << endl;

        start = high_resolution_clock::now();
        multigraph.maximumCliqueApproximation();
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "[Maximum Clique Approximation Algorithm] Time taken: "
             << duration.count() << " microseconds"
             << endl;

        multigraph.printClique();
        multigraphsVectorList.push_back(multigraph);
    }

    cout << "----MAXIMUM COMMON SUBGRAPH----" << endl;

    cout << "Graphs being considered: " << endl;
    multigraphsVectorList[0].printAdjacencyGraph();
    multigraphsVectorList[1].printAdjacencyGraph();

    auto start = high_resolution_clock::now();
    Multigraph associationGraph = Multigraph::maximumCommonSubgraph(true, multigraphsVectorList[0], multigraphsVectorList[1]);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "[Maximum Common Subgraph Exact Algorithm] Time taken: "
         << duration.count() << " microseconds"
         << endl;

    cout << "Association graph..." << endl;
    associationGraph.printAdjacencyGraph();

    cout << "Max common subgraph..." << endl;
    associationGraph.printClique();

    cout << "----------METRIC-----------" << endl;

    MultigraphMetricService mms = MultigraphMetricService();

    start = high_resolution_clock::now();
    Multigraph multigraph1 = multigraphs.front();
    multigraphs.pop_front();
    Multigraph multigraph2 = multigraphs.front();
    mms.calculateGraphEditDistance(multigraph1, multigraph2);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "[Graph Edit Distance Algorithm] Time taken: "
         << duration.count() << " microseconds"
         << endl;

    return EXIT_SUCCESS;
}
