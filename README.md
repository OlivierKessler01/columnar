# Columnar
Columnar is a database managment system written in C and following the C90 standard.

It's a little concurrent system whose point is high performance over a single thread for data agregation queries using
an ANSI SQL compliant API.

## SQL interpreter structure
![Interpreter](interpreter.png)
### 1. Lexical Analyser
 The goal of lexical analysis is to split the request into a collecton of elements of various types.

"SELECT A FROM B WHERE B =1;" =>
{
    "SELECT": keyword,
    " ": whitespace,
    "A": identifier,
    "FROM": keyword,
    "B" : identifier,
    "WHERE": keyword,
    "B": identifier,
    " ": whitespace,
    "=": equal sign,
    "1": integer,
    ";": semicolon
}

### 2. Synthax Analyser / Parser

### 3. Semantical Analyser

### 4. Intermediate execution plan generator
 This phase's goal is the generate an execution plan from the elements understood in the previous phases.
 An execution plan is

### 5. Execution plan optimizer





# Compatibility
Columnar is only compatible with Linux over x86 patforms at the moment.

# Installation
## Using docker

## Using the source
```sh
# Get the source
git clone git@github.com:OlivierKessler01/columnar.git
# Compile the source
make
# Run the daemon
./columnar
```

# Contributing
This project is open to contributors, especially if you have some experience with concurrent C programming.

# Run the tests

# License





