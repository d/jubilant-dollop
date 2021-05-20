# How to build and run tests

```shell
# generate build system with debug info and ASAN
CXXFLAGS='-fsanitize=address' hack/hack gen Debug build.debug
# build and run tests
hack/hack test build.debug
```

# Design
## Query

This is an object that

1. parses a textual representation of a query; 
1. creates operators (explained below), and wires them up.
   
For more details, see [the test](query_test.cc)

## RecordSet

I really should have called this "Operator", but it's too late when I realized that. This is an interface with two methods:

1. `AttributeNames`
1. `Records`

### Base table (FROM)

Reads file and parses them.

### Projection (SELECT)

Calculates a projection (column mapping), then perform that over each input record.

### Limit (TAKE)

Passes through the input but truncates at specified limit

### Sort (ORDERBY)

This made me feel a bit "yuck" because I chose to represent records as a sequence of strings. Anyway, held my nose and sorted by numeric value on the order key.

### Join (JOIN)

The `JOIN foo a` syntax actually leads to _two_ operators:

1. a base table scan (FROM) for file `foo`
1. a natural join between the "current" relation and the just-created base table scan on join key `a`

### Aggregate (COUNTBY)

Aggregate using a hash table (`unordered_map`).

## OperatorFactory and FsProvider

Almost the first thing written. Having the two interfaces allowed us to:

1. Defer implementing the _actual_ logic of processing data while designing the parsing (Query) class
1. Defer implementing the _actual_ file processing logic while designing base table scan (FROM)
1. Quickly iterate on the main interface. More iterations led to better designs!

### OperatorFactor
Well, in the absence of a good dependency injection framework, had to write the boring wiring code here.

### FsProvider

This is the minimal interface we use to interact with the file system: given a string, return an `std::istream`

# My compiler / standard library is too old

Welp, contact me to change the code, or try the following neat Docker trick:

```shell
unzip assignment-data.zip
# this will build our code in a Docker container image, and run it in a container
# If you see a blinking cursor on a blank line, it is ready for query input
# type in queries, or press Ctrl-D to terminate input
hack/test-in-docker
```
