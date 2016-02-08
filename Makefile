TESTS_C=$(wildcard test/test_*.c)
TESTS=$(basename $(TESTS_C))
TESTS_O=$(TESTS:=.o)

all: test

main: main.o hmmlib.o
	@gcc main.o hmmlib.o -o main

test: $(TESTS)
	@$(foreach t,$(TESTS),$(t);)

$(TESTS): %: %.o hmmlib.o test/unit_test.o
	@gcc $< hmmlib.o test/unit_test.o -o $@

%.o: %.c hmmlib.h
	@gcc -c $< -o $@

clean:
	@rm -f */*.o *.o main $(TESTS)