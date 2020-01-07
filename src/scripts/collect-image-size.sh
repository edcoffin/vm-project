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

report_file="$pwd/../report/stats/image-sizes.txt"
echo "" > "$report_file" 

for framework in "${frameworks[@]}"
do
    for task in "${tasks[@]}"
    do
        echo "Getting $framework/$task image size..."
        cd "$pwd/$framework/$task/"
        make clean
        make main
        echo "$framework/$task" >> "$report_file"
        du -b build/main | cut -f 1 >> "$report_file"
    done
done
