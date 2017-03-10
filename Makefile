CFLAGS = -Ofast -flto -ffast-math -Wall

all: threesat.o wrapper.o
	@clang $(CFLAGS) $^ -o threesat
	@rm -f *.o
test: threesat.o test.o
	@clang $(CFLAGS) $^ -o testoutput
	@-./testoutput
	@make clean --no-print-directory
clean:
	@rm -f threesat
	@rm -f testoutput
	@rm -f *.o
	@rm -f *.gch
	@rm -rf threesat.dSYM
%.o: %.c
	@clang -c $(CFLAGS) $< -o $@
threesat.o: threesat.h threesat.c
test.o: test.c
wrapper.o: wrapper.c