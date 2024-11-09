#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include <bits/stdc++.h>
using namespace std;

typedef struct {
    int value;
    int state[6][6][6];
} CUBE;

// Deklarasi fungsi
int findValue(CUBE c);
CUBE highestSuccessor(CUBE c);
CUBE randomSuccessor(CUBE c);
void generateInitialState(CUBE *c);
void printState(CUBE c);

#endif // LOCALSEARCH_H
