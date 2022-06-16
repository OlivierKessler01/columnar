columnar: main.c filesystem/configuration.c
	gcc -o columnar main.c filesystem/configuration.c -W -Wall -std=c90 -pedantic

clean: 
	rm -rf *.o

mrproper : clean 
	rm columnar
