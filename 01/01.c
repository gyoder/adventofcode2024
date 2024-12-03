#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void* a,const void* b) {
      return *(uint32_t*)a - *(uint32_t*)b;
}

int main() {
    uint32_t row_a[1000];
    uint32_t row_b[1000];

    FILE *file;
    file = fopen("input.txt", "r");

    if (file == NULL)
        return 1;

    char line[15];
    int i = 0;
    while(fgets(line, sizeof(line), file) != NULL) {
        int a, b;

        if (sscanf(line, "%d   %d", &a, &b) == 2) {
            row_a[i] = a;
            row_b[i] = b;
        }
        
        i++;


    }

    printf("Read %d lines\n", i);
    
    qsort(&row_a, 1000, 4, cmp);
    qsort(&row_b, 1000, 4, cmp);

    int sum = 0;
    for (int i = 0; i < 1000; i++) {
        sum += abs(row_a[i] - row_b[i]);
    }

    printf("Answer: %d\n", sum);


    sum = 0;

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (row_a[i] == row_b[j]) {
                sum += row_b[j];
            }
        }
    }

    printf("Answer: %d\n", sum);


}