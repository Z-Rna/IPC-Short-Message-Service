all: s.out c.out

s.out: s.c
	gcc -w -Wall -std=gnu99 s.c -o s
	
c.out: c.c
	gcc -w -Wall -std=gnu99 c.c -o c
