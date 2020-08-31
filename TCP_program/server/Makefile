teleset: mainteleset.o comhlink.o
	gcc $(CFLAGS) -o teleset mainteleset.o comhlink.o


mainteleset.o: mainteleset.c comhlink.o
	gcc $(CFLAGS) -c mainteleset.c

comhlink.o: comhlink.c comhlink.h
	gcc $(CFLAGS) -c comhlink.c

clean: 
	rm -f  *.o teleset      
