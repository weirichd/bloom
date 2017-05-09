#!/bin/bash
make clean
docker run -v $PWD:/src/app -w=/src/app bloom_filter /bin/bash -c 'make && make mem_test'
docker run -v $PWD:/src/app -w=/src/app bloom_filter /bin/bash -c 'cd python && python stats_test.py'
