    for (int i = 0; i < 5; i++) {
        int rank = h->cards[i].rank;
        for (int j = 0; j < 5; j++) {
            if (rank == needed[j]) {
                found[j] = 1;
                break; // no need to check the rest
            }
        }
    }