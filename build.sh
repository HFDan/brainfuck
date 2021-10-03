#!/usr/bin/bash

cd build/ || exit
cmake "-G=Unix Makefiles" "-DCMAKE_C_COMPILER=/usr/bin/clang" ../
