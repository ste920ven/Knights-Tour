all:
	g++ -std=c++11 -o submission *.cpp
test:
	./submission

clean:
	rm -f *o submission output.txt *~ \#*
