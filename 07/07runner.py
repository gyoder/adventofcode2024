import ctypes
import os
import time

c_lib = ctypes.CDLL(os.path.join(os.path.dirname(__file__), '07lib.so'))

# int valid_operation(int sum, int nums[], int size, int cursum, int id) {
c_lib.valid_operation.argtypes = (ctypes.c_uint64, ctypes.POINTER(ctypes.c_uint64), ctypes.c_uint64, ctypes.c_uint64, ctypes.c_uint64)
c_lib.valid_operation.restype = ctypes.c_uint64

total = 0
with open('input.txt') as f:
    data = f.read().strip().split('\n')
    starttime = time.time()
    for line in data:
        sum = int(line.split(': ')[0])
        nums = [int(x) for x in line.split(': ')[1].split(' ')]
        n = len(nums)
        nums = (ctypes.c_uint64 * n)(*nums)
        total += int(c_lib.valid_operation(sum, nums, len(nums), 0, 0))
        #print(total)
    # print time in milliseconds
    print((time.time() - starttime)*1000)

print(total)
