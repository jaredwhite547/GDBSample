all:
	gcc -g Sample.c vector.c -std=c99 -o Sample

clean:
	rm Sample 
