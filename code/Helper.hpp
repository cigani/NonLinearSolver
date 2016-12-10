//
// Created by Alexander Lorkowski on 12/10/16.
//

#ifndef HELPER_HPP_
#define HELPER_HPP_

#include <iostream>
#include <iomanip>

class Helper {
private:
	std::string stringPadding(std::string original, size_t charCount);
	std::string programName;

public:

	Helper(std::string name);
	virtual ~Helper();

    void show_usage();
    void show_methods();

};


#endif //HELPER_HPP_
