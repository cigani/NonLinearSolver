//
/* AUTHORS:
* Jaquier, Michael <michael.jaquier@epfl.ch>
* Lorkowski, Alexander <alexander.lorkowski@epfl.ch>
*/
//

#include <iostream>
#include "exprtk.hpp"


void square_wave() {
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    std::string expr_string = "a*(4/pi)*"
            "((1 /1)*sin( 2*pi*f*t)+(1 /3)*sin( 6*pi*f*t)+"
            " (1 /5)*sin(10*pi*f*t)+(1 /7)*sin(14*pi*f*t)+"
            " (1 /9)*sin(18*pi*f*t)+(1/11)*sin(22*pi*f*t)+"
            " (1/13)*sin(26*pi*f*t)+(1/15)*sin(30*pi*f*t)+"
            " (1/17)*sin(34*pi*f*t)+(1/19)*sin(38*pi*f*t)+"
            " (1/21)*sin(42*pi*f*t)+(1/23)*sin(46*pi*f*t)+"
            " (1/25)*sin(50*pi*f*t)+(1/27)*sin(54*pi*f*t))";

    static const double pi = double(3.141592653589793238462643383279502);

    double f = pi / double(10);
    double t = double(0);
    double a = double(10);
    //std::cout << "a" << a;
    //std::cout << "t" << t;

    symbol_table_t symbol_table;
    symbol_table.add_variable("f", f);
    symbol_table.add_variable("t", t);
    symbol_table.add_variable("a", a);
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(expr_string, expression);

    const double delta = double(4) * pi / double(1000);

    for (t = double(-2) * pi; t <= double(+2) * pi; t += delta) {
        double result = expression.value();
        //printf("%19.15f\t%19.15f\t%19.15f\t%19.15f\n", t, result, t, a);
    }
}

int main() {
//    square_wave();

    std::vector<std::vector<double> > values(0, std::vector<double>(3));
    std::vector<double> val1{2, 3, 4};
    values.push_back(val1);
    values.push_back(val1);
    std::cout << values.size() << std::endl;
    return 0;
}