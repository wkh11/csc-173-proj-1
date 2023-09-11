//
// Created by Wei kang He on 9/10/23.
//

//in dfa.c we define our data structure

#include "dfa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct DFA {
    //include the five tuple here
    int nStates;
    //126 to represent the ascii alphabet, which encompasses every possible keyboard letter
    int startOrCurrState;
    int acceptingState;
    DFA_State states;
};
//relationship: DFA defines # of states, startingState. DFA_State is the transition table
struct DFA_State {
    //state "s" and symbol "x" can be represented as a table
        //one entry for each combo of s and x
        //transitionTable[number of states][all the ascii values go here. if not val we are looking for, set as -1]
    //each state has following information: where it can go next.
    //if it is the accepting state
    int inputAlphabet[10];
};

//now create new instance of a DFA
DFA new_DFA(int nStates) {
    //allows us to free space for DFA
    DFA this = (DFA)malloc(sizeof(struct DFA));
    this->nStates = nStates;
    this->startOrCurrState = 0;
    this->acceptingState = 10;
    //allows us to free space for DFA_State
    this->states = (DFA_State)malloc(sizeof(struct DFA_State));
    //psuedo code
        // at each state, n, set each of the values to false
    for (int i = 0; i < nStates; i++) {
        for (int j = 0; j < 10; j++) {
            //if val in transition table is set to -1, that means value is rejected
            this->states[i].inputAlphabet[j] = -1;
        }
    }
    //if there are 7 states, and state 7 is reached, which is the length of the states, then we return true
    return this;
}

void DFA_print(DFA dfa) {
    for (int i = 0; i < dfa->nStates; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d, ", dfa->states[i].inputAlphabet[j]);
        }
        printf("\n");
    }
}



