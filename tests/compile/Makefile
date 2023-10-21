# Always rebuild all targets.
.PHONY: all clean main-c.out main-cpp.out

all: main-c.out main-cpp.out

clean:
	rm -f main-c.out main-cpp.out

CLANG_WARNINGS = -Weverything -Wno-padded -Wno-poison-system-directories
GCC_WARNINGS = -Wall -Wextra

main-c.out: main.c ../../webgpu.h Makefile
	clang -std=c99 $(CLANG_WARNINGS) -o $@ $<
	gcc   -std=c99 $(GCC_WARNINGS)   -o $@ $<
	clang -std=c11 $(CLANG_WARNINGS) -o $@ $<
	gcc   -std=c11 $(GCC_WARNINGS)   -o $@ $<
	clang -std=c17 $(CLANG_WARNINGS) -o $@ $<
	gcc   -std=c17 $(GCC_WARNINGS)   -o $@ $<

main-cpp.out: main.cpp ../../webgpu.h Makefile
	clang++ -std=c++98 $(CLANG_WARNINGS) -o $@ $<
	g++     -std=c++98 $(GCC_WARNINGS)   -o $@ $<
	clang++ -std=c++03 $(CLANG_WARNINGS) -o $@ $<
	g++     -std=c++03 $(GCC_WARNINGS)   -o $@ $<
	clang++ -std=c++11 $(CLANG_WARNINGS) -o $@ $<
	g++     -std=c++11 $(GCC_WARNINGS)   -o $@ $<
	clang++ -std=c++14 $(CLANG_WARNINGS) -o $@ $<
	g++     -std=c++14 $(GCC_WARNINGS)   -o $@ $<
	clang++ -std=c++17 $(CLANG_WARNINGS) -o $@ $<
	g++     -std=c++17 $(GCC_WARNINGS)   -o $@ $<
	clang++ -std=c++20 $(CLANG_WARNINGS) -o $@ $<
	g++     -std=c++20 $(GCC_WARNINGS)   -o $@ $<
