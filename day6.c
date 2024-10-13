#include <stdio.h>
#include <math.h>

struct two_pair {
    int a;
    int b;
};

// x * (n - x) = s => - x^2 + nx - s = 0
struct two_pair solve(int n, int s) {
    int smaller = (int) ceil(
        ((double)n - sqrt((double)(n*n - 4*s))) / 2.0
    );
    int larger  = (int) floor(
        ((double)n + sqrt((double)(n*n - 4*s))) / 2.0
    );
    return (struct two_pair){
        .a=smaller,
        .b=larger,
    };
}

int main() {
    int time[4];
    int distance[4];

    FILE* fptr = fopen("test", "r");
    if (fptr == NULL) {
        printf("could not find input\n");
        return 1;
    }
    
    fscanf(fptr, "%*[a-zA-Z]: %d %d %d ", &time[0], &time[1], &time[2]);
    fscanf(fptr, "%*[a-zA-Z]: %d %d %d ", &distance, distance+4, distance+8);

    printf("%d\n", time[0]);
    printf("%d\n", time[1]);
    printf("%d\n", distance[1]);

    int total = 1;
    for (int i = 0; i < 3; i++) {
        struct two_pair result = solve(time[i], distance[i]);
        total *= (result.b - result.a + 1); 
    }

    printf("total %d\n", total);
    return 0;
}
