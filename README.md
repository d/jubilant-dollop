# How to build and run tests

```shell
# generate build system with debug info and ASAN
CXXFLAGS='-fsanitize=address' hack/hack gen Debug build.debug
# build and run tests
hack/hack test build.debug
```
