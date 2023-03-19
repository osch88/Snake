#!/bin/bash

if [[ -z "$1" ]]; then
	cmake -S . -B build/
	cmake --build build/
else
	cd build/
	cmake -S .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1
fi

