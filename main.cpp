#include "main.h"
#include "Multigraph.cpp"
#include "MultigraphReader.cpp"
#include "MultigraphMetricService.cpp"
#include <cstdlib>
#include <list>
#include <iostream> // Include iostream for console output
#include <chrono>
#include <string>
using namespace std::chrono;

int main() {
    std::list<Multigraph> multigraphs;
    std::string filePath;
    MultigraphReader reader1;
    MultigraphReader reader2;
    int files;
    do {
        cout << "How many files do you want to upload? (1 or 2)" << endl;
        cin >> files;
    } while (files != 1 && files != 2);

    for(int i=0; i< files; i++){
        do {
            string message = (i == 0) ? "1st" : "2nd";
            cout << "Enter the absolute path to the " << message << " file containing the multigraph (one per file)" << endl;
            string fileName;
            cin >> fileName;
            filePath = fileName;
            if(i == 0) {
                multigraphs.push_back(reader1.readMultigraphsFromFile(filePath));
            } else {
                multigraphs.push_back(reader2.readMultigraphsFromFile(filePath));
            }

            if (multigraphs.empty()) {
                cout << "Multigraph file could not be located" << endl;
                cout << "Press any key to try again" << endl;
                getchar();
                getchar();
            }
        } while (multigraphs.empty());
    }
    std::vector<Multigraph> multigraphsVectorList;
    multigraphsVectorList.push_back(multigraphs.front());
    multigraphsVectorList.push_back(multigraphs.back());
    
    if(files == 1){
        while(true) {
            cout << "GRAPH CONSIDERED: " << endl << endl;
            multigraphs.front().printAdjacencyMatrix();
            cout << "The first row and the leftmost column correspond to the indices of the vertices." << endl;
            cout << "If a star/dot appears in the adjacency matrix of a graph, it means that this corresponding vertex was removed from the original graph." << endl << endl;
            cout << endl << "What do you want to do? Choose correct option" << endl;
            cout << "1. Calculate maximum clique" << endl;
            cout << "2. Close program" << endl;
            int choice;
            cin >> choice;
            switch(choice){
                case 1:{
                    // Implement a function in Multigraph class to print the graph details
                    vector<int> startingClique;

                    cout << endl << "====================== MAXIMUM CLIQUE ========================" << endl;

                    auto start = high_resolution_clock::now();
                    multigraphs.front().maximumCliqueExact(startingClique, multigraphs.front().verticesInGraph());
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);

                    cout<<"-> Maximum clique - exact algorithm:" << endl << endl;
                    cout << "Consists of vertices with indices: ";
                    printVector(multigraphs.front().maxClique);
                    cout << endl << endl;
                    cout << "Resulting maximum clique: " << endl;
                    multigraphs.front().printCliqueExact();
                    cout << "Maximum clique in this graph: " << endl;
                    multigraphs.front().printWithMissingVertices(multigraphs.front().maxClique);

                    auto start2 = high_resolution_clock::now();
                    multigraphs.front().maximumCliqueApproximation();
                    auto stop2 = high_resolution_clock::now();
                    auto duration2 = duration_cast<microseconds>(stop2 - start2);


                    cout<<"-> Maximum clique - approximation algorithm:" << endl << endl;
                    cout << "Consists of vertices with indices: ";
                    printVector(multigraphs.front().maxCliqueApproximation);
                    cout << endl << endl;
                    cout << "Resulting maximum clique: " << endl;
                    multigraphs.front().printCliqueApprox();
                    cout << "Maximum clique in this graph: " << endl;
                    multigraphs.front().printWithMissingVertices(multigraphs.front().maxCliqueApproximation);

                    cout << "[Maximum Clique Algorithm - Exact] Time taken: "
                        << duration.count() << " microseconds"
                        << endl;
                    cout << "[Maximum Clique Algorithm - Approximation] Time taken: "
                        << duration2.count() << " microseconds"
                        << endl;
                    cout << endl;

                    cout << endl << "========================================================" << endl;
                    break;}
                case 2: 
                    return EXIT_SUCCESS;
                default:
                    break;
            }
        }
    } else {
        while(true) {
            cout << "GRAPHS CONSIDERED: " << endl << endl;
            cout << "Graph 1: " << endl;
            multigraphs.front().printAdjacencyMatrix();
            cout << "Graph 2:" << endl;
            multigraphs.back().printAdjacencyMatrix();
            cout << "The first row and the leftmost column correspond to the indices of the vertices." << endl;
            cout << "If a star/dot appears in the adjacency matrix of a graph, it means that this corresponding vertex was removed from the original graph." << endl << endl;
            cout << "What do you want to do? Choose correct option" << endl;
            cout << "1. Calculate maximum clique" << endl;
            cout << "2. Calculate maximum common subgraph" << endl;
            cout << "3. Calculate graph edit distance" << endl;
            cout << "4. Close program" << endl;
            int choice;
            cin >> choice;
            switch(choice){
                case 1: {
                    int i = 1;
                    cout << endl << "====================== MAXIMUM CLIQUE ========================" << endl;
                    for (Multigraph multigraph : multigraphs) {
                        // Implement a function in Multigraph class to print the graph details
                        vector<int> startingClique;

                        cout << endl << "-------- " << ((i==1) ? "1ST" : "2ND") << " MULTIGRAPH --------" << endl;

                        auto start = high_resolution_clock::now();
                        multigraph.maximumCliqueExact(startingClique, multigraph.verticesInGraph());
                        auto stop = high_resolution_clock::now();
                        auto duration = duration_cast<microseconds>(stop - start);

                        cout << "-> Maximum clique - exact algorithm result:" << endl << endl;
                        cout << "Consists of vertices with indices: ";
                        printVector(multigraph.maxClique);
                        cout << endl << endl;
                        cout << "Resulting maximum clique: " << endl;
                        multigraph.printCliqueExact();
                        cout << "Maximum clique in this graph: " << endl;
                        multigraph.printWithMissingVertices(multigraph.maxClique);

                        auto start2 = high_resolution_clock::now();
                        multigraph.maximumCliqueApproximation();
                        auto stop2 = high_resolution_clock::now();
                        auto durationApprox = duration_cast<microseconds>(stop2 - start2);

                        cout << "-> Maximum clique - approximation algorithm result:" << endl << endl;
                        cout << "Consists of vertices with indices: ";
                        printVector(multigraph.maxCliqueApproximation);
                        cout << endl << endl;
                        cout << "Resulting maximum clique: " << endl;
                        multigraph.printCliqueApprox();
                        cout << "Maximum clique in this graph: " << endl;
                        multigraph.printWithMissingVertices(multigraph.maxCliqueApproximation);

                        cout << "[Maximum Clique Algorithm - Exact] Time taken: "
                            << duration.count() << " microseconds"
                            << endl;
                        cout << "[Maximum Clique Algorithm - Approximation] Time taken: "
                             << durationApprox.count() << " microseconds"
                            << endl;
                        cout << "--------------------------------" << endl;
                        i += 1;
                    }
                    cout << endl << "==============================================================" << endl;
                    break;
                }
                case 2: {
                    cout << endl << "================== MAXIMUM COMMON SUBGRAPH ===================" << endl;
                    cout << endl;

                    cout << "-> Maximum common subgraph - exact algorithm result" << endl << endl;
                    auto start = high_resolution_clock::now();
                    tuple<Multigraph, Multigraph, Multigraph, vector<int>, vector<int>> subgraphInfo = Multigraph::maximumCommonSubgraph(true, multigraphsVectorList[0], multigraphsVectorList[1]);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);

                    Multigraph resultingSubgraph = get<0>(subgraphInfo);
                    Multigraph subgraphAs1stGraph = get<1>(subgraphInfo);
                    Multigraph subgraphAs2ndGraph = get<2>(subgraphInfo);
                    vector<int> verticesIn1stGraph = get<3>(subgraphInfo);
                    vector<int> verticesIn2ndGraph = get<4>(subgraphInfo);

                    cout << "Resulting subgraph: " << endl;
                    resultingSubgraph.printAdjacencyMatrix();

                    cout << "Corresponding indices of vertices from initial graphs: " << endl;
                    cout << "Graph 1" << "\t" << "Graph 2" << endl;
                    for (int i=0; i<resultingSubgraph.getVerticesNo(); i++)
                        cout << verticesIn1stGraph[i] << "\t\t" << verticesIn2ndGraph[i] << endl;
                    cout << endl;

                    cout << "Subgraph in 1st graph: " << endl;
                    subgraphAs1stGraph.printWithMissingVertices(verticesIn1stGraph);

                    cout << "Subgraph in 2nd graph: " << endl;
                    subgraphAs2ndGraph.printWithMissingVertices(verticesIn2ndGraph);

                    cout << "-> Maximum common subgraph - approximation algorithm result" << endl << endl;
                    auto start2 = high_resolution_clock::now();
                    tuple<Multigraph, Multigraph, Multigraph, vector<int>, vector<int>> subgraphInfoApprox = Multigraph::maximumCommonSubgraph(false, multigraphsVectorList[0], multigraphsVectorList[1]);
                    auto stop2 = high_resolution_clock::now();
                    auto duration2 = duration_cast<microseconds>(stop2 - start2);

                    Multigraph resultingSubgraphApprox = get<0>(subgraphInfoApprox);
                    Multigraph subgraphAs1stGraphApprox = get<1>(subgraphInfoApprox);
                    Multigraph subgraphAs2ndGraphApprox = get<2>(subgraphInfoApprox);
                    vector<int> verticesIn1stGraphApprox = get<3>(subgraphInfoApprox);
                    vector<int> verticesIn2ndGraphApprox = get<4>(subgraphInfoApprox);

                    cout << "Resulting subgraph: " << endl;
                    resultingSubgraphApprox.printAdjacencyMatrix();

                    cout << "Corresponding indices of vertices from initial graphs: " << endl;
                    cout << "Graph 1" << "\t" << "Graph 2" << endl;
                    for (int i=0; i<resultingSubgraphApprox.getVerticesNo(); i++)
                        cout << verticesIn1stGraphApprox[i] << "\t\t" << verticesIn2ndGraphApprox[i] << endl;
                    cout << endl;

                    cout << "Subgraph in 1st graph: " << endl;
                    subgraphAs1stGraphApprox.printWithMissingVertices(verticesIn1stGraphApprox);

                    cout << "Subgraph in 2nd graph: " << endl;
                    subgraphAs2ndGraphApprox.printWithMissingVertices(verticesIn2ndGraphApprox);

                    cout << "[Maximum Common Subgraph Algorithm - Exact] Time taken: "
                        << duration.count() << " microseconds"
                        << endl;
                    cout << "[Maximum Common Subgraph Algorithm - Approximation] Time taken: "
                        << duration2.count() << " microseconds"
                        << endl;
                    cout << endl << "==========================================================" << endl << endl;
                    break;
                }
                case 3: {
                    cout << endl << "=================== GRAPH EDIT DISTANCE ===================" << endl << endl;
                    MultigraphMetricService mms = MultigraphMetricService();
                    cout << "-> Graph edit distance - exact algorithm result" << endl << endl;
                    auto start = high_resolution_clock::now();
                    Multigraph multigraph1 = multigraphs.front();
                    Multigraph multigraph2 = multigraphs.back();
                    mms.calculateGraphEditDistance(multigraph1, multigraph2);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    
                    cout << "-> Graph edit distance - approximation algorithm result" << endl << endl;
                    auto start2 = high_resolution_clock::now();
                    mms.calculateGraphEditDistanceApproximation(multigraph1, multigraph2);
                    auto stop2 = high_resolution_clock::now();
                    auto duration2 = duration_cast<microseconds>(stop2 - start2);
                    
                    cout << "[Graph Edit Distance Algorithm - Exact] Time taken: "
                        << duration.count() << " microseconds"
                        << endl;
                    cout << "[Graph Edit Distance Algorithm - Approximation] Time taken: "
                        << duration2.count() << " microseconds"
                        << endl;
                    cout << endl << "============================================================" << endl << endl;
                    break;
                }
                case 4: 
                    return EXIT_SUCCESS;
                default:
                    break;
            }
        }
    }

    return EXIT_SUCCESS;
}
