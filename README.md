# Zygote

Simple program that will apply a seccomp filter to itself and execve() another process.
It will parse a configuration file and apply the corresponding filters.
```shell
mkdir build
cd build
cmake ..
cmake --build . --target all
./zygote/src/main/zygote -d --config=$(git rev-parse --show-toplevel)/zygote/res/dynamically-linked-default.yaml -- ./zygote/src/main/main_simple
```
