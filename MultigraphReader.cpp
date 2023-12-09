
#include "MultigraphReader.h"

MultigraphReader::MultigraphReader() {
}


/*
 * Create an adjacency matrix by reading a local file.
 *
 * Parameters:
 *      _filePath - path to the file containing graph data
 * */
std::list<Multigraph> MultigraphReader::readMultigraphsFromFile(std::string filePath) {
    this->multigraphFile.open(filePath);

    std::string line = "";

    int numOfGraphs = 0;
    std::getline(multigraphFile, line);
    numOfGraphs = stoi(line);
    int rowNum = 0;
    int colNum = 0;
    int graphSize = 0;
    Multigraph newMultigraph(0);
    Multigraph *multigraph;
    std::list<Multigraph> multigraphs;
    while(std::getline(multigraphFile, line)) {
        if(rowNum == graphSize || graphSize == 0) {
            graphSize = stoi(line);
            multigraph = new Multigraph(graphSize);
            rowNum = 0;
            std::getline(multigraphFile, line);
        }
        std::stringstream lineSplit(line);
        std::string numberString;
        while(lineSplit >> numberString) {
            multigraph -> setAdjMatrixEntry(rowNum, colNum, stoi(numberString));
            colNum += 1;
        }
        colNum = 0;
        rowNum += 1;
        if(rowNum == graphSize) {
            multigraphs.push_back(*multigraph);
        }
    }

    return multigraphs;
}