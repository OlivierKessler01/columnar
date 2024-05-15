# Columnar : Yet another columnar store.
Columnar is a database managment system written in C++ with a strong C flavor.

It's a little concurrent system whose point is high performance over a single
thread for data agregation queries using an ANSI SQL compliant API.


## Compatibility
Columnar is only compatible with Linux over x86 patforms at the moment.

## Architecture documentation
[doc/architecture.md](doc/architecture.md)


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

# License
[MIT, see here](LICENCE.txt)




