#include <stdio.h>
#include <stdlib.h> // qsort
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <ctype.h>
#include <math.h>
#include <sys/types.h>

#include "../utils.h"
// gcc part2.c -lm -o part2.out -Wall; ./part2.out

enum HandType {
    HIGH_CARD = 0,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_KIND,
    FULL_HOUSE,
    FOUR_OF_KIND,
    FIVE_OF_KIND
};

struct Hand {
    // enum HandType type; // optimization?
    char hand_str[5];
    char hand_str_sorted[5];
    int bet;
};

enum HandType evaluateHand(const char hand_str_sorted[5]) {
    int num_cards[5];
    num_cards[0] = 1;
    int num_diff_cards = 1;

    // handle which num_card bucket is the joker
    int joker_index = -1;
    if (hand_str_sorted[0] == 'J')
        joker_index = 0;

    char last_card = hand_str_sorted[0];
    for (size_t ci = 1; ci < 5; ci++) {    
        if (hand_str_sorted[ci] == last_card) {
            num_cards[num_diff_cards-1] += 1;
        } else {
            num_diff_cards += 1;
            num_cards[num_diff_cards-1] = 1;
            last_card = hand_str_sorted[ci];

            // track which bucket contains jokers
            if (hand_str_sorted[ci] == 'J')
                joker_index = num_diff_cards-1;
        }
    }

    // if there are jokers, add them to the largest bucket
    if (joker_index != -1) {
        if (num_diff_cards == 1)
            return FIVE_OF_KIND;

        int num_joker_cards = num_cards[joker_index];
        num_cards[joker_index] = num_cards[num_diff_cards-1];
        num_diff_cards -= 1;

        int max_val = -1;
        int max_i = -1;
        for (size_t i = 0; i < num_diff_cards; i++) {
            if (num_cards[i] > max_val) {
                max_val = num_cards[i];
                max_i = i;
            }
        }

        num_cards[max_i] += num_joker_cards;
    }

    // this copy isn't strictly necessary but makes for more readable code
    int sorted_num_cards[5];
    memcpy(sorted_num_cards, num_cards, 5 * sizeof(int));
    qsort(sorted_num_cards, num_diff_cards, sizeof(int), compare_int_desc);

    if (sorted_num_cards[0] == 5) {
        return FIVE_OF_KIND;
    } else if (sorted_num_cards[0] == 4) {
        return FOUR_OF_KIND;
    } else if (sorted_num_cards[0] == 3 && sorted_num_cards[1] == 2) {
        return FULL_HOUSE;
    } else if (sorted_num_cards[0] == 3 && sorted_num_cards[1] == 1) {
        return THREE_OF_KIND;
    } else if (sorted_num_cards[0] == 2 && sorted_num_cards[1] == 2) {
        return TWO_PAIR;
    } else if (sorted_num_cards[0] == 2 && sorted_num_cards[1] == 1) {
        return ONE_PAIR;
    } else {
        return HIGH_CARD;
    }
}

int cardValue(char card) {
    if (card >= '2' && card <= '9') {
        return card - '2';
    } else if (card == 'T') {
        return 8;
    } else if (card == 'J') {
        return -100; // WEAKEST
    } else if (card == 'Q') {
        return 10;
    } else if (card == 'K') {
        return 11;
    } else if (card == 'A') {
        return 12;
    } else {
        printf("got %x\n", card);
        exit_with_msg(2, "invalid card");
        return -1; // dead code
    }
}

int compareHands(const void* ptr1, const void* ptr2) {
    struct Hand* a = (struct Hand*) ptr1;
    struct Hand* b = (struct Hand*) ptr2;

    const int FIRST = -1;
    const int EQUAL = 0;
    const int LAST = 1;

    enum HandType hand_a = evaluateHand(a->hand_str_sorted);
    enum HandType hand_b = evaluateHand(b->hand_str_sorted);

    if (hand_a > hand_b) {
        return FIRST;
    } else if (hand_a < hand_b) {
        return LAST;
    } else {
        for (int i = 0; i < 5; i++) {
            int card_value_a = cardValue(a->hand_str[i]);
            int card_value_b = cardValue(b->hand_str[i]);
            if (card_value_a > card_value_b) {
                return FIRST;
            } else if (card_value_a < card_value_b) {
                return LAST;
            }
        }
        return EQUAL;
    }
}

int main() {
    FILE* fp = fopen_expect("input", "r");
    const int NUM_LINES = count_lines(fp);
    rewind(fp);

    struct Hand hand_buff[NUM_LINES];

    for (size_t i = 0; i < NUM_LINES; i++) {
        fscanf(fp, "%5s %d ", hand_buff[i].hand_str, &hand_buff[i].bet);
        memcpy(hand_buff[i].hand_str_sorted, hand_buff[i].hand_str, 5);
        qsort(hand_buff[i].hand_str_sorted, 5, sizeof(char), compare_char);
    }
    if (fclose(fp) == EOF)
        exit_with_msg(1, "failed to close file");

    qsort(hand_buff, NUM_LINES, sizeof(struct Hand), compareHands);

    // see order
    //for (size_t i = 0; i < NUM_LINES; i++) {
    //    printf("%.5s\n", hand_buff[i].hand_str);
    //}

    uint64_t total = 0;
    for (size_t i = 0; i < NUM_LINES; i++) {
        total += (NUM_LINES - i) * hand_buff[i].bet;
    }

    printf("total %ld\n", total);
    return 0;
}