#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <fcntl.h>
#include <unistd.h>

#define LEN 130

int dirarr[] = {-1, 0, 1, 0};

void clone_maze(char dest[LEN][LEN], char src[LEN][LEN]) {
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

int inf_loop_check(char newmaze[LEN][LEN], int r, int c) {

    int dir = 0;
    newmaze[r][c] = dir;
    while (r + dirarr[dir % 4] >= 0 && c + dirarr[(dir + 1) % 4] >= 0 && r + dirarr[dir % 4] < LEN && c + dirarr[(dir + 1) % 4] < LEN) {
        if (newmaze[r + dirarr[dir % 4]][c + dirarr[(dir + 1) % 4]] == '#') dir++;
        if (newmaze[r + dirarr[dir % 4]][c + dirarr[(dir + 1) % 4]] == '#') dir++;
        r += dirarr[dir % 4]; 
        c += dirarr[(dir + 1) % 4];
        if (newmaze[r][c] == dir % 4) 
            return 1;
        else if (dir == '.') newmaze[r][c] = dir % 4;
    }
    return 0;
}

int main() {
    int f = open("input.txt", 'r');
    char maze[LEN][LEN];
    for (int i = 0; i < LEN; i++) {
        read(f, maze[i], LEN);
        //printf("%s", maze[i]);
        lseek(f, 1, SEEK_CUR);
    }

    char orgmaze[LEN][LEN];
    clone_maze(orgmaze, maze);

    int r = 0;
    int c = 0;
    
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            if (maze[i][j] == '^') {
                r = i;
                c = j;
                break;
            }
        }
    }

    int startr = r;
    int startc = c;


    // maze[r][c] = 'X';
    int dir = 0;
    // while (r + dirarr[dir % 4] >= 0 && c + dirarr[(dir + 1) % 4] >= 0 && r + dirarr[dir % 4] < LEN && c + dirarr[(dir + 1) % 4] < LEN) {
    //     if (maze[r + dirarr[dir % 4]][c + dirarr[(dir + 1) % 4]] == '#') dir++;
    //     r += dirarr[dir % 4]; 
    //     c += dirarr[(dir + 1) % 4];
    //     maze[r][c] = 'X';
    // }

    int count = 0;

    for (int i = 0; i < LEN; i++)
        for (int j = 0; j < LEN; j++)
            if (maze[i][j] == 'X')
                count++;
    
    printf("Answer: %d\n", count);

    // for (int i = 0; i < LEN; i++) {
    //     for (int j = 0; j < LEN; j++) {
    //         printf("%c", maze[i][j]);
    //     }
    //     printf("\n");
    // }

    int count2 = 0;

    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            if (i == 6 && j == 3) {
                printf("");
            }
            dir = 0;
            if (maze[i][j] == '.') {
                char newmaze[LEN][LEN];
                clone_maze(newmaze, orgmaze);
                newmaze[i][j] = '#';
                r = startr;
                c = startc;
                newmaze[r][c] = dir + 48;
                while (r + dirarr[dir % 4] >= 0 && c + dirarr[(dir + 1) % 4] >= 0 && r + dirarr[dir % 4] < LEN && c + dirarr[(dir + 1) % 4] < LEN) {
                    if (newmaze[r + dirarr[dir % 4]][c + dirarr[(dir + 1) % 4]] == '#') dir++;
                    if (newmaze[r + dirarr[dir % 4]][c + dirarr[(dir + 1) % 4]] == '#') dir++;
                    r += dirarr[dir % 4]; 
                    c += dirarr[(dir + 1) % 4];
                    if (newmaze[r][c] == (dir % 4) + 48) {
                        count2++;
                        break;
                    }
                    else if (newmaze[r][c] == '.') 
                        newmaze[r][c] = (dir % 4) + 48;
                }
            }
        }
    }
                
    printf("Answer: %d\n", count2);
    

}


