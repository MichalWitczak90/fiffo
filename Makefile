uname := $(shell uname -s)

ifeq ($(uname), Linux)
	compiler := g++
else
	compiler := clang++
endif

all:
	$(compiler) -g -std=c++1z main.cpp source/generic_fifo.cpp -Iinclude/ -o fifo.elf

doxy:
	mkdir -p doxygen/
	doxygen doxyconfig