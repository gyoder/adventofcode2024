#include <stdio.h>
int sort_pages(int pages[], int come_before[], int plen, int arr_to_sort[], int alen) {
    int original[alen];
    for (int i = 0; i < alen; i++) {
        original[i] = arr_to_sort[i];
    }
    int sorted = 2;
    int count = 0;
    while (sorted != 0) {
        sorted = 1;
        for (int i = alen - 1; i >= 0; i-- ) {
            int companion_num = -1;
            int curr = arr_to_sort[i];
            for (int ind = 0; ind < plen; ind++) {
                if (pages[ind] == arr_to_sort[i]) {
                    companion_num = ind;
                    
                    for (int j = 0; j < i; j++) {
                        if (come_before[companion_num] == arr_to_sort[j]) {                        // bump all items back
                            int temp = arr_to_sort[j];
                            arr_to_sort[j] = arr_to_sort[i];
                            arr_to_sort[i] = temp;
                            sorted = 2;
                            break;
                        }
                        
                    }
                }
            }
        }
        count++;
        sorted--;
    }
    int real = 0;
    for (int i = 0; i < alen; i++) {
        if (original[i] != arr_to_sort[i]) real = 1;
    }
    if (real == 0) return 0;
    return arr_to_sort[alen/2];
}