#!/bin/bash

#NOTE: need to be in the build directory in order for this to run properly

../src/dpgen ../assignment_2_circuits/474a_circuit1.txt  ../output/474a_circuit1_out.v
../src/dpgen ../assignment_2_circuits/474a_circuit2.txt  ../output/474a_circuit2_out.v
../src/dpgen ../assignment_2_circuits/474a_circuit3.txt  ../output/474a_circuit3_out.v
../src/dpgen ../assignment_2_circuits/474a_circuit4.txt  ../output/474a_circuit4_out.v
../src/dpgen ../assignment_2_circuits/574a_circuit5.txt  ../output/574a_circuit5_out.v
../src/dpgen ../assignment_2_circuits/574a_circuit6.txt  ../output/574a_circuit6_out.v

../src/dpgen ../assignment_2_circuits/error1.txt  ../output/error1_out.v
../src/dpgen ../assignment_2_circuits/error2.txt  ../output/error2_out.v
../src/dpgen ../assignment_2_circuits/error3.txt  ../output/error3_out.v
../src/dpgen ../assignment_2_circuits/error4.txt  ../output/error4_out.v

../src/dpgen ../assignment_2_circuits/mixedcircuit1.txt  ../output/mixedcircuit1_out.v
../src/dpgen ../assignment_2_circuits/mixedcircuit2.txt  ../output/mixedcircuit2_out.v
../src/dpgen ../assignment_2_circuits/mixedcircuit3.txt  ../output/mixedcircuit3_out.v

../src/dpgen ../assignment_2_circuits/ucircuit1.txt  ../output/ucircuit1_out.v
../src/dpgen ../assignment_2_circuits/ucircuit2.txt  ../output/ucircuit2_out.v
../src/dpgen ../assignment_2_circuits/ucircuit3.txt  ../output/ucircuit3_out.v