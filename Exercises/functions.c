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
    return 1;
}

int hand_rank(Hand *h){
    if (is_royal_flush(h)) return 10;
    if (is_flush(h)) return 6;
    return 1;
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