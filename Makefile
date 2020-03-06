all:
	g++ -g -std=c++1z main.cpp source/generic_fifo.cpp -Iinclude/ -o fifo.elf

doxy:
	mkdir -p doxygen/
	doxygen doxyconfig