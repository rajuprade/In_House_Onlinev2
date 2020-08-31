INCLUDEDIR	=-I /usr/include/libxml2 
CFLAGS          = -Wall -g ${INCLUDEDIR} -I.
LIBS= -lxml2 -lm 
LIBXML=-L/usr/include/libxml2 
LIBS0=${LIBS} ${LIBXML} 

teleset: serv.o server.o
	gcc $(CFLAGS) $(LIBXMl) -o teleset serv.o server.o $(LIBS)


serv.o: serv.c server.o
	gcc $(CFLAGS)  -c serv.c 

server.o: server.c server.h
	gcc $(CFLAGS) -c server.c 
clean: 
	rm -f  *.o teleset      
