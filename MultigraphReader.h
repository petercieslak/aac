#ifndef AAC_MULTIGRAPHREAD_H
#define AAC_MULTIGRAPHREAD_H

#include <fstream>
#include <string>
#include <iostream>
#include <list>
#include "Multigraph.h"

class MultigraphReader {
    std::ifstream multigraphFile;

    public:
        // Constructor
        explicit MultigraphReader();

        // Method for reading graphs from file
        
        Multigraph readMultigraphsFromFile(std::string filePath);
};

#endif //AAC_MULTIGRAPHREAD_H