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

report_dir="$pwd/../report/stats/"

for framework in "${frameworks[@]}"
do
    for task in "${tasks[@]}"
    do
        echo "Getting $framework/$task RSS stats..."
        cd "$pwd/$framework/$task/"
        make clean
        make main
        report_file="$report_dir/rss-$framework-$task.txt"
        echo "" > $report_file
        /usr/bin/time -v "$pwd/$framework/$task/build/main" 2> "$report_file"
    done
done
