project(ExternalCharManipulator)
cmake_minimum_required(VERSION 2.6)
add_library(ExternalCharManipulator ${Library} code.c)
target_link_libraries(ExternalCharManipulator Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory Machine List ExternalEntitiesFactory ListMap Processor Char ExternalActorsFactory)