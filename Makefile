TESTS=test/test_load test/test_save test/test_sanity
TESTS_C=$(TESTS:=.c)
TESTS_O=$(TESTS:=.o)

all: main

main: main.o hmmlib.o
	gcc main.o hmmlib.o -o main

test: $(TESTS)
	$(foreach t,$(TESTS),$(t);)

$(TESTS): %: %.o hmmlib.o test/unit_test.o
	gcc $< hmmlib.o test/unit_test.o -o $@

%.o: %.c hmmlib.h
	gcc -c $< -o $@

clean:
	rm */*.o *.o main $(TESTS)