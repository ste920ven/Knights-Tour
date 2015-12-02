all:
	g++ -std=c++11 -o submission *.cpp
test:
	./submission
