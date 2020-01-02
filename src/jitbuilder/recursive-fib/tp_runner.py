import csv
import glob
import math
import os
import statistics
import subprocess
import sys

print("Clearing old results")
for f in glob.glob("./build/tp_results/*"):
    os.remove(f)

count = 100

max_time_sec = 0
max_time_ns = 10000000
ns_bucket_size = 500000

out_path = "build/tp_results/"
print("Running " + str(count) + " throughput tests...")

for t in range(1, count):
    file_name = out_path + str(t).zfill(3) + ".txt"
    subprocess.run(["./build/tp", str(file_name), str(max_time_sec), str(max_time_ns)])
    
print("Finished running tests")

results = {}

# discard first 10 runs
for t in range(10, count):
    run_index = t - 9
    with open(out_path + str(t).zfill(3) + ".txt") as f:
        print(out_path + str(t).zfill(3) + ".txt")
        for i in f:
            bucket = ( int(i) // ns_bucket_size ) * ns_bucket_size
            if bucket in results:
                if run_index in results[bucket]:
                    results[bucket][run_index] += 1
                else:
                    results[bucket][run_index] = 1
            else:
                results[bucket] = { run_index : 1 }

# printing results 

print("bucket_size={}, num_buckets={}".format(ns_bucket_size, len(results)))

last_bucket = list(results.keys())[-1]

# print out csv 
# last_bucket_1 is a hack to get inclusive range
table = []
for bucket in range(0, last_bucket + 1, ns_bucket_size):
    data = [bucket]
    for t in range(10, count):
        run_index = t - 9
        if bucket in results:
            if run_index in results[bucket]:
                data.append(results[bucket][run_index])
            else:
                data.append(0)
        else:
            data.append(0)
    # each row contains bucket_index, avg, std_deviation, confidence
    row = [data[0]]

    avg = sum(data[1:]) / ( len(data) - 1 )
    row.append(avg)
    
    std = statistics.stdev(data[1:])
    row.append(std)
    
    confidence = std / math.sqrt(len(data) - 1)
    row.append(confidence)

    table.append(row)

writer = csv.writer(sys.stdout)
writer.writerows(table)