#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


int main() {

    FILE *file;
    file = fopen("input.txt", "r");

    if (file == NULL)
        return 1;

    char line[1000];
    int i = 0;
    int safe = 0;
    while(fgets(line, sizeof(line), file) != NULL) {
        int32_t int_line[8];
        for (int i = 0; i < 8; i++) {
            int_line[i] = -1;
        }
        if (sscanf(line, "%" PRIi32 " %" PRIi32 " %" PRIi32 " %" PRIi32 " %" PRIi32 " %" PRIi32 " %" PRIi32 " %" PRIi32 "", &int_line[0], &int_line[1], &int_line[2], &int_line[3], &int_line[4], &int_line[5], &int_line[6], &int_line[7]) != 0) {
            int j = 0;
            // int valid = 1;
            int insafe = 0;
            for (int k = 0; k < 8; k++) {
                int n_int_line[7];
                for (int l = 0; l < 8; l++) {
                    if (l < k) {
                        n_int_line[l] = int_line[l];
                    } else if (l > k) {
                        n_int_line[l-1] = int_line[l];
                    } 
                }
                int valid = 1;
                int m = 0;
                if (n_int_line[0] < n_int_line[1]) {
                    m = 1;
                }
                j=0;  // i spent so fucking long debugging realizing i didnt move this line here from line 24 immma cry
                while (j < 6 && valid > 0) {
                    if (n_int_line[j+1] == -1) {
                        break;
                    }
                    // if (int_line[j] - int_line[j+1] == 0) {
                    //     // valid = 0;
                    //     valid--;
                    //     break;
                    // }
                    if (n_int_line[j + m] - n_int_line[j+1 - m] > 3 || n_int_line[j + m] - n_int_line[j+1 - m] <= 0) {
                        // valid = 0;
                        valid--;
                        //continue; // apparently continues are weird i guess
                    }
                    // if (int_line[j + m] - int_line[j+1 - m] <= 0) {
                    //     // valid = 0;
                    //     valid--;
                    //     // if (valid == 1) {
                    //     //     int_line[j + 1] = int_line[j];
                    //     // }
                    //     //continue;
                    // }
                    j++;
                }
                if (valid > 0) {
                    insafe = 1;
                }
            }
            safe += insafe;
            
        }
        
        i++;


    }

    printf("Read %d lines\n", i);
    
    printf("Answer: %d\n", safe);


}