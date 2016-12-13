include_directories(${CMAKE_CURRENT_SOURCE_DIR})
cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# The next lines represent a list of all the executables in the folder (chapter)
# There is typically one executable per exercise.
# As you solve exercises, you need to add them here.
# The syntax is add_executable(executable_name source_file_name)

add_executable(nonlinear Main.cpp Chord.cpp Newton.cpp FixedPoint.cpp
        Equations.cpp Aitken.cpp exprtk.hpp Bisection.cpp NonlinearSolver.cpp
        string.hpp Eigen Jacobian.cpp EquationTools.cpp EquationsControl.cpp
        Gauss.cpp Expression.cpp Helper.cpp ExpressionSystem.cpp NewtonSystem.cpp
        NonlinearSystemsSolver.cpp)
add_executable(tests TestSuit.cpp Chord.cpp Newton.cpp FixedPoint.cpp
        Equations.cpp Aitken.cpp exprtk.hpp Bisection.cpp NonlinearSolver.cpp
        string.hpp Eigen Jacobian.cpp EquationTools.cpp EquationsControl.cpp
        Gauss.cpp Expression.cpp ExpressionSystem.cpp NewtonSystem.cpp NonlinearSystemsSolver.cpp)
add_executable(scratch scratch.cpp exprtk.hpp Eigen Gauss.cpp)

add_executable(testReader testReader.cpp ExpressionSystem.cpp Expression.cpp)
