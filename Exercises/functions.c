#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int rank;
    char suit;
} Card;

typedef struct {
    Card cards[5];
} Hand;

typedef struct{
    int rank_value;
    int tiebreaks[5];
} HandValue;

int top_of_straight(Hand *h){
    int counts[15] = {0};
    for (int i=0; i<5; i++) counts[h->cards[i].rank] = 1;

    for (int i=14; i>=5; i--){
        if (counts[i] && counts[i-1] && counts[i-2] && counts[i-3] && counts[i-4])
            return i;
    }
    if (counts[14] && counts[2] && counts[3] && counts[4] && counts[5])
        return 5;
    return 0;
}

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

    for (int i=0; i<5; i++){
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

HandValue n_of_a_kind(Hand *h){
    int counts[15] = {0};
    HandValue val = {0};

    for (int i = 0; i< 5; i++) counts[h->cards[i].rank]++;
    
    int max_1 = 0;
    int max_2 = 0;

    int rank_1 = 0;
    int rank_2 = 0;

    for (int i = 2; i < 15; i++){
        if (counts[i] > max_1){
            max_2 = max_1; rank_2 = rank_1;
            max_1 = counts[i]; rank_1 = i;
        } else if (counts[i] > max_2){
            max_2 = counts[i]; rank_2 = i;
        }
    }

    if (max_1 == 4){
        val.rank_value = 8;
        val.tiebreaks[0] = rank_1;

        for (int i = 14, k = 1; i >=2; i--){
            if (i!= rank_1 && counts[i]){
                val.tiebreaks[k++] = i;
            }
        }
    } else if (max_1 == 3 && max_2 == 2){
        val.rank_value = 7;
        val.tiebreaks[0] = rank_1;
        val.tiebreaks[1] = rank_2;
    } else if (max_1 == 3){
        val.rank_value = 4;
        val.tiebreaks[0] = rank_1;
        for (int i = 14, k = 1; i>= 2; i--){
            if (i != rank_1 && counts[i]){
                val.tiebreaks[k++] = i;
            }
        }
    } else if (max_1 == 2 && max_2 == 2){
        val.rank_value = 3;
        val.tiebreaks[0] = (rank_1 > rank_2) ? rank_1 : rank_2;
        val.tiebreaks[1] = (rank_1 > rank_2) ? rank_2 : rank_1;

        for (int i = 14; i >= 2; i--){
            if (counts[i] == 1){
                val.tiebreaks[2] = i;
            }
        }
    } else if (max_1 == 2) {
        val.rank_value = 2;
        val.tiebreaks[0] = rank_1;
        for (int i = 14, k = 1; i>=2; i--){
            if (i!= rank_1 && counts[i]){
                val.tiebreaks[k++] = i;
            }
        }
    } else {
        val.rank_value = 1;
        for (int i = 14, k = 0; i>=2; i--){
            if (counts[i]){
                val.tiebreaks[k++] = i;
            }
        }
    }

    return val;
}


HandValue hand_value(Hand *h){
    HandValue val = n_of_a_kind(h); 
    if (is_royal_flush(h)){
        val.rank_value = 10;
        return val;
    }
    if (is_straight_flush(h)){
        val.rank_value = 9;
        val.tiebreaks[0] = top_of_straight(h);
        return val;
    }
    if (is_flush(h)){
        val.rank_value = 6;
        int counts[15] = {0};
        for (int i = 0; i < 5; i++){
            counts[h->cards[i].rank]++;
        }
        for (int i = 14, k = 0; i >= 2; i--){
            if (counts[i]) val.tiebreaks[k++] = i;
        }
        return val;
    }
    if (is_straight(h)){
        val.rank_value = 5;
        val.tiebreaks[0] = top_of_straight(h);
        return val;
    }
    return val;
}


int compare_hands(HandValue a, HandValue b){
    if (a.rank_value != b.rank_value){
        return (a.rank_value > b.rank_value) ? 1: -1;}
    for (int i= 0; i < 5; i++){
        if (a.tiebreaks[i] != b.tiebreaks[i]){
            return (a.tiebreaks[i] > b.tiebreaks[i]) ? 1 : -1;
        }
    }
    return 0;
}

int main(){
    clock_t start = clock();

    Hand h2 = {{{14, 'S'}, {13, 'S'}, {12, 'S'}, {11, 'S'}, {10, 'S'}}};
    Hand h3 = {{{14, 'S'}, {13, 'S'}, {12, 'S'}, {11, 'S'}, {10, 'S'}}};
    Hand h1 = {{{10, 'H'}, {10, 'D'}, {10, 'C'}, {9, 'S'}, {9, 'H'}}};
    
    HandValue hv1 = hand_value(&h1);
    HandValue hv2 = hand_value(&h2);

    int result = compare_hands(hv1, hv2);
    if (result == 1){
        printf("Hand 1 wins\n");
    } else if (result == -1){
        printf("Hand 2 wins \n");
    } else {
        printf("It's an exact draw!\n");
    }

    clock_t end = clock();
    double elapsed = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Elapsed time: %.6f seconds\n", elapsed);

    return 0;
}