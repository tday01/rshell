CC = g++ -c
CFLAGS = -Wall -ansi -Werror -pedantic -std=c++11
LINK = g++ -g
COURSE = CS100
VERSION = 01

a.out		:	test.o component.o container.o strategy.o decorator.o factory.o print.o
					$(LINK) test.o component.o container.o strategy.o decorator.o factory.o print.o

test.o		:	test.cpp component.h container.h strategy.h
					$(CC) $(CFLAGS) test.cpp

component.o	:	component.cpp component.h
					$(CC) $(CFLAGS) component.cpp
					
strategy.o	:	strategy.cpp strategy.h
					$(CC) $(CFLAGS) strategy.cpp
					
container.o	:	container.cpp container.h
					$(CC) $(CFLAGS) container.cpp
					
decorator.o	:	decorator.cpp decorator.h
					$(CC) $(CFLAGS) decorator.cpp
					
factory.o	:	factory.cpp factory.h
					$(CC) $(CFLAGS) factory.cpp
					
print.o		:	print.cpp print.h
					$(CC) $(CFLAGS) print.cpp

docm		:	test.cpp component.cpp container.cpp strategy.cpp decorator.cpp
					c++ -std=c++11 -m32 -g -fno-inline -fno-omit-frame-pointer test.cpp\
					component.cpp container.cpp strategy.cpp decorator.cpp -o\
					myappMemLeakChk
					
clean		:
				rm -r *.o a.out
					
save		:	
				tar cvzf LAB03_$(COURSE)_$(VERSION).tar.gz *.cpp *.h\
					makefile
