TESTS_C=$(wildcard test/test_*.c)
TESTS=$(basename $(TESTS_C))
TESTS_O=$(TESTS:=.o)
REQS=hmmlib hashtable
REQS_C=$(REQS:=.c)
REQS_O=$(REQS:=.o)
REQS_H=$(REQS:=.h)

all: test

main: main.o $(REQS_O)
	@gcc main.o $(REQS_O) -o main

test: $(TESTS)
	@$(foreach t,$(TESTS),$(t);)
	@rm -f *.o */*.o $(TESTS)

$(TESTS): %: %.o $(REQS_O) test/unit_test.o
	@gcc $< $(REQS_O) test/unit_test.o -o $@

%.o: %.c $(REQS_H)
	@gcc -c $< -o $@

clean:
	@rm -f */*.o *.o main $(TESTS)