CFLAGS = -O0 -flto -ffast-math -Wall -ggdb

all: util.o wrapper.o algorithms.o hashset.o
	@clang $(CFLAGS) $^ -o threesat
	@rm -f *.o
test: util.o test.o algorithms.o hashset.o
	@clang $(CFLAGS) $^ -o testoutput
	@-./testoutput
	@rm -f *.o
clean:
	@rm -f threesat
	@rm -f testoutput
	@rm -f *.o
	@rm -f *.gch
	@rm -rf threesat.dSYM

%.o: %.c
	@clang -c $(CFLAGS) $< -o $@
util.o: util.h util.c
test.o: test.c
wrapper.o: wrapper.c
algorithms.o: algorithms.h algorithms.c
hashset.o: hashset.h hashset.c