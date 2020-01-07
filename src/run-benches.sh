#!/bin/bash

declare -a frameworks=("llvm" 
                      #"jitbuilder"
                      #"native"
                     )

declare -a tasks=("increment"
                 #"recursive-fib"
                 #"iterative-fib"
                )

cd "$(dirname "$0")"
pwd=$PWD

for framework in "${frameworks[@]}"
do
    echo "Running $f benchmark..."
    for task in "${tasks[@]}"
    do
        cd "$pwd/$framework/$task/"
        make run-bench > bench-results.txt
    done
    cd ..
done


#cd llvm/increment

#make clean
#make run-bench > bench-results.txt