# Columnar : Yet another columnar store.

Columnar is a database managment system written in C++ with a strong C flavor.

Columnar offers an ANSI SQL compliant API.

Client side, each request spawns a new process, which initiates a new TCP 
connection to the server.

Server side, each connection spawns a new process.

## Compatibility
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
# Compile the source of the server and run it
make server 
```

* Using the client
```bash
make client 
./columnarc 127.0.0.1 3307
#Prompt displays
> SELECT * FROM whatever table;
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




