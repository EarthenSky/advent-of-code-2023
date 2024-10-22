#include <stdio.h>
#include <stdlib.h> // qsort
#include <string.h> // strncmp

#include <ctype.h>

#include "../utils.h"
// gcc part1.c -lm -o part1.out -Wall; ./part1.out

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

int main() {
    char start[3] = { 'A', 'A', 'A' };
    char end[3] = { 'Z', 'Z', 'Z' };
 
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

    struct node* current = &adj_list[0];
    if (strncmp(current->s, start, 3) != 0)
        exit_with_msg(1, "start is not correct...");

    size_t steps = 0;
    while (strncmp(current->s, end, 3) != 0) {
        if (instructions[steps % num_instructions] == 'L') {
            current = current->left;
        } else {
            current = current->right;
        }
        steps += 1;
    }

    printf("steps: %ld\n", steps);
}
