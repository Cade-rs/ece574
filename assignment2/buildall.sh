#!/bin/bash

#NOTE: need to be in the build directory in order for this to run properly
rm -r ../build/*

cmake -G "MinGW Makefiles" ..

mingw32-make 