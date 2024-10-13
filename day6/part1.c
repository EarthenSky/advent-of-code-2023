#include <stdio.h>
#include <math.h>
// gcc part1.c -lm -o part1.out; ./part1.out

struct two_pair { int a; int b; };

// x * (n - x) = s => - x^2 + nx - s = 0
struct two_pair solve(int n, int s) {
    double inner = sqrt((double)(n*n - 4*s));
    int smaller = (int) floor(
        1.0 + ((double)n - inner) * 0.5
    );
    int larger = (int) ceil(
        -1.0 + ((double)n + inner) * 0.5
    );
    return (struct two_pair){ smaller, larger };
}

int main() {
    int time[4];
    int distance[4];

    FILE* fptr = fopen("input", "r");
    if (fptr == NULL) {
        perror("could not find './input' file");
        return 1;
    }

    fscanf(fptr, "%*[a-zA-Z]: %d %d %d %d ", time+0, time+1, time+2, time+3);
    fscanf(fptr, "%*[a-zA-Z]: %d %d %d %d ", distance+0, distance+1, distance+2, distance+3);

    int total = 1;
    for (int i = 0; i < 4; i++) {
        struct two_pair result = solve(time[i], distance[i]);
        total *= (result.b - result.a + 1);
        printf("%d from [%d, %d]\n", result.b - result.a + 1, result.a, result.b);
    }

    printf("total %d\n", total);

    if (fclose(fptr) == EOF) {
        perror("failed to close file");
        return 1;
    }
    return 0;
}
