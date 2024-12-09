#include <stdint.h>
#include <math.h>
uint64_t valid_operation(uint64_t sum, uint64_t nums[], uint64_t size, uint64_t cursum, uint64_t id) {
    if (id == size) 
    {
        if (cursum == sum) 
        {
            return sum;
        }
        return 0;
    }
    if (valid_operation(sum, nums, size, cursum + nums[id], id + 1) != 0)
    {
        return sum;
    }
    // if (valid_operation(sum, nums, size, cursum - nums[id], id + 1) != 0)
    // {
    //     return sum;
    // }
    if (valid_operation(sum, nums, size, cursum * nums[id], id + 1) != 0)
    {
        return sum;
    }
    // if (valid_operation(sum, nums, size, cursum / nums[id], id + 1) != 0)
    // {
    //     return sum;
    // }
    int s = 0;
    while (((int) (nums[id] / pow(10, s))) != 0) s++;
    if (valid_operation(sum, nums, size, cursum * pow(10, s) + nums[id], id + 1)) {
        return sum;
    }
    return 0;
}