#!/bin/bash


g++ -std=gnu++0x -o $1_0 -O0 $1.cpp
g++ -std=gnu++0x -o $1_1 -O1 $1.cpp
g++ -std=gnu++0x -o $1_2 -O2 $1.cpp
g++ -std=gnu++0x -o $1_3 -O3 $1.cpp

