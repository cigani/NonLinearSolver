cmake_minimum_required(VERSION 3.6)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_CXX_STANDARD 11)

# The next lines represent a list of all the executables in the folder (chapter)
# There is typically one executable per exercise.
# As you solve exercises, you need to add them here.
# The syntax is add_executable(executable_name source_file_name)

add_executable(Aitken Aitken.cpp)
add_executable(Chord Chord.cpp)
add_executable(Equations Equations.cpp)
add_executable(FixedPoint FixedPoint.cpp)
add_executable(Newton Newton.cpp)
add_executable(Secant Secant.cpp)


