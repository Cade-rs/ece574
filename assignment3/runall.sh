#!/bin/bash

#NOTE: need to be in the build directory in order for this to run properly

./src/hlsyn "../assignment3_testfiles_new/error tests/error1.c"  ../output/error1_out.v
./src/hlsyn "../assignment3_testfiles_new/error tests/error1.c"  ../output/error2_out.v
./src/hlsyn "../assignment3_testfiles_new/error tests/error1.c"  ../output/error3_out.v

./src/hlsyn "../assignment3_testfiles_new/if tests/test_if1.c"  ../output/test_if1_out.v
./src/hlsyn "../assignment3_testfiles_new/if tests/test_if2.c"  ../output/test_if2_out.v
./src/hlsyn "../assignment3_testfiles_new/if tests/test_if3.c"  ../output/test_if3_out.v
./src/hlsyn "../assignment3_testfiles_new/if tests/test_if4.c"  ../output/test_if4_out.v

./src/hlsyn "../assignment3_testfiles_new/latency tests/hls_lat_test1.c"  ../output/hls_lat_test1_out.v
./src/hlsyn "../assignment3_testfiles_new/latency tests/hls_lat_test2.c"  ../output/hls_lat_test2_out.v
./src/hlsyn "../assignment3_testfiles_new/latency tests/hls_lat_test3.c"  ../output/hls_lat_test3_out.v
./src/hlsyn "../assignment3_testfiles_new/latency tests/hls_lat_test4.c"  ../output/hls_lat_test4_out.v
./src/hlsyn "../assignment3_testfiles_new/latency tests/hls_lat_test5.c"  ../output/hls_lat_test5_out.v
./src/hlsyn "../assignment3_testfiles_new/latency tests/hls_lat_test6.c"  ../output/hls_lat_test6_out.v

./src/hlsyn "../assignment3_testfiles_new/standard tests/hls_test1.c"  ../output/hls_test1_out.v
./src/hlsyn "../assignment3_testfiles_new/standard tests/hls_test2.c"  ../output/hls_test2_out.v
./src/hlsyn "../assignment3_testfiles_new/standard tests/hls_test3.c"  ../output/hls_test3_out.v
./src/hlsyn "../assignment3_testfiles_new/standard tests/hls_test4.c"  ../output/hls_test4_out.v
./src/hlsyn "../assignment3_testfiles_new/standard tests/hls_test5.c"  ../output/hls_test5_out.v
./src/hlsyn "../assignment3_testfiles_new/standard tests/hls_test6.c"  ../output/hls_test6_out.v
./src/hlsyn "../assignment3_testfiles_new/standard tests/hls_test7.c"  ../output/hls_test7_out.v
./src/hlsyn "../assignment3_testfiles_new/standard tests/hls_test8.c"  ../output/hls_test8_out.v

