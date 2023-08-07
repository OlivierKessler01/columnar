columnar: main.cpp filesystem/configuration.cpp
	g++ -o columnar.o main.cpp \
		filesystem/configuration.cpp process/daemonize.cpp \
		-W -Wall -pedantic

test_heap: clean dsa/heap_test.cpp 
	g++ -o heap_test.o \
		dsa/heap_test.cpp \
		dsa/heap.cpp dsa/vector_utils.cpp -W -Wall -pedantic \
	&& ./heap_test.o

test_heap_sort: clean dsa/sort/heap_sort_test.cpp
	g++ -o heap_sort_test.o \
		dsa/sort/heap_sort_test.cpp \
		dsa/vector_utils.cpp \
		dsa/sort/heap_sort.cpp dsa/heap.cpp -W -Wall -pedantic \
	&& ./heap_sort_test.o

clean: 
	rm -rf *.o

