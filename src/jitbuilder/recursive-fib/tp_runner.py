import glob
import math
import os
import subprocess

print("Clearing old results")
for f in glob.glob("./build/tp_results/*"):
    os.remove(f)

count = 11

max_time_sec = 0
max_time_ns = 10000000
ns_bucket_size = 500000

out_path = "build/tp_results/"
print("Running " + str(count) + " throughput tests...")

for t in range(1, count):
    file_name = out_path + str(t).zfill(3) + ".txt"
    subprocess.run(["./build/tp", str(file_name), str(max_time_sec), str(max_time_ns)])
    
print("Finished running tests")

# group the method invocations at time t into buckets of size ns_bucket_size
# note trailing integer division '//'
num_buckets = ( (max_time_sec * 1000000000 + max_time_ns) // ns_bucket_size )

# create array of size num_buckets initialized to zero
result = [0] * ( num_buckets + 1 )

print("bucket_size=" + str(ns_bucket_size) + ", num_buckets=" + str(num_buckets))

# discard first 10 runs
for t in range(10, count):
    with open(out_path + str(t).zfill(3) + ".txt") as f:
        print(out_path + str(t).zfill(3) + ".txt")
        for i in f:
            print(i)
            print(int(i) // ns_bucket_size)
            result[int(i) // ns_bucket_size] += 1       

print(result)

