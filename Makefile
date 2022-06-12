columnar: main.c filesystem/configuration.c
	gcc -o columnar main.c filesystem/configuration.c -W -Wall -ansi -pedantic

clean: 
	rm -rf *.o

mrproper : clean 
	rm columnar