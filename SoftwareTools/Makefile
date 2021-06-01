.POSIX:
.SUFFIXES:
CC = gcc
CXX = g++
# OpenMP requires gcc. On macOS, gcc seems to link to clang, resulting in a compile error
CFLAGS = -Wall -g -O3 -fopenmp 
CXXFLAGS = -Wall -g -O2 -std=c++11 -pthread -march=native
LDFLAGS =
LDLIBS = -lgmp -lm
SHARED_OBJ = convolution.o global-common.o table.o table_fixed.o walsh-transform.o

.PHONY: all
all: skinny64 skinny128

skinny64: skinny64-differential-hamming skinny64-linear-hamming skinny64-differential-box-weight skinny64-linear-box-weight \
	  skinny64-differential-hamming-2D skinny64-differential-box-weight-2D skinny64-linear-hamming-2D skinny64-linear-box-weight-2D \
	  skinny64-differential-clustering skinny64-linear-clustering skinny64-differential-trail-weight skinny64-linear-trail-weight \
	  skinny64-differential-unrounded skinny64-differential skinny64-correlation skinny64-parse-and-convolve \
	  skinny64-sbox-once skinny64-sbox-twice

skinny64-differential-hamming: skinny64-tools/skinny64-differential-hamming-weight.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-differential-hamming-2D: skinny64-tools/skinny64-differential-hamming-weight-2D.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-linear-hamming: skinny64-tools/skinny64-linear-hamming-weight.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-linear-hamming-2D: skinny64-tools/skinny64-linear-hamming-weight-2D.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-differential-box-weight: skinny64-tools/skinny64-differential-box-weight.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-differential-box-weight-2D: skinny64-tools/skinny64-differential-box-weight-2D.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-linear-box-weight: skinny64-tools/skinny64-linear-box-weight.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-linear-box-weight-2D: skinny64-tools/skinny64-linear-box-weight-2D.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-differential-clustering: skinny64-tools/skinny64-differential-clustering.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-linear-clustering: skinny64-tools/skinny64-linear-clustering.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-differential-trail-weight: skinny64-tools/skinny64-differential-trail-weight.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-linear-trail-weight: skinny64-tools/skinny64-linear-trail-weight.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-differential-unrounded: skinny64-tools/skinny64-differential-probability-unrounded.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-differential: skinny64-tools/skinny64-differential-probability.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-correlation: skinny64-tools/skinny64-correlation.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-parse-and-convolve: skinny64-tools/skinny64-parse-and-convolve.o csvparser.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-sbox-once: skinny64-tools/skinny64-sbox-once.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny64-sbox-twice: skinny64-tools/skinny64-sbox-twice.o skinny64-tools/skinny64-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny64-tools/$@ $^ $(LDLIBS)

skinny128: skinny128-differential-hamming skinny128-linear-hamming skinny128-differential-box-weight skinny128-linear-box-weight \
	   skinny128-differential-hamming-2D skinny128-differential-box-weight-2D skinny128-linear-hamming-2D skinny128-linear-box-weight-2D \
	   skinny128-differential-clustering skinny128-linear-clustering \
	   skinny128-sbox-once skinny128-sbox-twice

skinny128-differential-hamming: skinny128-tools/skinny128-differential-hamming-weight.o skinny128-tools/skinny128-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny128-tools/$@ $^ $(LDLIBS)

skinny128-differential-hamming-2D: skinny128-tools/skinny128-differential-hamming-weight-2D.o skinny128-tools/skinny128-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny128-tools/$@ $^ $(LDLIBS)

skinny128-linear-hamming: skinny128-tools/skinny128-linear-hamming-weight.o skinny128-tools/skinny128-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny128-tools/$@ $^ $(LDLIBS)

skinny128-linear-hamming-2D: skinny128-tools/skinny128-linear-hamming-weight-2D.o skinny128-tools/skinny128-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny128-tools/$@ $^ $(LDLIBS)

skinny128-differential-box-weight: skinny128-tools/skinny128-differential-box-weight.o skinny128-tools/skinny128-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny128-tools/$@ $^ $(LDLIBS)

skinny128-differential-box-weight-2D: skinny128-tools/skinny128-differential-box-weight-2D.o skinny128-tools/skinny128-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny128-tools/$@ $^ $(LDLIBS)

skinny128-linear-box-weight: skinny128-tools/skinny128-linear-box-weight.o skinny128-tools/skinny128-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny128-tools/$@ $^ $(LDLIBS)

skinny128-linear-box-weight-2D: skinny128-tools/skinny128-linear-box-weight-2D.o skinny128-tools/skinny128-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny128-tools/$@ $^ $(LDLIBS)

skinny128-differential-clustering: skinny128-tools/skinny128-differential-clustering.o skinny128-tools/skinny128-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny128-tools/$@ $^ $(LDLIBS)

skinny128-linear-clustering: skinny128-tools/skinny128-linear-clustering.o skinny128-tools/skinny128-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny128-tools/$@ $^ $(LDLIBS)

skinny128-sbox-once: skinny128-tools/skinny128-sbox-once.o skinny128-tools/skinny128-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny128-tools/$@ $^ $(LDLIBS)

skinny128-sbox-twice: skinny128-tools/skinny128-sbox-twice.o skinny128-tools/skinny128-common.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) -o skinny128-tools/$@ $^ $(LDLIBS)

.PHONY: clean
clean:
	rm -rf bin *.o 	skinny64-tools/*.o skinny64-tools/skinny64-differential-hamming skinny64-tools/skinny64-linear-hamming skinny64-tools/skinny64-differential-box-weight \
	skinny64-tools/skinny64-linear-box-weight skinny64-tools/skinny64-differential-hamming-2D skinny64-tools/skinny64-differential-box-weight-2D \
	skinny64-tools/skinny64-linear-hamming-2D skinny64-tools/skinny64-linear-box-weight-2D skinny64-tools/skinny64-differential-clustering skinny64-tools/skinny64-linear-clustering \
	skinny64-tools/skinny64-differential-trail-weight skinny64-tools/skinny64-linear-trail-weight skinny64-tools/skinny64-differential-unrounded skinny64-tools/skinny64-differential \
	skinny64-tools/skinny64-correlation skinny64-tools/skinny64-parse-and-convolve skinny64-tools/skinny64-sbox-once skinny64-tools/skinny64-sbox-twice \
	skinny128-tools/*.o skinny128-tools/skinny128-differential-hamming skinny128-tools/skinny128-linear-hamming skinny128-tools/skinny128-differential-box-weight \
	skinny128-tools/skinny128-linear-box-weight skinny128-tools/skinny128-differential-hamming-2D skinny128-tools/skinny128-differential-box-weight-2D \
	skinny128-tools/skinny128-linear-hamming-2D skinny128-tools/skinny128-linear-box-weight-2D skinny128-tools/skinny128-differential-clustering skinny128-tools/skinny128-linear-clustering \
	skinny128-tools/skinny128-sbox-once skinny128-tools/skinny128-sbox-twice

.PHONY: install
install: skinny64 skinny128
	mkdir -p bin
	cp skinny64-tools/skinny64-differential-hamming skinny64-tools/skinny64-linear-hamming skinny64-tools/skinny64-differential-box-weight \
	skinny64-tools/skinny64-linear-box-weight skinny64-tools/skinny64-differential-hamming-2D skinny64-tools/skinny64-differential-box-weight-2D \
	skinny64-tools/skinny64-linear-hamming-2D skinny64-tools/skinny64-linear-box-weight-2D skinny64-tools/skinny64-differential-clustering skinny64-tools/skinny64-linear-clustering \
	skinny64-tools/skinny64-differential-trail-weight skinny64-tools/skinny64-linear-trail-weight skinny64-tools/skinny64-differential-unrounded skinny64-tools/skinny64-differential \
	skinny64-tools/skinny64-correlation skinny64-tools/skinny64-parse-and-convolve skinny64-tools/skinny64-sbox-once skinny64-tools/skinny64-sbox-twice \
	skinny128-tools/skinny128-differential-hamming skinny128-tools/skinny128-linear-hamming skinny128-tools/skinny128-differential-box-weight \
	skinny128-tools/skinny128-linear-box-weight skinny128-tools/skinny128-differential-hamming-2D skinny128-tools/skinny128-differential-box-weight-2D \
	skinny128-tools/skinny128-linear-hamming-2D skinny128-tools/skinny128-linear-box-weight-2D skinny128-tools/skinny128-differential-clustering skinny128-tools/skinny128-linear-clustering \
	skinny128-tools/skinny128-sbox-once skinny128-tools/skinny128-sbox-twice \
	bin

.SUFFIXES: .cpp .c .o
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

