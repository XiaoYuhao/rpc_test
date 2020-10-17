###########################
#	Makefile
###########################

#source object target
SOURCE 	:= 
OBJS 	:= pthreadpool.o procedure.o network.o
TARGET	:= server  

#compile and lib parameter
CXX		:= g++
LIBS	:= 
LDFLAGS	:= -lpthread 
DEFINES	:=
CFLAGS	:= -g
CXXFLAGS:= -std=c++11
 
.PHONY: clean

#link parameter
LIB := 

#link
$(TARGET): $(OBJS) server.cpp
	$(CXX) -o $@ $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) $^

pthreadpool.o: pthreadpool.cpp pthreadpool.h
	$(CXX)  $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) -c $^

procedure.o: procedure.cpp procedure.h
	$(CXX)  $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) -c $^

network.o: network.h network.cpp
	$(CXX)  $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) -c $^

#clean
clean:
	rm -fr *.o
	rm -fr *.gch
	rm -fr server


