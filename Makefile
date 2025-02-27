.default: all

all: a1

clean:
	rm -f a1 *.o

a1: main.o Node.o NodeList.o PathSolver.o
	g++ -Wall -Werror -std=c++14 -g -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -c $^
