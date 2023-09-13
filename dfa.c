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
    DFA_State states;
};
//relationship: DFA defines # of states, startingState. DFA_State is the transition table
struct DFA_State {
    //state "s" and symbol "x" can be represented as a table
        //one entry for each combo of s and x
        //transitionTable[number of states][all the ascii values go here. if not val we are looking for, set as -1]
    //each state has following information: where it can go next.
    //if it is the accepting state
    bool isAcceptingState;
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
    //allows us to free space for DFA_State
    this->states = (DFA_State)malloc(sizeof(struct DFA_State));
//    this->states->acceptingState = 10;

    for (int i = 0; i < nStates; i++) {
        //base case: initialize all current states to false
        this->states[i].isAcceptingState = false;
    }

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
void DFA_set_transition_str(DFA dfa, int src, char *str, int dst) {
    int currentState = src;
    for (int i = 0; str[i] != '\0'; i++) {
        char input = str[i];
        //edit made by wei: we do "dst + 1" because for ex: at state 0, if the pattern "csc" if input = c, it should transition to dst+1
        //which means state is accepted, now go to next state
        DFA_set_transition(dfa, currentState, input, dst+1);
        currentState = dst+1;  // Updates the current state for the next iteration
    }
}

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
void DFA_set_transition_all(DFA dfa, int src, int dst) {
    // Iterates through all possible input symbols (all the ASCII values 0 to 127)
    for (int input = 0; input < 128; input++) {
        DFA_set_transition(dfa, src, (char)input, dst);
    }
    //always run this method first before set_transition_str -> this assigns every value in the row the same val.
    //so on row 0, every value is assigned 0
}

/**
 * Set whether the given DFA's state is accepting or not.
 */
void DFA_set_accepting(DFA dfa, int acceptingState, bool value) {
    //here, we must go into the final state and set it equal to the final state number so that if it is reached, we return true
    //value = final state number
    dfa->states[acceptingState].isAcceptingState = value;
}

/**
 * Return true if the given DFA's state is an accepting state.
 */
bool DFA_get_accepting(DFA dfa, int state) {
    //given the dfa, and the current state, we check if that state was assigned to be the accepting_state
    return dfa->states[state].isAcceptingState;
}

bool DFA_execute(DFA dfa, char *input) {
    int currentState = dfa->startOrCurrState;
    for (int i = 0; input[i] != '\0'; i++) {
        char currentSymbol = input[i];
        // Get the next state based on the current state and input symbol
        int nextState = DFA_get_transition(dfa, currentState, currentSymbol);
        // If the transition leads to an invalid state, reject the input
        if (nextState == -1) {
            return false;
        }
        currentState = nextState; // Move to the next state
    }
    // Check if the final state is an accepting state
    return DFA_get_accepting(dfa, currentState);
}




