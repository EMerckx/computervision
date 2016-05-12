#!/bin/bash

# check if directory "build" exists
if [ ! -d "build" ]; then
    mkdir build
fi

# check if directory "dist" exists
if [ ! -d "dist" ]; then
    mkdir dist
fi

# go to build directory
cd build

# run cmake command
cmake ..

# run make command
make -j4

# return to original directory
cd ..