# This Makefile orchestrates the building, verification and timing of
# your implementations.
#
# - richard.m.veras@ou.edu


# Increments to use in the tests
# These are good debugging sizes
# MIN=16
# MAX=2048
# STEP=16

# These are better benchmarking sizes
#MIN=32
#MAX=4096
#STEP=32

# These are bigger benchmarking sizes, but you may run out of memory on the general strides test
# MIN=64
# MAX=8192
# STEP=64

MIN=16
MAX=512
STEP=16

all: clean run_verifier run_bench

run_verifier: run_verifier_op2_var01 run_verifier_op2_var02 run_verifier_op2_var03 run_verifier_op2_var04 run_verifier_op2_var05

run_bench: run_bench_op2_var01 run_bench_op2_var02 run_bench_op2_var03 run_bench_op2_var04 run_bench_op2_var05

run_bench_op2_var01: build_bench
	touch ./data/result_bench_op2_var01.csv
        # square matrices, a and b are row major
        #                       min    max    step    m n   rs_src cs_src rs_dst cs_dst
	./run_bench_op2_var01.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     1      -1 | tee -a ./data/result_bench_op2_var01.csv
        # square matrices, a and b are col major
	./run_bench_op2_var01.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     -1      1 | tee -a ./data/result_bench_op2_var01.csv
        # square matrices, a row major and b col major
	./run_bench_op2_var01.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     -1      1 | tee -a ./data/result_bench_op2_var01.csv
        # square matrices, a col major and b row major
	./run_bench_op2_var01.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     1      -1 | tee -a ./data/result_bench_op2_var01.csv
        # square matrices, a and b general strides
        #./run_bench_op2_var01.x  ${MIN} ${MAX} ${STEP} 1 1   -2      1     1      -2 | tee -a ./data/result_bench_op2_var01.csv #NOTE: This may ask for too much mem 
	./run_bench_op2_var01.x  ${MIN} ${MAX} ${STEP} 1 1   2      1     1      -2 | tee -a ./data/result_bench_op2_var01.csv
        # rectangular matrices, a row major and b col major
	./run_bench_op2_var01.x  ${MIN} ${MAX} ${STEP} 1 -${MIN}   1      -1     -1      1 | tee -a ./data/result_bench_op2_var01.csv
        # rectangular matrices, a row major and b col major
	./run_bench_op2_var01.x  ${MIN} ${MAX} ${STEP} -${MIN} 1   1      -1     -1      1 | tee -a ./data/result_bench_op2_var01.csv

run_bench_op2_var02: build_bench
	touch ./data/result_bench_op2_var02.csv
        # square matrices, a and b are row major
        #                       min    max    step    m n   rs_src cs_src rs_dst cs_dst
	./run_bench_op2_var02.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     1      -1 | tee -a ./data/result_bench_op2_var02.csv
        # square matrices, a and b are col major
	./run_bench_op2_var02.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     -1      1 | tee -a ./data/result_bench_op2_var02.csv
        # square matrices, a row major and b col major
	./run_bench_op2_var02.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     -1      1 | tee -a ./data/result_bench_op2_var02.csv
        # square matrices, a col major and b row major
	./run_bench_op2_var02.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     1      -1 | tee -a ./data/result_bench_op2_var02.csv
        # square matrices, a and b general strides
        #./run_bench_op2_var02.x  ${MIN} ${MAX} ${STEP} 1 1   -2      1     1      -2 | tee -a ./data/result_bench_op2_var02.csv #NOTE: This may ask for too much mem 
	./run_bench_op2_var02.x  ${MIN} ${MAX} ${STEP} 1 1   2      1     1      -2 | tee -a ./data/result_bench_op2_var02.csv
        # rectangular matrices, a row major and b col major
	./run_bench_op2_var02.x  ${MIN} ${MAX} ${STEP} 1 -${MIN}   1      -1     -1      1 | tee -a ./data/result_bench_op2_var02.csv
        # rectangular matrices, a row major and b col major
	./run_bench_op2_var02.x  ${MIN} ${MAX} ${STEP} -${MIN} 1   1      -1     -1      1 | tee -a ./data/result_bench_op2_var02.csv

run_bench_op2_var03: build_bench
	touch ./data/result_bench_op2_var03.csv
        # square matrices, a and b are row major
        #                       min    max    step    m n   rs_src cs_src rs_dst cs_dst
	./run_bench_op2_var03.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     1      -1 | tee -a ./data/result_bench_op2_var03.csv
        # square matrices, a and b are col major
	./run_bench_op2_var03.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     -1      1 | tee -a ./data/result_bench_op2_var03.csv
        # square matrices, a row major and b col major
	./run_bench_op2_var03.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     -1      1 | tee -a ./data/result_bench_op2_var03.csv
        # square matrices, a col major and b row major
	./run_bench_op2_var03.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     1      -1 | tee -a ./data/result_bench_op2_var03.csv
        # square matrices, a and b general strides
        #./run_bench_op2_var03.x  ${MIN} ${MAX} ${STEP} 1 1   -2      1     1      -2 | tee -a ./data/result_bench_op2_var03.csv #NOTE: This may ask for too much mem 
	./run_bench_op2_var03.x  ${MIN} ${MAX} ${STEP} 1 1   2      1     1      -2 | tee -a ./data/result_bench_op2_var03.csv
        # rectangular matrices, a row major and b col major
	./run_bench_op2_var03.x  ${MIN} ${MAX} ${STEP} 1 -${MIN}   1      -1     -1      1 | tee -a ./data/result_bench_op2_var03.csv
        # rectangular matrices, a row major and b col major
	./run_bench_op2_var03.x  ${MIN} ${MAX} ${STEP} -${MIN} 1   1      -1     -1      1 | tee -a ./data/result_bench_op2_var03.csv

run_bench_op2_var04: build_bench
	touch ./data/result_bench_op2_var04.csv
        # square matrices, a and b are row major
        #                       min    max    step    m n   rs_src cs_src rs_dst cs_dst
	./run_bench_op2_var04.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     1      -1 | tee -a ./data/result_bench_op2_var04.csv
        # square matrices, a and b are col major
	./run_bench_op2_var04.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     -1      1 | tee -a ./data/result_bench_op2_var04.csv
        # square matrices, a row major and b col major
	./run_bench_op2_var04.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     -1      1 | tee -a ./data/result_bench_op2_var04.csv
        # square matrices, a col major and b row major
	./run_bench_op2_var04.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     1      -1 | tee -a ./data/result_bench_op2_var04.csv
        # square matrices, a and b general strides
        #./run_bench_op2_var03.x  ${MIN} ${MAX} ${STEP} 1 1   -2      1     1      -2 | tee -a ./data/result_bench_op2_var03.csv #NOTE: This may ask for too much mem 
	./run_bench_op2_var04.x  ${MIN} ${MAX} ${STEP} 1 1   2      1     1      -2 | tee -a ./data/result_bench_op2_var04.csv
        # rectangular matrices, a row major and b col major
	./run_bench_op2_var04.x  ${MIN} ${MAX} ${STEP} 1 -${MIN}   1      -1     -1      1 | tee -a ./data/result_bench_op2_var04.csv
        # rectangular matrices, a row major and b col major
	./run_bench_op2_var04.x  ${MIN} ${MAX} ${STEP} -${MIN} 1   1      -1     -1      1 | tee -a ./data/result_bench_op2_var04.csv

run_bench_op2_var05: build_bench
	touch ./data/result_bench_op2_var05.csv
        # square matrices, a and b are row major
        #                       min    max    step    m n   rs_src cs_src rs_dst cs_dst
	./run_bench_op2_var05.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     1      -1 | tee -a ./data/result_bench_op2_var05.csv
        # square matrices, a and b are col major
	./run_bench_op2_var05.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     -1      1 | tee -a ./data/result_bench_op2_var05.csv
        # square matrices, a row major and b col major
	./run_bench_op2_var05.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     -1      1 | tee -a ./data/result_bench_op2_var05.csv
        # square matrices, a col major and b row major
	./run_bench_op2_var05.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     1      -1 | tee -a ./data/result_bench_op2_var05.csv
        # square matrices, a and b general strides
        #./run_bench_op2_var03.x  ${MIN} ${MAX} ${STEP} 1 1   -2      1     1      -2 | tee -a ./data/result_bench_op2_var03.csv #NOTE: This may ask for too much mem 
	./run_bench_op2_var05.x  ${MIN} ${MAX} ${STEP} 1 1   2      1     1      -2 | tee -a ./data/result_bench_op2_var05.csv
        # rectangular matrices, a row major and b col major
	./run_bench_op2_var05.x  ${MIN} ${MAX} ${STEP} 1 -${MIN}   1      -1     -1      1 | tee -a ./data/result_bench_op2_var05.csv
        # rectangular matrices, a row major and b col major
	./run_bench_op2_var05.x  ${MIN} ${MAX} ${STEP} -${MIN} 1   1      -1     -1      1 | tee -a ./data/result_bench_op2_var05.csv

run_verifier_op2_var01: build_verifier
	touch ./data/result_verification_op2_var01.csv
        # square matrices, a and b are row major
        #                       min    max    step    m n   rs_src cs_src rs_dst cs_dst
	./run_test_op2_var01.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     1      -1 | tee -a ./data/result_verification_op2_var01.csv
        # square matrices, a and b are col major
	./run_test_op2_var01.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     -1      1 | tee -a ./data/result_verification_op2_var01.csv
        # square matrices, a row major and b col major
	./run_test_op2_var01.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     -1      1 | tee -a ./data/result_verification_op2_var01.csv
        # square matrices, a col major and b row major
	./run_test_op2_var01.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     1      -1 | tee -a ./data/result_verification_op2_var01.csv
        # square matrices, a and b general strides
	./run_test_op2_var01.x  ${MIN} ${MAX} ${STEP} 1 1   -2      1     1      -2 | tee -a ./data/result_verification_op2_var01.csv
        # rectangular matrices, a row major and b col major
	./run_test_op2_var01.x  ${MIN} ${MAX} ${STEP} 1 -${MIN}   1      -1     -1      1 | tee -a ./data/result_verification_op2_var01.csv
        # rectangular matrices, a row major and b col major
	./run_test_op2_var01.x  ${MIN} ${MAX} ${STEP} -${MIN} 1   1      -1     -1      1 | tee -a ./data/result_verification_op2_var01.csv
	grep -i "FAIL" ./data/result_verification_op2_var01.csv | wc -l

run_verifier_op2_var02: build_verifier
	touch ./data/result_verification_op2_var02.csv
        # square matrices, a and b are row major
        #                       min    max    step    m n   rs_src cs_src rs_dst cs_dst
	./run_test_op2_var02.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     1      -1 | tee -a ./data/result_verification_op2_var02.csv
        # square matrices, a and b are col major
	./run_test_op2_var02.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     -1      1 | tee -a ./data/result_verification_op2_var02.csv
        # square matrices, a row major and b col major
	./run_test_op2_var02.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     -1      1 | tee -a ./data/result_verification_op2_var02.csv
        # square matrices, a col major and b row major
	./run_test_op2_var02.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     1      -1 | tee -a ./data/result_verification_op2_var02.csv
        # square matrices, a and b general strides
	./run_test_op2_var02.x  ${MIN} ${MAX} ${STEP} 1 1   -2      1     1      -2 | tee -a ./data/result_verification_op2_var02.csv
        # rectangular matrices, a row major and b col major
	./run_test_op2_var02.x  ${MIN} ${MAX} ${STEP} 1 -${MIN}   1      -1     -1      1 | tee -a ./data/result_verification_op2_var02.csv
        # rectangular matrices, a row major and b col major
	./run_test_op2_var02.x  ${MIN} ${MAX} ${STEP} -${MIN} 1   1      -1     -1      1 | tee -a ./data/result_verification_op2_var02.csv
	grep -i "FAIL" ./data/result_verification_op2_var02.csv | wc -l

run_verifier_op2_var03: build_verifier
	touch ./data/result_verification_op2_var03.csv
        # square matrices, a and b are row major
        #                       min    max    step    m n   rs_src cs_src rs_dst cs_dst
	./run_test_op2_var03.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     1      -1 | tee -a ./data/result_verification_op2_var03.csv
        # square matrices, a and b are col major
	./run_test_op2_var03.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     -1      1 | tee -a ./data/result_verification_op2_var03.csv
        # square matrices, a row major and b col major
	./run_test_op2_var03.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     -1      1 | tee -a ./data/result_verification_op2_var03.csv
        # square matrices, a col major and b row major
	./run_test_op2_var03.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     1      -1 | tee -a ./data/result_verification_op2_var03.csv
        # square matrices, a and b general strides
	./run_test_op2_var03.x  ${MIN} ${MAX} ${STEP} 1 1   -2      1     1      -2 | tee -a ./data/result_verification_op2_var03.csv
        # rectangular matrices, a row major and b col major
	./run_test_op2_var03.x  ${MIN} ${MAX} ${STEP} 1 -${MIN}   1      -1     -1      1 | tee -a ./data/result_verification_op2_var03.csv
        # rectangular matrices, a row major and b col major
	./run_test_op2_var03.x  ${MIN} ${MAX} ${STEP} -${MIN} 1   1      -1     -1      1 | tee -a ./data/result_verification_op2_var03.csv
	grep -i "FAIL" ./data/result_verification_op2_var03.csv | wc -l

run_verifier_op2_var04: build_verifier
	touch ./data/result_verification_op2_var04.csv
        # square matrices, a and b are row major
        #                       min    max    step    m n   rs_src cs_src rs_dst cs_dst
	./run_test_op2_var04.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     1      -1 | tee -a ./data/result_verification_op2_var04.csv
        # square matrices, a and b are col major
	./run_test_op2_var04.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     -1      1 | tee -a ./data/result_verification_op2_var04.csv
        # square matrices, a row major and b col major
	./run_test_op2_var04.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     -1      1 | tee -a ./data/result_verification_op2_var04.csv
        # square matrices, a col major and b row major
	./run_test_op2_var04.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     1      -1 | tee -a ./data/result_verification_op2_var04.csv
        # square matrices, a and b general strides
	./run_test_op2_var04.x  ${MIN} ${MAX} ${STEP} 1 1   -2      1     1      -2 | tee -a ./data/result_verification_op2_var04.csv
        # rectangular matrices, a row major and b col major
	./run_test_op2_var04.x  ${MIN} ${MAX} ${STEP} 1 -${MIN}   1      -1     -1      1 | tee -a ./data/result_verification_op2_var04.csv
        # rectangular matrices, a row major and b col major
	./run_test_op2_var04.x  ${MIN} ${MAX} ${STEP} -${MIN} 1   1      -1     -1      1 | tee -a ./data/result_verification_op2_var04.csv
	grep -i "FAIL" ./data/result_verification_op2_var04.csv | wc -l

run_verifier_op2_var05: build_verifier
	touch ./data/result_verification_op2_var05.csv
        # square matrices, a and b are row major
        #                       min    max    step    m n   rs_src cs_src rs_dst cs_dst
	./run_test_op2_var05.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     1      -1 | tee -a ./data/result_verification_op2_var05.csv
        # square matrices, a and b are col major
	./run_test_op2_var05.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     -1      1 | tee -a ./data/result_verification_op2_var05.csv
        # square matrices, a row major and b col major
	./run_test_op2_var05.x  ${MIN} ${MAX} ${STEP} 1 1   1      -1     -1      1 | tee -a ./data/result_verification_op2_var05.csv
        # square matrices, a col major and b row major
	./run_test_op2_var05.x  ${MIN} ${MAX} ${STEP} 1 1   -1      1     1      -1 | tee -a ./data/result_verification_op2_var05.csv
        # square matrices, a and b general strides
	./run_test_op2_var05.x  ${MIN} ${MAX} ${STEP} 1 1   -2      1     1      -2 | tee -a ./data/result_verification_op2_var05.csv
        # rectangular matrices, a row major and b col major
	./run_test_op2_var05.x  ${MIN} ${MAX} ${STEP} 1 -${MIN}   1      -1     -1      1 | tee -a ./data/result_verification_op2_var05.csv
        # rectangular matrices, a row major and b col major
	./run_test_op2_var05.x  ${MIN} ${MAX} ${STEP} -${MIN} 1   1      -1     -1      1 | tee -a ./data/result_verification_op2_var05.csv
	grep -i "FAIL" ./data/result_verification_op2_var05.csv | wc -l

build_verifier:
	./build_test_op2.sh

# TODO: Build timer
build_bench:
	./build_bench_op2.sh

# TODO: Run Timer

clean:
	rm -f *.x *~ *.o

cleanall: clean
	rm -rf *.csv
