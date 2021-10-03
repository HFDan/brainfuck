#!/usr/bin/bash

cd build/
cmake "-G=Unix Makefiles" "-DCMAKE_C_COMPILER=/usr/bin/clang" ../
