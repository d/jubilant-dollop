# How to build and run tests

```shell
# generate build system with debug info and ASAN
CXXFLAGS='-fsanitize=address' hack/hack gen Debug build.debug
# build and run tests
hack/hack test build.debug
```

# My compiler / standard library is too old

Welp, contact me to change the code, or try the following neat Docker trick:

```shell
unzip assignment-data.zip
# this will build our code in a Docker container image, and run it in a container
# If you see a blinking cursor on a blank line, it is ready for query input
# type in queries, or press Ctrl-D to terminate input
hack/test-in-docker
```
