#!/bin/bash

cmake -DCMAKE_BUILD_TYPE= -G "CodeBlocks - Unix Makefiles"

make

./RunFunctionTests
