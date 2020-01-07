#!/bin/bash

declare -a frameworks=("llvm" 
                      "jitbuilder"
                      "native"
                     )

declare -a tasks=("increment"
                 "recursive-fib"
                 "iterative-fib"
                )

cd "$(dirname "$0")"
pwd=$PWD

for framework in "${frameworks[@]}"
do
    for task in "${tasks[@]}"
    do
        echo "Running $framework/$task benchmarks..."
        cd "$pwd/$framework/$task/"
        make run-bench > bench-results.txt
    done
    cd ..
done
