# Columnar : Yet another columnar store.

Columnar is a database managment system written in C++ with a strong C flavor.

Columnar offers an ANSI SQL compliant API.

Columnar uses raw SQL over TCP/IP as Application and Transport protocols.



The server has **two different execution modes** you can choose from : 
* **Subprocessing** : Spawns a new process to handle each request. Offers high isolation between requests, compute parallelism over your multiple cores, at the cost of kernel overhead and limit in terms of number of concurrent requests. Suited for CPU-bound tasks (ex: some complex aggregation/window functions).
* **Async IO** : Uses a single process and a single thread to handle concurrent requests, but will treat disk IO asynchronously. All requests share heap, all requests share stack, and parallelism over multiple cores is not possible. Suited for IO-bound requests (ex: index lookups).

Client side, each request initiates a new TCP connection to the server.

## Compatiblity
Columnar is only compatible with Linux over x86 patforms at the moment.

## Architecture documentation
[doc/architecture.md](doc/architecture.md)

## Project directory structure

- [server/](server/) Server code
  - [dsa/](server/dsa) Various usefull data structures and algorithms.
  - [filesytem/](server/filesystem) Various POSIX-compatible utils to access the filesystem.
  - [parser/](server/parser) SQL grammar parser 
  - [scanner/](server/scanner) SQL synthax scanner 
  - [process/](server/process) Code handling the process/thread generation and network handling 
  - [query/](server/query) Query planner and executor 
- [client/](client/) Client code


## Installation & usage

* Installing the server 
```bash
# Get the source
git clone git@github.com:OlivierKessler01/columnar.git
# Update the configuration file
vim /etc/columnar/columnar.cnf
echo "log_file_path=/var/log/columnar.log" >> /etc/columnar/columnar.cnf

# If you want the server to spawn processes to handle requests
echo "run_mode=process" >> /etc/columnar/columnar.cnf
# Or using async ios via select() syscall 
echo "run_mode=async" >> /etc/columnar/columnar.cnf

# Compile the source of the server and run it
make server 
```

* Using the client in interactive mode
```bash
make client 
./columnarc 127.0.0.1 3307
#Prompt displays
> SELECT * FROM whatever table;
test test test
```

* Using the client for one-shot requests

```bash
make client 
./columnarc 127.0.0.1 3307 "SELECT * FROM whatever table;"
test test test
```

# Contributing
This project is open to contributors, especially if you have some experience with concurrent C programming.

# Run the tests
```bash
make tests
```
# Run the server + client
```bash
make run-dev
```

# Server syslogs
```bash
make log-server
journalctl -f | grep columnar
```

# License
[MIT, see here](LICENCE.txt)




