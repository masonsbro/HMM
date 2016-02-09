#ifndef HMMLIB_H
#define HMMLIB_H

#include <stdio.h>

typedef struct HMM {
    int num_states;
    int num_tokens;
    int* state_distribution_total;
    int** state_distribution;
    char** tokens;
    int* token_distribution_total;
    int** token_distribution;
} HMM;

void load_HMM(FILE* stream, HMM* hmm);
void save_HMM(FILE* stream, HMM* hmm);
int generate_sequence(HMM* hmm, char** sequence, int max_length);

#endif