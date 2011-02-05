project(ExternalConsoleManipulator)
cmake_minimum_required(VERSION 2.6)
add_library(ExternalConsoleManipulator ${Library} code.c)
target_link_libraries(ExternalConsoleManipulator Object Number Logic Comparation Allocator File Method NumberFactory LogicFactory StringFactory CharFactory MethodFactory Machine List ListMap ExternalEntitiesFactory Processor Console)