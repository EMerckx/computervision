#!/bin/bash

# build latest version
cd build
make -j4
cd ..

# run exercise
./dist/ex_10.out ./img/rays.png
