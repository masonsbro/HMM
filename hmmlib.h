#ifndef HMMLIB_H
#define HMMLIB_H

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

#endif