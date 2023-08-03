all: main-clang main-gcc

CLANG_WARNINGS = -Weverything -Wno-padded -Wno-poison-system-directories
GCC_WARNINGS = -Wall -Wextra

main-clang: main.c ../../webgpu.h Makefile
	clang -std=c99 $(CLANG_WARNINGS) -o $@ $<

main-gcc: main.c ../../webgpu.h Makefile
	gcc -std=c99 $(GCC_WARNINGS) -o $@ $<
