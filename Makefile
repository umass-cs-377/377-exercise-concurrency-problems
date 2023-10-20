.PHONY : all
all : incrementer workers balance

.DEFAULT_GOAL := all

clean:
	rm incrementer workers balance

incrementer: incrementer.cpp
	g++ -o incrementer incrementer.cpp

workers: workers.cpp
	g++ -o workers workers.cpp

balance: balance.cpp
	g++ -o balance balance.cpp