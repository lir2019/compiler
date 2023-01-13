#!/bin/bash

set -x

rm build -r
./build.sh

log=tmp_log

./build/test_configure_file 2>&1 | tee $log
./build/test_lexer 2>&1 | tee -a $log
echo ====================== failed cases ========================
grep failure $log
