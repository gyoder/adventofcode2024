import ctypes
import os

c_lib = ctypes.CDLL(os.path.join(os.path.dirname(__file__), '05lib.so'))

c_lib.sort_pages.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.POINTER(ctypes.c_int), ctypes.c_int)
c_lib.sort_pages.restype = ctypes.c_int

with open('input.txt') as f:
    data = f.read().strip().split('\n')
    pages = []
    comes_before = []
    arrays_to_sort = []
    before = True
    for line in data:
        if line == '':
            before = False
            continue
        if before:
            page = line.split('|')[0]
            pages.append(int(page))
            comes_before.append(int(line.split('|')[1]))
        else:
            arrays_to_sort.append([int(x) for x in line.split(',')])
n = len(pages)
pages = (ctypes.c_int * n)(*pages)
comes_before = (ctypes.c_int * n)(*comes_before)
sum = 0
for arr in arrays_to_sort:
    n = len(arr)
    arr = (ctypes.c_int * n)(*arr)
    #print(c_lib.sort_pages(pages, comes_before, len(pages), arr, len(arr)))
    sum += c_lib.sort_pages(pages, comes_before, len(pages), arr, len(arr))
    

print(sum)