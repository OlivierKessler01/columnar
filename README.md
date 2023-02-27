# Columnar
Columnar is a database managment system written in C and following the C90 standard.

It's a little concurrent system whose point is high performance over a single thread for data agregation queries using
an ANSI SQL compliant API.

## SQL interpreter structure
![Interpreter](interpreter.png)

### Literrature

The understand the following lines, one might want to refer to the "Dragon book" as a compiler reference, and/or
the Stanford SOE.YCSCS1 Compiler course.

### 1. Lexical Analyser
 The goal of lexical analysis is to split the request into a collecton of elements of various types.

```json
"SELECT A FROM B WHERE B =1;" :
{
    "<lexeme>: "<token class>",
    "SELECT": "keyword",
    " ": "whitespace",
    "A": "identifier",
    "FROM": "keyword",
    "B" : "identifier",
    "WHERE": "keyword",
    "B": "identifier",
    " ": "whitespace",
    "=": "equal sign",
    "1": "integer",
    ";": "semicolon"
}
```

To do so, it reads the string from left to right, and uses bounded lookahead. Reservered keywords help minimizing the
amount of lookahead, but it's still needed in some cases.

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





