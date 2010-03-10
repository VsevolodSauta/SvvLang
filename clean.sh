find -name cmake_install.cmake -exec rm {} +
find -name CMakeFiles -exec rm -rf {} +
find -name Testing -exec rm -rf {} +
find -name Makefile -exec rm {} +
find -name CMakeCache.txt -exec rm {} +
find -name CTestTestfile.cmake -exec rm {} +
