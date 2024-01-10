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
            cout << "The first row and the leftmost column correspond to the indices of the vertices." << endl << endl;
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
                    cout << "Maximum clique as a graph: " << endl;
                    multigraphs.front().printCliqueExact();

                    auto start2 = high_resolution_clock::now();
                    multigraphs.front().maximumCliqueApproximation();
                    auto stop2 = high_resolution_clock::now();
                    auto duration2 = duration_cast<microseconds>(stop2 - start2);


                    cout<<"-> Maximum clique - approximation algorithm:" << endl << endl;
                    cout << "Consists of vertices with indices: ";
                    printVector(multigraphs.front().maxCliqueApproximation);
                    cout << endl << endl;
                    cout << "Maximum clique as a graph: " << endl;
                    multigraphs.front().printCliqueApprox();

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
            cout << "The first row and the leftmost column correspond to the indices of the vertices." << endl << endl;
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
                        cout << "Maximum clique as a graph: " << endl;
                        multigraph.printCliqueExact();

                        auto start2 = high_resolution_clock::now();
                        multigraph.maximumCliqueApproximation();
                        auto stop2 = high_resolution_clock::now();
                        auto durationApprox = duration_cast<microseconds>(stop2 - start2);

                        cout << "-> Maximum clique - approximation algorithm result:" << endl << endl;
                        cout << "Consists of vertices with indices: ";
                        printVector(multigraph.maxCliqueApproximation);
                        cout << endl << endl;
                        cout << "Maximum clique as a graph: " << endl;
                        multigraph.printCliqueApprox();

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
                    Multigraph maxCommonSubgraph = Multigraph::maximumCommonSubgraph(true, multigraphsVectorList[0], multigraphsVectorList[1]);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);

                    cout << "Resulting subgraph: " << endl;
                    maxCommonSubgraph.printAdjacencyMatrix();

                    cout << "-> Maximum common subgraph - approximation algorithm result" << endl << endl;
                    auto start2 = high_resolution_clock::now();
                    Multigraph maxCommonSubgraphApprox = Multigraph::maximumCommonSubgraph(false, multigraphsVectorList[0], multigraphsVectorList[1]);
                    auto stop2 = high_resolution_clock::now();
                    auto duration2 = duration_cast<microseconds>(stop2 - start2);

                    cout << "Resulting subgraph: " << endl;
                    maxCommonSubgraphApprox.printAdjacencyMatrix();

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
