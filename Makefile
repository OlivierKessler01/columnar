columnar: main.c filesystem/configuration.c
	gcc -g -o columnar main.c filesystem/configuration.c process/daemonize.c array/sort.c -W -Wall -std=c90 -pedantic

clean: 
	rm -rf *.o

mrproper : clean 
	rm columnar
