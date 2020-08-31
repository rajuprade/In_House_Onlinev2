INCLUDEDIR	=-I /usr/include/libxml2 
CFLAGS          = -Wall -g ${INCLUDEDIR} -I.
LIBS= -lxml2 -lm -lpthread
LIBXML=-L/usr/include/libxml2 
LIBS0=${LIBS} ${LIBXML} 

teleset: main.o system.o shared_mem.o xml.o common.o user_info.o
	gcc $(CFLAGS) $(LIBXMl) -o teleset main.o system.o shared_mem.o xml.o common.o user_info.o $(LIBS0)

   
main.o: main.c system.o shared_mem.o xml.o common.o user_info.o 
	gcc $(CFLAGS) $(LIBS0) -c main.c 

system.o: system.c server.h
	gcc $(CFLAGS) -c system.c 

shared_mem.o: shared_mem.c shared_mem.h
	gcc $(CFLAGS) -c shared_mem.c 

xml.o: xml.c xml.h
	gcc $(CFLAGS) -c xml.c $(LIBS0)

common.o: common.c server.h
	gcc $(CFLAGS) -c common.c 

user_info.o: user_info.c user_info.h
	gcc $(CFLAGS) -c user_info.c 

               
clean: 
	rm -f  *.o teleset     
