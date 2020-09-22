CFLAGS = -W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-long-long -Wmissing-declarations -O3

all: a.out a_db.out

mrproper:
	rm *.o *.out

a.out: main.o solve.o heapsort.o
	gcc $(CFLAGS) main.o solve.o heapsort.o
main.o: main.c
	gcc $(CFLAGS) -c main.c
solve.o: solve.c
	gcc $(CFLAGS) -c solve.c
heapsort.o: heapsort.c
	gcc $(CFLAGS) -c heapsort.c

a_db.out: main_db.o solve_db.o heapsort_db.o
	gcc $(CFLAGS) -g main_db.o solve_db.o heapsort_db.o -o a_db.out
main_db.o: main.c
	gcc $(CFLAGS) -g -c main.c -o main_db.o
solve_db.o: solve.c
	gcc $(CFLAGS) -g -c solve.c -o solve_db.o
heapsort_db.o: heapsort.c
	gcc $(CFLAGS) -g -c heapsort.c -o heapsort_db.o
