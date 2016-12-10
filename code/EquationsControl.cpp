//
/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/
//

#include "Equations.hpp"

///
void EquationsControl::logErrors(const std::__1::string &expr_string,
                                 exprtk::parser<double> &parser) const {
    printf("Error: %s\tExpression: %s\n",
           parser.error().c_str(),
           expr_string.c_str());

    for (size_t i = 0; i < parser.error_count(); ++i) {
        exprtk::parser_error::type error = parser.get_error(i);

        printf("Error: %02d  Position: %02d Type: [%14s] Msg: "
                       "%s\tExpression: %s\n",
               static_cast<unsigned int>(i),
               static_cast<unsigned int>(error.token.position),
               to_str(error.mode).c_str(),
               error.diagnostic.c_str(),
               expr_string.c_str());
    }
}