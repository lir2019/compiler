#!/bin/bash

set -x

rm build -r

./build.sh
./build/test_configure_file
./build/test_test
