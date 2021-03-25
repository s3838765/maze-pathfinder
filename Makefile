.default: all

all: a1

clean:
	rm -f a1 *.o

a1: PathSolver.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
