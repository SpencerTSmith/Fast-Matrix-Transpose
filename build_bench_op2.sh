#!/usr/bin/env bash
#
# This file builds the verifier code based on the configured vars.
# You should not need to modify this.
#
# - richard.m.veras@ou.edu

source op2_dispatch_vars.sh

echo $OP2_BASELINE_FILE

echo $OP2_SUBMISSION_VAR01_FILE
echo $OP2_SUBMISSION_VAR02_FILE
echo $OP2_SUBMISSION_VAR03_FILE
echo $OP2_SUBMISSION_VAR04_FILE
echo $OP2_SUBMISSION_VAR05_FILE

echo $CFLAGS


# Build the timer
# NOTE: need gnu99/gnu11 to get the POSIX compliance for timing
gcc -std=gnu99 -O2 -c -DFUN_NAME_TST="test" ./src/timer_op_02.c -static -fPIC  


# build the variants
gcc $CFLAGS -c -DFUN_NAME="test" $OP2_SUBMISSION_VAR01_FILE -o op2_var01.o
gcc $CFLAGS -c -DFUN_NAME="test" $OP2_SUBMISSION_VAR02_FILE -o op2_var02.o
gcc $CFLAGS -c -DFUN_NAME="test" $OP2_SUBMISSION_VAR03_FILE -o op2_var03.o
gcc $CFLAGS -c -DFUN_NAME="test" $OP2_SUBMISSION_VAR04_FILE -o op2_var04.o  # blocked transpose
gcc $CFLAGS -c -DFUN_NAME="test" $OP2_SUBMISSION_VAR05_FILE -o op2_var05.o


# build the times
gcc $CFLAGS timer_op_02.o op2_var01.o -o ./run_bench_op2_var01.x
gcc $CFLAGS timer_op_02.o op2_var02.o -o ./run_bench_op2_var02.x
gcc $CFLAGS timer_op_02.o op2_var03.o -o ./run_bench_op2_var03.x
gcc $CFLAGS timer_op_02.o op2_var04.o -o ./run_bench_op2_var04.x
gcc $CFLAGS timer_op_02.o op2_var05.o -o ./run_bench_op2_var05.x


