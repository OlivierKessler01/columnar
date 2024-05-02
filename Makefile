build_columnard:
	g++ -g -o columnard server/main.cpp \
		server/filesystem/configuration.cpp server/process/daemonize.cpp \
		-W -Wall -pedantic

.ONESHELL:
columnard: build_columnard
	killall columnard
	./columnard

build_columnarc:
	g++ -g -o columnarc client/main.cpp -W -Wall -pedantic

.ONESHELL:
columnarc: build_columnarc
	killall columnarc
	./columnarc

tests: test_heap

test_heap: clean  
	g++ -g  -o heap_test server/dsa/heap/heap_test.cpp \
		server/dsa/heap/heap.cpp server/dsa/vector_utils.cpp -W -Wall -pedantic \
	&& ./heap_test

test_heap_sort: clean 
	g++ -g -o heap_sort_test \
		server/dsa/sort/heap_sort_test.cpp \
		server/dsa/vector_utils.cpp \
		server/dsa/sort/heap_sort.cpp server/dsa/heap/heap.cpp -W -Wall -pedantic \
	&& ./heap_sort_test

clean: 
	rm -rf columnarc columnard

