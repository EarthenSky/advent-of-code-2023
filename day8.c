#include<stdio.h>
#include "../utils.h"

struct node {
   char[3] s;
   struct node *left;
   struct node *right;
};

int node_compare(void* a, void* b) {
    return strncmp(
        (struct node*) a.s,
        (struct node*) b.s,
        3
    );
}

int bsearch_node_compare(void* a, void* b) {
    return strncmp(
        (char*) a,
        (struct node*) b,
        3
    );
}

int main() {
    char[3] start = { 'A', 'A', 'A' };
    char[3] end = { 'Z', 'Z', 'Z' };
 
    FILE* fp = fopen_expect("input", "r");
    const int NUM_LINES = count_lines(fp);
    rewind(fp);

    char[2048] instructions;
    fgets(instructions, 2048, fp);
    fseek(fp, 1, SEEK_CUR);
    size_t num_instructions = strlen(instructions);

    struct node[NUM_LINES-2] adj_list;

    const size_t LINE_SIZE = 3+3+10+1+1;
    for (size_t i = 0; i < NUM_LINES - 2; i++) {
        char[LINE_SIZE] line;
        fgets(line, LINE_SIZE, fp);
        sscanf(line, "%3[A_Z]", adj_list[i].s);
    }

    # sort adj_list so we can binary search it.
    qsort(adj_list, NUM_LINES-2, sizeof(struct node), node_compare);

    fseek(fp, 1 + num_instructions, SEEK_SET);
    for (size_t i = 0; i < NUM_LINES - 2; i++) {
        char[LINE_SIZE] line;
        fgets(line, LINE_SIZE, fp);

        char[3] target, char[3] left, char[3] right;
        sscanf(line, "%.3[A_Z] = (%.3[A-Z], %.3[A-Z]) ", target, left, right);

        bsearch(target, adj_list, NUM_LINES-2, sizeof(struct node), node_compare);
    }

}
