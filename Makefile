CXX = clang++
CXXFLAGS = -I./nmf -I./Eigen
TARGET = main

main: 	main.o\
	nmf/nmf.o
	$(CXX) -o main main.o nmf/nmf.o
nmf.o:	nmf/nmf.cpp nmf/nmf.h
	$(CXX) -c nmf/nmf.cpp $(CXXFLAGS)   
main.o: main.cpp
	$(CXX) -c main.cpp $(CXXFLAGS) 

.PHONY:clean
clean:
	$(RM) *.o main



