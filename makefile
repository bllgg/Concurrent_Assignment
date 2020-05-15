all: linked_list.c linked_list.h main.c
	gcc -g -o prog linked_list.c main.c -lpthread

clean:
	rm prog
