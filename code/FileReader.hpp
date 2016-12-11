//
// Created by Alexander Lorkowski on 12/11/16.
//

#ifndef FILEREADER_HPP_
#define FILEREADER_HPP_


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class FileReader {
private:
    std::string filename;
    std::vector<std::vector<std::string>> equations;
    void read();
    int rows;
    int columns;

public:
    FileReader(std::string input);
    virtual ~FileReader();
    std::vector<std::vector<std::string>> getSystem();
    void print();
    std::string getEquation(int i, int j);
    int getRows();
    int getColumns();
};


#endif //FILEREADER_HPP_
