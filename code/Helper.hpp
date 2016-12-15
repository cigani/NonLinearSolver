//
// Created by Alexander Lorkowski on 12/10/16.
//

#ifndef HELPER_HPP_
#define HELPER_HPP_

#include <iostream>
#include <iomanip>

class Helper {
private:
    /*! A function that formats the output of the Helper class.
     *
     * \param original The string to be padded.
     * \param charCount The length of the outputed string.
     */
	std::string stringPadding(std::string original, size_t charCount);

    /// The name of the program.
	std::string programName;

public:

	/*! A constructor to assign the program name to the helper class.
     *
     * \param name The name of the program.
     */
	Helper(std::string name);

    //! A virtual destructor for the Newton method.
	virtual ~Helper();

    //! A method that prints the usage screen onto the console.
    void show_usage();

    //! A method that prints implemented Nonlinear Solvers in the program.
    void show_methods();

};


#endif //HELPER_HPP_
