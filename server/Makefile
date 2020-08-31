##############################################################
#
# Makefile 
##############################################################


####### Compilers, tolls and options

CFLAGS = -Wall -O2 
CXXFLAGS = -Wall -O2 
LFLAGS = -L/usr/include/libxml2 
LIBS= -lxml2 -lm
INCPATH = -I /usr/include/libxml2 
RM = rm -f
CC = gcc

####### Files

SOURCES = server.c serv.c

HEADERS = server.h 

OBJECTS = serv.o server.o 

PROG = teleset

first: all

######## Implicites rules
# tab with vim, not kde

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $< 

####### Build rules

all: Makefile $(PROG) 

$(PROG): $(OBJECTS)
	  gcc $(LFLAGS) $(OBJECTS) -o $(PROG) $(LIBS)

clean:
	$(RM) $(PROG) $(OBJECTS) *~ *core*


####### Compile

server.o: server.c server.h 

serv.o: serv.c server.h


