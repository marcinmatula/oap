CUDA_PATH := /usr/local/cuda-6.0
MODE := Debug
PLATFORM := samsung
EXTRA_CXXOPTIONS :=
EXTRA_NVCCOPTIONS :=
CXX := g++
NVCC := $(CUDA_PATH)/bin/nvcc --compiler-bindir /usr/bin/gcc-4.8
