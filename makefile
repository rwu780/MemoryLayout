mem_mod1:memlayout.o mem_mod1.o mem_mod2.o mem_mod3.o
	gcc -o mem_mod1.out mem_mod1.o memlayout.o -static -m32 
	gcc -o mem_mod2.out mem_mod2.o memlayout.o -static -m32
	gcc -o mem_mod3.out mem_mod3.o memlayout.o -static -m32

memlayout.o:memlayout.c memlayout.h
	gcc -c -m32 memlayout.c

mem_mod1.o:mem_mod1.c
	cc -c -static -m32 mem_mod1.c

mem_mod2.o:mem_mod2.c
	cc -c -static -m32 mem_mod2.c
mem_mod3.o:mem_mod3.c
	cc -c -static -m32 mem_mod3.c
clean: 
	rm -f *.o *.out
