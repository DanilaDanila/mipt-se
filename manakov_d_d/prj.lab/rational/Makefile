# GNU/Linux ONLY

COMPILER=g++
TEST_NAME=tests
LIBNAME=rational.a

all: release

test:
	$(COMPILER) tests.cpp -o $(TEST_NAME)
	./$(TEST_NAME) < input.txt

release: rational
	ar rcs $(LIBMANE) rational.o

rational: rational.cpp
	$(COMPILER) -c rational.cpp

clean:
	rm *.o $(TEST_NAME) $(LIBNAME)