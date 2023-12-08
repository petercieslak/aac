#include "main.h"
#include "Multigraph.cpp"
#include "MultigraphReader.cpp"
#include "MultigraphMetricService.cpp"
#include <cstdlib>
#include <list>
#include <iostream> // Include iostream for console output
#include <chrono>
//#include <windows.h>
#include <unistd.h>
using namespace std::chrono;

int main() {
    std::list<Multigraph> multigraphs;
    std::string filePath;
    MultigraphReader reader;

    do {
        cout << "Enter the name of the file containing the multigraphs (file has to be in the same directory as the .exe file)" << endl;
        string fileName;
        cin >> fileName;
        filePath = fileName; // Hardcoded file path

        multigraphs = reader.readMultigraphsFromFile(filePath); // Read multigraphs from file

        if (multigraphs.empty()) {
            cout << "Multigraph file could not be located" << endl;
            cout << "Press any key to try again" << endl;
            getchar();
            getchar();
        }
    } while (multigraphs.empty());


    std::vector<Multigraph> multigraphsVectorList;

    cout << "-----------MAXIMUM CLIQUE-----------" << endl;

    int i = 1;
    // Obtain maximum clique for all multigraphs
    for (Multigraph multigraph : multigraphs) {
        // Implement a function in Multigraph class to print the graph details
        vector<int> startingClique;

        cout << i << ". Multigraph" << endl;

        auto start = high_resolution_clock::now();
        multigraph.maximumCliqueExact(startingClique, multigraph.verticesInGraph());
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "[Maximum Clique Algorithm - Exact] Time taken: "
            << duration.count() << " microseconds"
            << endl;

        start = high_resolution_clock::now();
        multigraph.maximumCliqueApproximation();
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "[Maximum Clique Algorithm - Approximation] Time taken: "
             << duration.count() << " microseconds"
             << endl;

        multigraph.printClique();
        multigraphsVectorList.push_back(multigraph);

        i += 1;
    }

    cout << "------MAXIMUM COMMON SUBGRAPH------" << endl;

    cout << "Graphs being considered: " << endl;
    multigraphsVectorList[0].printAdjacencyMatrix();
    multigraphsVectorList[1].printAdjacencyMatrix();

    cout << "Exact algorithm..." << endl;
    auto start = high_resolution_clock::now();
    Multigraph associationGraph = Multigraph::maximumCommonSubgraph(true, multigraphsVectorList[0], multigraphsVectorList[1]);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "[Maximum Common Subgraph Algorithm - Exact] Time taken: "
         << duration.count() << " microseconds"
         << endl;

    cout << "Association graph..." << endl;
    associationGraph.printAdjacencyMatrix();

    cout << "Max common subgraph (Maximum Clique of the association graph)..." << endl;
    associationGraph.printClique();

    cout << "Approximation algorithm..." << endl;
    start = high_resolution_clock::now();
    Multigraph associationGraphApprox = Multigraph::maximumCommonSubgraph(false, multigraphsVectorList[0], multigraphsVectorList[1]);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "[Maximum Common Subgraph Algorithm - Approximation] Time taken: "
         << duration.count() << " microseconds"
         << endl;

    cout << "Association graph..." << endl;
    associationGraphApprox.printAdjacencyMatrix();

    cout << "Max common subgraph (Maximum Clique of the association graph)..." << endl;
    associationGraphApprox.printClique();

    cout << "------------METRIC------------" << endl;

    MultigraphMetricService mms = MultigraphMetricService();
    cout << "Exact algorithm..." << endl;
    start = high_resolution_clock::now();
    Multigraph multigraph1 = multigraphs.front();
    multigraphs.pop_front();
    Multigraph multigraph2 = multigraphs.front();
    mms.calculateGraphEditDistance(multigraph1, multigraph2);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "[Graph Edit Distance Algorithm - Exact] Time taken: "
         << duration.count() << " microseconds"
         << endl;

    cout << "Approximation algorithm..." << endl;
    start = high_resolution_clock::now();
    mms.calculateGraphEditDistanceApproximation(multigraph1, multigraph2);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "[Graph Edit Distance Algorithm - Approximation] Time taken: "
         << duration.count() << " microseconds"
         << endl;

    sleep(2);
    cout << "Press key to continue..." << endl;
    getchar();
    getchar();

    return EXIT_SUCCESS;
}
