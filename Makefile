columnar: main.c filesystem/configuration.c
	g++ -g columnar main.c filesystem/configuration.c process/daemonize.c dsa/merge_sort.cpp dsa/heap.cpp -W -Wall -std=c90 -pedantic

clean: 
	rm -rf *.o

mrproper : clean 
	rm columnar
