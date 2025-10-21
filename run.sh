#!/bin/bash

cmake --build build -t Lib
if [ $? -eq 0 ]; then
    echo
    build/libbst "${@:1}" 2>&1
fi
