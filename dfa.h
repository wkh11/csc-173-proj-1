//
// Created by Wei kang He on 9/10/23.
//

//the idndef(if not defined) and define statement are automatically generated when we create a header file
#ifndef UNTITLED_DFA_H
#define UNTITLED_DFA_H

#include <stdbool.h>

//structure tag
//all subsequent calls of DFA will not need to be declared as DFA*
typedef struct DFA* DFA;

typedef struct DFA_State* DFA_State;

//this is the type name: this is where we will define the data structure's 5tuple here. but it will be done in dfa.c
extern DFA new_DFA(int nStates);

//print DFA
extern void DFA_print(DFA dfa);

//extern keyword means that the variable can be accessed from anywhere in the program
extern void DFA_free(DFA dfa);

extern int DFA_get_size(DFA dfa);

extern int DFA_get_transition(DFA dfa, int src, char sym);

extern void DFA_set_transition(DFA dfa, int src, char sym, int dst);

extern void DFA_set_transition_str(DFA dfa, int src, char *str, int dst);

extern void DFA_set_transition_all(DFA dfa, int src, int dst);

extern void DFA_set_accepting(DFA dfa, int state, bool value);

extern bool DFA_get_accepting(DFA dfa, int state);

extern bool DFA_execute(DFA dfa, char *input);




#endif //UNTITLED_DFA_H
