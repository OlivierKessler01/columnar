columnar: main.c filesystem/configuration.c
	gcc -g -o columnar main.c filesystem/configuration.c process/daemonize.c -W -Wall -std=c90 -pedantic

clean: 
	rm -rf *.o

mrproper : clean 
	rm columnar
