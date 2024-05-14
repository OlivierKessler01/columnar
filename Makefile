build_server:
	g++ -g -o columnard server/main.cpp \
		server/filesystem/configuration.cpp server/process/daemonize.cpp \
		-W -Wall -pedantic

.ONESHELL:
server: build_server
	killall columnard
	./columnard

build_client:
	g++ -g -o columnarc client/main.cpp -W -Wall -pedantic

.ONESHELL:
client: build_client
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

