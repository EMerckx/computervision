#!/bin/bash

# build latest version
cd build
make -j4
cd ..

# run exercise
./dist/ex_11.out ./img/rays.png
