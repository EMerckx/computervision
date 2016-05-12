#!/bin/bash

# build latest version
cd build
make -j4
cd ..

# run exercise
./dist/ex_13.out ./img/shot1.png ./img/shot2.png
