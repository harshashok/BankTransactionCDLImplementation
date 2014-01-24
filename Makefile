warmup1: warmup1.o my402list.o verify.o
	gcc -o warmup1 -g verify.o warmup1.o my402list.o

warmup1.o: my402list.h verify.h warmup1.c verify.c
	gcc -g -c -Wall warmup1.c

verify.o: verify.c verify.h my402list.h
	gcc -g -c -Wall verify.c verify.h

my402list.o: my402list.c my402list.h
	gcc -g -c -Wall my402list.c my402list.h

clean:
	rm -f *.o warmup1
