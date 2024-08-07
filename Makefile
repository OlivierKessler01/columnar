CC = g++
CFLAGS = -std=c++20
RED    := \033[31m
GREEN  := \033[32m
YELLOW := \033[33m
BLUE   := \033[34m
RESET  := \033[0m

# The @ makes sure that the command itself isn't echoed in the terminal
help: # Print help on Makefile
	@echo "Please use 'make <target>' where <target> is one of"
	@echo ""
	@grep '^[^.#]\+:\s\+.*#' Makefile | \
	sed "s/\(.\+\):\s*\(.*\) #\s*\(.*\)/`printf "\033[93m"`  \1`printf "\033[0m"`	\3 [\2]/" | \
	expand -35
	@echo ""
	@echo "Check the Makefile to know exactly what each target is doing."

  
build_server: clean # Build the server 
	@$(CC) $(CFLAGS) -g -o columnard server/main.cpp \
		server/filesystem/configuration.cpp \
		server/query/runner.cpp \
		server/scanner/scanner.cpp \
		server/parser/parser.cpp \
		server/process/daemon.cpp \
		-W -Wall -pedantic

build_client: clean #Build the client
	@$(CC) $(CFLAGS) -g -o columnarc client/main.cpp client/socket.cpp -W -Wall -pedantic


.ONESHELL:
.PHONY:
run_server:
	@killall columnard 2>/dev/null
	./columnard

.PHONY:
server: build_server run_server # Build and launch the server

.PHONY:
client: build_client
	@killall columnarc 2>/dev/null
	./columnarc 127.0.0.1 3307

.PHONY:
run-dev: server client # Build client and server, then run them

tests: test_heap test_heap_sort test_scanner_generator # Run the test suite

generate_scanner: clean # Generate the scanner code
	$(CC) $(CFLAGS) -g  -o scanner_ex  \
		server/scanner/generator.cpp \
		-W -Wall -pedantic \
	&& ./scanner_ex

test_scanner_generator: clean
	$(CC) $(CFLAGS) -g -DTEST -o scanner_generator_test  \
		server/scanner/generator.cpp \
		-W -Wall -pedantic \
	&& ./scanner_generator_test

test_heap: clean  
	$(CC) $(CFLAGS) -g  -DTEST -o heap_test \
		server/dsa/heap/heap.cpp \
		server/dsa/vector_utils.cpp \
		-W -Wall -pedantic \
	&& ./heap_test

test_heap_sort: clean 
	$(CC) $(CFLAGS) -g -o heap_sort_test \
		server/dsa/sort/heap_sort_test.cpp \
		server/dsa/vector_utils.cpp \
		server/dsa/sort/heap_sort.cpp \
		server/dsa/heap/heap.cpp \
		-W -Wall -pedantic \
	&& ./heap_sort_test

clean: # Remove all generated binaries
	@rm -rf columnarc columnard *_test

log-server: # Read the daemon syslogs
	journalctl -n 100 -f | grep columnar



.PHONY:
trace: build_server build_client
	@echo -e "$(RED)Kill old servers and clients$(RESET)"
	@killall columnard 2>/dev/null
	@killall columnarc 2>/dev/null
	@echo -e "$(RED)Sleep 5 secs $(RESET)"
	@sleep 5
	@echo -e "$(RED)Enable kernel tracing $(RESET)"
	@source ~/.bash_profile && start_kernel_tracing
	./columnard
	@echo -e "$(RED)Sending two requests in parallel $(RESET)"
	@for i in {1..2}; do \
		./columnarc 127.0.0.1 3307 test & \
	done
	@echo -e "$(RED)Disable kernel tracing $(RESET)"
	@source ~/.bash_profile && stop_kernel_tracing
	
