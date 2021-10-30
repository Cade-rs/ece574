#!/bin/bash

#NOTE: need to be in the build directory in order for this to run properly
pwd
rm -r ../build/*
pwd
cmake -G "MinGW Makefiles" ..
pwd
mingw32-make