/*
 * AUTHORS:
 * Jaquier, Michael <michael.jaquier@epfl.ch>
 * Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
 */

#include "FileReader.hpp"

FileReader::FileReader(std::string input) {
    filename = input;
    read();
}

FileReader::~FileReader() {};

void FileReader::read() {
    rows = 0;
    columns = 0;
    int count = 0;
    std::ifstream fin(filename);
    std::string line;
    while (std::getline(fin, line)) {         // for each line
        std::vector<std::string> lineData;    // create a new row
        std::string val;
        std::istringstream lineStream(line);
        while (lineStream >> val) {           // for each value in line
            lineData.push_back(val);          // add to the current row
            if ( count == 0 ) {
                columns++;
            }
        }
        equations.push_back(lineData);        // add row to equations
        rows++;
        count++;
    }
}

std::vector<std::vector<std::string>> FileReader::getSystem() {
    return equations;
}

std::string FileReader::getEquation(int i, int j) {
    return equations.at(i).at(j);
}

void FileReader::print() {
    std::vector<std::vector<double>>::const_iterator it;
    std::vector<double>::const_iterator it2;

    for ( const std::vector<std::string> &v : equations ) {
        for ( std::string eq : v ) {
            std::cout << eq << ' ';
        }
        std::cout << std::endl;
    }
}