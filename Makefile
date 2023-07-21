columnar: main.cpp filesystem/configuration.cpp
	g++ -o columnar main.cpp \
		filesystem/configuration.cpp process/daemonize.cpp dsa/merge_sort.cpp \
		dsa/heap.cpp dsa/vector_utils.cpp -W -Wall -pedantic


test: heap_test.cpp 
	g++ -o test \
		heap_test.cpp \
		dsa/heap.cpp dsa/vector_utils.cpp -W -Wall -pedantic

clean: 
	rm -rf *.o

mrproper : clean 
	rm columnar
