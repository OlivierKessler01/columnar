columnar:
	g++ -g -c main.cpp -o columnar.o main.cpp \
		filesystem/configuration.cpp process/daemonize.cpp \
		-W -Wall -pedantic

test_heap: clean  
	g++ -g  -o heap_test.o dsa/heap/heap_test.cpp \
		dsa/heap/heap.cpp dsa/vector_utils.cpp -W -Wall -pedantic \
	&& ./heap_test.o

test_heap_sort: clean 
	g++ -g -o heap_sort_test.o \
		dsa/sort/heap_sort_test.cpp \
		dsa/vector_utils.cpp \
		dsa/sort/heap_sort.cpp dsa/heap/heap.cpp -W -Wall -pedantic \
	&& ./heap_sort_test.o

clean: 
	rm -rf *.o

