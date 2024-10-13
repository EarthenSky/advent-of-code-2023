// TODO: what's this & how big?
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <ctype.h>
#include <math.h>
#include <sys/types.h>
// gcc part2.c -lm -o part2.out -Wall; ./part2.out

struct two_pair { int64_t a; int64_t b; };

// x * (n - x) = s => - x^2 + nx - s = 0
struct two_pair solve(int64_t n, int64_t s) {
    double inner = sqrt((double)(n*n - 4*s));
    int64_t smaller = (int) floor(
        1.0 + ((double)n - inner) * 0.5
    );
    int64_t larger = (int) ceil(
        -1.0 + ((double)n + inner) * 0.5
    );
    return (struct two_pair){ smaller, larger };
}

void exit_with_msg(int exit_code, const char* msg) {
    perror(msg);
    exit(exit_code);
}

// 0 false, 1 true -> true removes the character
void filter(char* str_out, int (*compare_function)(int)) {
    char* str_in = str_out;
    while (*str_in != '\0') {
        while (compare_function(*str_in) && *str_in != '\0')
            str_in += 1;

        *str_out = *str_in;
        str_out += 1;
        str_in += 1;
    }
    // assign new null terminator
    *str_out = *str_in;
}

int main() {
    int64_t time;
    int64_t distance;

    {
        FILE* fp = fopen("input", "r");
        if (fp == NULL)
            exit_with_msg(1, "could not find './input' file");

        char* line = NULL;
        size_t len = 0;
        ssize_t read = getline(&line, &len, fp);
        if (read == -1) exit_with_msg(1, "failed to read 1st line"); 
        filter(line, isspace);
        sscanf(line, "%*[a-zA-Z]:%ld", &time);

        read = getline(&line, &len, fp);
        if (read == -1) exit_with_msg(1, "failed to read 2nd line"); 
        filter(line, isspace);
        sscanf(line, "%*[a-zA-Z]:%ld", &distance);

        if (fclose(fp) == EOF)
            exit_with_msg(1, "failed to close file");
    }

    struct two_pair result = solve(time, distance);
    int64_t total = (result.b - result.a + 1);
    printf("%ld from [%ld, %ld]\n", result.b - result.a + 1, result.a, result.b);
    printf("total %ld\n", total);
    return 0;
}