all: linkedList.c
	gcc -o linkedList linkedList.c

clean:
	rm linkedList
