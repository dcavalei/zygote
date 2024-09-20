#!/usr/bin/env bash

docker build . -t zygote-sdk:local;
docker run --rm -it -u $(id -u):$(id -g) -v $PWD:/workspace zygote-sdk:local bash
