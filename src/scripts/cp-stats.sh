#!/bin/bash

declare -a frameworks=("llvm" 
                      "jitbuilder"
                      "native"
                     )

declare -a tasks=("increment"
                 "recursive-fib"
                 "iterative-fib"
                )

cd "$(dirname "$0")/.."
pwd=$PWD

for framework in "${frameworks[@]}"
do
    for task in "${tasks[@]}"
    do
        cp "$pwd/$framework/$task/bench-results.txt" "$pwd/../report/stats/bench-$framework-$task.txt"
    done
done
