#include <stdio.h>
#include <stdlib.h> // qsort
#include <stdbool.h> // bool
#include <string.h> // strncmp

#include <ctype.h>

#include "../utils.h"
// gcc part2.c -o part2.out -Wall; ./part2.out

struct node {
   char s[3];
   struct node *left;
   struct node *right;
};

int node_compare(const void* a, const void* b) {
    return strncmp( ((struct node*) a)->s, ((struct node*) b)->s, 3);
}

int bsearch_node_compare(const void* a, const void* b) {
    return strncmp((char*) a, ((struct node*) b)->s, 3);
}

// TODO: use unsigned __int128
// re: https://stackoverflow.com/questions/16088282/is-there-a-128-bit-integer-in-gcc

// we want to solve (ax + b) % c = d
size_t solve_crt(size_t a, size_t b, size_t c, size_t d) {
    if (a >= c) {
        size_t x = 0;
        size_t value = b;
        while (value != (d % c)) {
            value = (b + (a * x)) % c;
            x += 1;
        }
        return b + a * (x - 1);
    } else {
        return solve_crt(c, d, a, b);
    }
}

int main() {
    // TODO: CRLF normalize file automatically
    FILE* fp = fopen_expect("input", "r");
    const int NUM_LINES = count_lines(fp);
    rewind(fp);

    char instructions[2048];
    fgets(instructions, 2048, fp);
    fseek(fp, 1, SEEK_CUR);

    // remove newline from fgets
    size_t num_instructions = strlen(instructions) - 1;
    instructions[num_instructions] = '\0';

    struct node adj_list[NUM_LINES-2];

    const size_t LINE_SIZE = 3+3+10+1+1;
    for (size_t i = 0; i < NUM_LINES - 2; i++) {
        char line[LINE_SIZE];
        fgets(line, LINE_SIZE, fp);
        sscanf(line, "%3c", adj_list[i].s);
    }

    // sort adj_list so we can binary search it.
    qsort(adj_list, NUM_LINES-2, sizeof(struct node), node_compare);

    // 2 for number of newlines
    fseek(fp, num_instructions + 2, SEEK_SET);
    for (size_t i = 0; i < NUM_LINES - 2; i++) {
        char line[LINE_SIZE];
        fgets(line, LINE_SIZE, fp);

        char target[3], left[3], right[3];
        sscanf(line, "%3c = (%3c, %3c)", target, left, right);

        struct node* item = bsearch(target, adj_list, NUM_LINES-2, sizeof(struct node), node_compare);
        item->left  = bsearch(left, adj_list, NUM_LINES-2, sizeof(struct node), node_compare);
        item->right = bsearch(right, adj_list, NUM_LINES-2, sizeof(struct node), node_compare);
    }

    // count numbers, to init the lists
    int num_starts = 0;
    int num_ends = 0;
    for (size_t i = 0; i < NUM_LINES - 2; i++) {
        if (adj_list[i].s[2] == 'A') {
            num_starts += 1;
        } else if (adj_list[i].s[2] == 'Z') {
            num_ends += 1;
        }
    }

    if (num_starts != num_ends)
        exit_with_msg(1, "error: num_starts != num_ends");

    struct node* starts[num_starts];
    struct node* ends[num_ends];
    int si = 0, ei = 0;
    for (size_t i = 0; i < NUM_LINES - 2; i++) {
        if (adj_list[i].s[2] == 'A') {
            starts[si] = &adj_list[i];
            si++;
        } else if (adj_list[i].s[2] == 'Z') {
            ends[ei] = &adj_list[i];
            ei++;
        }
    }

    // the step at which each step was last at each end
    int last_at[num_starts][num_ends];
    int last_last_at[num_starts][num_ends];
    for (size_t ci = 0; ci < num_starts; ci++) {
        for (size_t ei = 0; ei < num_ends; ei++) {
            last_at[ci][ei] = -1;
            last_last_at[ci][ei] = -1;
        }
    }

    size_t steps = 0;
    while (true) {
        for (size_t si = 0; si < num_starts; si++) {
            if (instructions[steps % num_instructions] == 'L') {
                starts[si] = starts[si]->left;
            } else {
                starts[si] = starts[si]->right;
            }
        }

        steps += 1;

        // check for repetitions
        bool at_least_one = false;
        for (size_t si = 0; si < num_starts; si++) {
            if (starts[si]->s[2] == 'Z') {
                for (size_t ei = 0; ei < num_ends; ei++) {
                    if (starts[si] == ends[ei]) {
                        last_last_at[si][ei] = last_at[si][ei];
                        last_at[si][ei] = steps;
                        break;
                    }
                }
                at_least_one = true;
            }
        }

        if (at_least_one) {
            bool all_cycles = true;
            size_t cycle_size[num_starts];
            size_t cycle_offset[num_starts];
            for (size_t ci = 0; ci < num_starts; ci++) {
                bool has_a_cycle = false;
                for (size_t ei = 0; ei < num_ends; ei++) {
                    if (last_at[ci][ei] != -1 && last_last_at[ci][ei] != -1) {
                        cycle_size[ci] = (last_at[ci][ei] - last_last_at[ci][ei]);
                        cycle_offset[ci] = steps - last_at[ci][ei];
                        has_a_cycle = true;
                        break;
                    }
                }
                if (has_a_cycle == false) { 
                    all_cycles = false;
                    break;
                }
            }

            if (all_cycles) {
                size_t total_steps = 0;

                // TODO: how to make sure that the CRT can be applied to multiple layers & the cycle size is known?
                //for (size_t ci = 0; ci < num_starts; ci++) {
                //    printf("attempt: %ld\n", solve_crt(20777, 41554, 15517, 41554-10520));
                //}

                //printf("size: %ld, offset: %ld\n", cycle_size[ci], cycle_offset[ci]);
                //printf("steps: %ld\n", steps);
                return 0;
            }
        }
    }
}
