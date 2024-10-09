#!/usr/bin/env bash

######################################
# DO NOT CHANGE THIS FOLLOWING LINE: #
OP2_BASELINE_FILE="baseline_op_02.c" #
######################################

############################################
# HOWEVER, CHANGE THESE LINES:             #
# Replace the filenames with your variants #
############################################
OP2_SUBMISSION_VAR01_FILE="./src/master_transpose.c"
OP2_SUBMISSION_VAR02_FILE="./src/tuned_variant02_op_02.c"
OP2_SUBMISSION_VAR03_FILE="./src/tuned_variant20_op_02.c"
### blocked transpose
OP2_SUBMISSION_VAR04_FILE="./src/tuned_variant10_op_02.c"
OP2_SUBMISSION_VAR05_FILE="./src/tuned_variant30_op_02.c"

######################################################
# You can even change the compiler flags if you want #
######################################################
# CFLAGS="-std=c99 -O2"
CFLAGS="-std=c99 -O2 -mavx2 -mfma -fopenmp -Wall -g"

