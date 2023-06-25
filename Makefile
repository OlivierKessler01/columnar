columnar: main.cpp filesystem/configuration.cpp
	g++ -o columnar main.cpp filesystem/configuration.cpp process/daemonize.cpp dsa/merge_sort.cpp dsa/heap.cpp -W -Wall -pedantic

clean: 
	rm -rf *.o

mrproper : clean 
	rm columnar
