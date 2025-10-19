#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rank;
    char suit;
} Card;

typedef struct {
    Card cards[5];
} Hand;

int is_flush(Hand *h){
    char first_suit = h->cards[0].suit;
    for (int i = 1; i< 5; i++) {
        if (h-> cards[i].suit != first_suit)
            return 0;
    }
    return 1;
}

int is_straight(Hand *h){
    int counts[15] = {0};
    int i;

    for (i=0; i<5; i++){
        int rank = h->cards[i].rank;
        counts[rank]++;
        if (counts[rank] >1){
            return 0;
        }
    }
    for (i = 2; i< 11; i++){
        if (counts[i] && counts[i+1] && counts[i+2] && counts[i+3] && counts[i+4]){
            return 1;
        }
    }
    if (counts[14] && counts[2] && counts[3] && counts[4] && counts[5]){
        return 1;
    }
    return 0;
}

int is_royal_flush(Hand *h){
    if (!is_flush(h))
        return 0;
    int needed[] = {10, 11, 12, 13, 14};
    int found[5] = {0};
    
    for (int i = 0; i < 5; i++){
        int rank = h->cards[i].rank;
        for (int j = 0; j < 5; j++){
            if (rank == needed[j]){
                found[j] = 1;
                break;}
        }
    }

    for (int i = 0; i < 5; i++){
        if (!found[i])
            return 0;
    }
    return 1;
}

int is_straight_flush(Hand *h){
    if (!is_flush(h))
        return 0;
    return is_straight(h);
}

int n_of_a_kind(Hand *h){
    int counts[15] = {0};
    for (int i = 0; i< 5; i++) counts[h->cards[i].rank]++;
    int max_1 = 0;
    int max_2 = 0;
    for (int i = 2; i<15; i++){
        if (counts[i] > max_1){
            max_2 = max_1;
            max_1 = counts[i];
        } else if (counts[i] > max_2) {
            max_2 = counts[i];
        }
    }
    if (max_1 == 4){return 8;}
    if (max_1 == 3 && max_2 == 2){return 7;}
    if (max_1 == 3 && max_2 != 2){return 4;}
    if (max_1 == 2 && max_2 == 2){return 3;}
    if (max_1 ==2 && max_2 != 2){return 2;}
    return 0;
}


int hand_rank(Hand *h){
    if (is_flush(h)){
        if (is_royal_flush(h)){
            return 10;
        }
        return 6;
    } else if (is_straight_flush(h)){
        return 9;
    }
    if (is_straight(h)){
        return 5;
    }
    return n_of_a_kind(h);
}

int main(){
    Hand h1 = {{{14, 'S'}, {13, 'S'}, {12, 'S'}, {11, 'S'}, {10, 'S'}}};
    Hand h2 = {{{10, 'H'}, {10, 'D'}, {10, 'C'}, {9, 'S'}, {9, 'H'}}};
    if (is_royal_flush(&h1)){
        printf("The first hand is a royal flush\n");
    } else {
        printf("The first hand is not a royal flush\n");
    }
    return 0;
}