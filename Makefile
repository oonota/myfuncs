CXX = clang++
CFLAGS = -I./nmf -I.
TARGET = main

VPATH = ./nmf:./Eigen

SOURCES = main.cpp\
          nmf.cpp

OBJECTS = $(subst .cpp,.o,$(SOURCES)) 



%.o:%.cpp
	$(CXX) -c $< $(CFLAGS)

main:	$(OBJECTS)
	$(CXX) -o $@ $^

.PHONY:clean
clean:
	$(RM) *.o main



