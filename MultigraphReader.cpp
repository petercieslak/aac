
#include "MultigraphReader.h"

MultigraphReader::MultigraphReader() {
}


/*
 * Create an adjacency matrix by reading a local file.
 *
 * Parameters:
 *      _filePath - path to the file containing graph data
 * */
Multigraph MultigraphReader::readMultigraphsFromFile(std::string filePath) {
    this->multigraphFile.open(filePath);

    std::string line = "";
    std::getline(multigraphFile, line);
    int graphSize = 0;
    std::getline(multigraphFile, line);
    graphSize = stoi(line);

    Multigraph multigraph(graphSize);

    int rowNum = 0;
    int colNum = 0;

    while(std::getline(multigraphFile, line)) {
        std::stringstream lineSplit(line);
        std::string numberString;
        while(lineSplit >> numberString) {
            multigraph.setAdjMatrixEntry(rowNum, colNum, stoi(numberString));
            colNum += 1;
        }
        colNum = 0;
        rowNum += 1;

        if(rowNum == graphSize) {
            break;  // Stop reading after one Multigraph - assumption
        }
    }

    return multigraph;
}