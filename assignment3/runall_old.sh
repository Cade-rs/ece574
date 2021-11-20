#!/bin/bash

#NOTE: need to be in the build directory in order for this to run properly

./src/hlsyn ../assignment_2_circuits/474a_circuit1.txt 9999 ../output/circuit1_out.v
./src/hlsyn ../assignment_2_circuits/474a_circuit2.txt 9999 ../output/circuit2_out.v
./src/hlsyn ../assignment_2_circuits/474a_circuit3.txt 9999 ../output/circuit3_out.v
./src/hlsyn ../assignment_2_circuits/474a_circuit4.txt 9999 ../output/circuit4_out.v
./src/hlsyn ../assignment_2_circuits/574a_circuit5.txt 9999 ../output/circuit5_out.v
./src/hlsyn ../assignment_2_circuits/574a_circuit6.txt 9999 ../output/circuit6_out.v

./src/hlsyn ../assignment_2_circuits/error1.txt 9999 ../output/error1_out.v
./src/hlsyn ../assignment_2_circuits/error2.txt 9999 ../output/error2_out.v
./src/hlsyn ../assignment_2_circuits/error3.txt 9999 ../output/error3_out.v
./src/hlsyn ../assignment_2_circuits/error4.txt 9999 ../output/error4_out.v

./src/hlsyn ../assignment_2_circuits/mixedcircuit1.txt 9999 ../output/mixedcircuit1_out.v
./src/hlsyn ../assignment_2_circuits/mixedcircuit2.txt 9999 ../output/mixedcircuit2_out.v
./src/hlsyn ../assignment_2_circuits/mixedcircuit3.txt 9999 ../output/mixedcircuit3_out.v

./src/hlsyn ../assignment_2_circuits/ucircuit1.txt 9999 ../output/ucircuit1_out.v
./src/hlsyn ../assignment_2_circuits/ucircuit2.txt 9999 ../output/ucircuit2_out.v
./src/hlsyn ../assignment_2_circuits/ucircuit3.txt 9999 ../output/ucircuit3_out.v
