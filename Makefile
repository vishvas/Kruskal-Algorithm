all: run

run:  kruskal.out 
	


kruskal.out: kruskal.c		
		gcc -o kruskal.out kruskal.c

	
clean: kruskal.c 
	rm kruskal.out
