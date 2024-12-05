#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <fcntl.h>
#include <unistd.h>

#define LEN 140

char word[] = "XMAS";

int is_valid(char maze[LEN][LEN], int r, int c, int num, int rmod, int cmod) {

    if (r < 0 || c < 0 || r >= LEN || c >= LEN) {
        return 0;
    }
    if (maze[r][c] != word[num]) {
        return 0;
    }
    //if (num > 0) printf("%c\n", maze[r][c]);
    if (num == 3) {
        printf("r: %02d, c: %02d\n", r - 3*rmod, c- 3*cmod);
        return 1;
    } 
    
    return is_valid(maze, r + rmod, c + cmod, num + 1, rmod, cmod);
    
}

int main() {
    int f = open("input.txt", 'r');
    char maze[LEN][LEN];
    char c[140];
    for (int i = 0; i < LEN; i++) {
        read(f, maze[i], LEN);
        //printf("%s", maze[i]);
        lseek(f, 1, SEEK_CUR);
    }

    int sum = 0;
    int sum2 = 0;

    is_valid(maze, 0, 12, 0, 1, 0);

    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            for (int r = -1; r <= 1; r++) {
                for (int c = -1; c <= 1; c++) {
                    sum += is_valid(maze, i, j, 0, r, c);

                }
            }
        }
    }

    printf("Anser: %d\n", sum);

    for (int i = 1; i < LEN - 1; i++) {
        for (int j = 1; j < LEN - 1; j++) {
            //printf("%d %d: %c, %c, %c, %c, %c: %d %d %d %d\n", i, j, maze[i][j], maze[i-1][j-1], maze[i-1][j+1], maze[i+1][j-1], maze[i+1][j+1], maze[i-1][j-1] + maze[i+1][j+1], maze[i-1][j-1] - maze[i+1][j+1], maze[i+1][j-1] + maze[i-1][j+1], maze[i+1][j-1] - maze[i-1][j+1]);
            sum2 += ((maze[i-1][j-1] + maze[i+1][j+1] == 'M' + 'S') && (abs(maze[i-1][j-1] - maze[i+1][j+1]) == 'S' - 'M')) && ((maze[i+1][j-1] + maze[i-1][j+1] == 'M' + 'S') && ((abs(maze[i+1][j-1] - maze[i-1][j+1]) == 'S' - 'M'))) && maze[i][j] == 'A';
        }
    }
    printf("Answer: %d\n", sum2);
}