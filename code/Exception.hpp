#ifndef EXCEPTIONDEF
#define EXCEPTIONDEF
#include <string>

class Exception {
private:
    /// The tag and message associated to the error.
    std::string mTag, mProblem;

public:

    /*! A constructor to instantiate exception class.
     *
     * \param tagString The identifier of the exception.
     * \param probString A string that describes the problem and how the program will handle it.
     */
    Exception(std::string tagString, std::string probString);

    /// A method to print out the error to the console.
    void PrintDebug() const;
};
#endif //EXCEPTIONDEF