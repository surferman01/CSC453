CC = gcc


prog: one.o two.o
	$(CC) -o prog one.o two.o

one.o: one.c hdr.h
	$(CC) -c one.c

two.o: two.c hdr.h
	$(CC) -c two.c

clean:
	rm -f *.o

test: prog
	./prog test_input