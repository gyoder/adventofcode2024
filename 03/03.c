#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <fcntl.h>
#include <unistd.h>

#define A 0
#define B 1 
/*
part a
int main() {
    int f = open("input.txt", 'r');
    int a[1000];
    int b[1000];
    int aa = -1;
    char as[3];
    int bb = -1;
    char bs[3];
    char nums[6];
    int len = 0;
    int aob = 0;
    int n = 0;
    char c;
    char expectedNextChar = defaultNextChar;
    while ((read(f, &c, 1)) == 1) {
        if (c == expectedNextChar) {
            // printf("%c", c);
            if (c == 'm') {
                if (n == 13) {
                    c = c;
                }
                expectedNextChar = 'u';
            } else if (c == 'u') {
                expectedNextChar = 'l';
            } else if (c == 'l') {
                expectedNextChar = '(';
            } else if (c == '(') {
                expectedNextChar = '\255';
            } else if (c == ')') {
                // win condition
                a[n] = (nums[0] - '0') * 100 + (nums[1] - '0') * 10 + (nums[2] - '0');
                b[n] = (nums[3] - '0') * 100 + (nums[4] - '0') * 10 + (nums[5] - '0');
                n++;
                for (int i = 0; i < 6; i++) nums[i] = 0;
                len = 0;
                aob = A;
                expectedNextChar = defaultNextChar;
            } else if (c == ',') {
                expectedNextChar = '\255';
                aob = B;
                len = 0;
            }
        } else if (expectedNextChar == '\255' && c >= '0' && c <= '9') {
            nums[len + 3 * aob] = c;
            len++;
        } else if (expectedNextChar == '\255' && c == ',') {
            if (len == 2) {
                nums[2] = nums[1]; 
                nums[1] = nums[0]; 
                nums[0] = '0';
            }
            if (len == 1) {
                nums[2] = nums[0]; 
                nums[1] = '0'; 
                nums[0] = '0';
            }
            expectedNextChar = '\255';
            aob = B;
            len = 0;
        } else if (expectedNextChar == '\255' && c == ')') {
            if (len == 2) {
                nums[5] = nums[4]; 
                nums[4] = nums[3]; 
                nums[3] = '0';
            }
            if (len == 1) {
                nums[5] = nums[3]; 
                nums[4] = '0'; 
                nums[3] = '0';
            }
            // win condition
            a[n] = (nums[0] - '0') * 100 + (nums[1] - '0') * 10 + (nums[2] - '0');
            b[n] = (nums[3] - '0') * 100 + (nums[4] - '0') * 10 + (nums[5] - '0');
            n++;
            for (int i = 0; i < 6; i++) nums[i] = 0;
            len = 0;
            aob = A;
            expectedNextChar = defaultNextChar;
        } else {
            for (int i = 0; i < 6; i++) nums[i] = 0;
            len = 0;
            aob = A;
            expectedNextChar = defaultNextChar;
        }
    }
    printf("got %d valid results\n", n);

    u_int64_t sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }

    printf("Part 1 Sum: %llu\n", sum);

}
*/

enum {
    MUL,
    DO,
    DONT
};

int main() {
    int f = open("input.txt", 'r');
    int a[1000];
    int b[1000];
    int aa = -1;
    char as[3];
    int bb = -1;
    char bs[3];
    char nums[6];
    int len = 0;
    int aob = 0;
    int started_dont = 0;
    int n = 0;
    char c;
    char defaultNextChar = 'm';
    char expectedNextChar = defaultNextChar;
    while ((read(f, &c, 1)) == 1) {
        if (c == expectedNextChar || c == 'd') {
            // printf("%c", c);
            if (c == 'm') {
                if (n == 13) {
                    c = c;
                }
                expectedNextChar = 'u';
            } else if (c == 'u') {
                expectedNextChar = 'l';
            } else if (c == 'l') {
                expectedNextChar = '(';
            } else if (c == '(') {
                expectedNextChar = '\255';
            } else if (c == 'd') {
                expectedNextChar = 'o';
                for (int i = 0; i < 6; i++) nums[i] = 0;
                len = 0;
                aob = A;
                started_dont = 0;
            } else if (c == 'o') {
                expectedNextChar = '\254';
            } else if (c == 'n') {
                expectedNextChar = '\'';
            } else if (c == '\'') {
                expectedNextChar = 't';
            } else if (c == 't') {
                expectedNextChar = '\254';
            } else if (c == ')') {
                // win condition
                a[n] = (nums[0] - '0') * 100 + (nums[1] - '0') * 10 + (nums[2] - '0');
                b[n] = (nums[3] - '0') * 100 + (nums[4] - '0') * 10 + (nums[5] - '0');
                n++;
                for (int i = 0; i < 6; i++) nums[i] = 0;
                len = 0;
                aob = A;
                expectedNextChar = defaultNextChar;
            } else if (c == ',') {
                expectedNextChar = '\255';
                aob = B;
                len = 0;
            }
        } else if (expectedNextChar == '\254') {
            if (c == '(') {
                read(f, &c, 1);
                if (c == ')') {
                    if (started_dont == 0) {
                        expectedNextChar = 'm';
                        defaultNextChar = 'm';
                    }
                    else {
                        defaultNextChar = '\253';
                        expectedNextChar = '\253';
                        started_dont = 0;
                    }

                }
            } else if (c == 'n') {
                expectedNextChar = '\'';
                started_dont = 1;
            }
        } else if (expectedNextChar == '\255' && c >= '0' && c <= '9') {
            nums[len + 3 * aob] = c;
            len++;
        } else if (expectedNextChar == '\255' && c == ',') {
            if (len == 2) {
                nums[2] = nums[1]; 
                nums[1] = nums[0]; 
                nums[0] = '0';
            }
            if (len == 1) {
                nums[2] = nums[0]; 
                nums[1] = '0'; 
                nums[0] = '0';
            }
            expectedNextChar = '\255';
            aob = B;
            len = 0;
        } else if (expectedNextChar == '\255' && c == ')') {
            if (len == 2) {
                nums[5] = nums[4]; 
                nums[4] = nums[3]; 
                nums[3] = '0';
            }
            if (len == 1) {
                nums[5] = nums[3]; 
                nums[4] = '0'; 
                nums[3] = '0';
            }
            // win condition
            a[n] = (nums[0] - '0') * 100 + (nums[1] - '0') * 10 + (nums[2] - '0');
            b[n] = (nums[3] - '0') * 100 + (nums[4] - '0') * 10 + (nums[5] - '0');
            n++;
            for (int i = 0; i < 6; i++) nums[i] = 0;
            len = 0;
            aob = A;
            expectedNextChar = defaultNextChar;
            started_dont = 0;
        } else {
            for (int i = 0; i < 6; i++) nums[i] = 0;
            len = 0;
            aob = A;
            expectedNextChar = defaultNextChar;
            started_dont = 0;
        }
    }
    printf("got %d valid results\n", n);

    u_int64_t sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }

    printf("Part 1 Sum: %llu\n", sum);

}