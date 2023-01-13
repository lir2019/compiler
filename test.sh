#!/bin/bash

set -x
set -e

./build.sh

cd build

ctest -j 20
