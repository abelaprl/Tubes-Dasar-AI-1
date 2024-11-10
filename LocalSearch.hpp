#ifndef LOCALSEARCH_HPP
#define LOCALSEARCH_HPP

typedef struct
{
    int value;
    int state[6][6][6];
} CUBE;

int findValue(CUBE c, int maxVal);
CUBE highestSuccessor(CUBE c);
CUBE randomSuccessor(CUBE c);
void generateInitialState(CUBE *c);
void printState(CUBE c);

#endif