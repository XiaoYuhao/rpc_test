###########################
#	Makefile
###########################

#source object target
SOURCE 	:= 
OBJS 	:= 
TARGET	:= client

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
$(TARGET): $(OBJS) client.cpp
	$(CXX) -o $@ $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) $^


#clean
clean:
	rm -fr *.o
	rm -fr *.gch
	rm -fr client


