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

    if (this == NULL) {
        printf("Memory Allocation failed.\n");
        return NULL; // Out of memory...
    }

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

//Frees up or dynamically allocated memory
void DFA_free(DFA dfa) {
    //check if pointer == null before dereferencing -> it can prevent crashes
    free(dfa->states);
    free(dfa);
}

//returns size of DFA
int DFA_get_size(DFA dfa) {
    return dfa->nStates;
}

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 */
int DFA_get_transition(DFA dfa, int currState, char input) {
    //currState represents what state you are currently on
    //input represents the current input character. we check if this input character either stays at curr state. or goes to next state.
    //the next state for valid input is defined in DFA_set_transition
    //so this function returns what state you go to next. either stay or go to another state
    return dfa->states[currState].inputAlphabet[input];

}

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 * state "destination state"?
 */
void DFA_set_transition(DFA dfa, int sourceState, char input, int destinationState) {
    //void function because we are simply accessing the 2d array and assigning it the destination State
    //ex: for pattern csc
    //at state[1].theInputAlphabetWillBe[this letter char].
/**
    since ascii values are assigned a numerical value, we can place "char input" into our input alphabet array,which
    is of size 126, representing ascii alphabet. when we need to retrieve it, we can the numerical value
    can help us figure out which letter it represents
**/
    dfa->states[sourceState].inputAlphabet[input] = destinationState;
}

/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */
void DFA_set_transition_str(DFA dfa, int currState, char *string, int destinationState) {

}

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
void DFA_set_transition_all(DFA dfa, int src, int dst) {

}




