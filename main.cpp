#include "main.h"
#include "Multigraph.cpp"
#include "MultigraphReader.cpp"
#include "MultigraphMetricService.cpp"
#include <cstdlib>
#include <list>
#include <iostream> // Include iostream for console output

int main() {
    std::string filePath = "C:/Users/Bartek/Desktop/inputGrafExample.txt"; // Hardcoded file path

    MultigraphReader reader; // Create an instance of MultigraphReader

    std::list<Multigraph> multigraphs = reader.readMultigraphsFromFile(filePath); // Read multigraphs from file

    // Print the multigraphs to the console
    for (Multigraph multigraph : multigraphs) {
        // Implement a function in Multigraph class to print the graph details
        multigraph.print(); // Assuming a function called print() exists in Multigraph class
        vector<int> startingCLique;



        multigraph.maximumCliqueExact(startingCLique, multigraph.verticesInGraph());
        multigraph.printClique();
    }
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
