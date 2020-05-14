all: linked_list.c linked_list.h main.c
	gcc -o prog linked_list.c main.c

clean:
	rm prog
