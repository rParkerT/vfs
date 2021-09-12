Implementation of basic linux commands in virtual file system.
Implemented commands are: mkdir, cd, ls, rm, mkfile

CommandsIf is used as interface for Commands class that parses user input,
while VirtualFileSystem contains commands implementation.

CMake is used for project build. For building tests for testVfs.cpp,
Catch2 repo from GitHub (https://github.com/catchorg/Catch2)
is pulled in local project skipList. Doxygen is used for project documentation.

To build project and project documentation, go to root directory:
$ cd root
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make doc

To run tests:
$ cd test
$ ./test

To run main and create your own VirtualFileSystem:
$ cd impl/src
$ ./vfs

To check valgrind: valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./vfs
