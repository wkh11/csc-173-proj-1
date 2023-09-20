#include <stdio.h>
#include "dfa.h"
#include "IntHashSet.h"



typedef struct string string;

int main() {
    // DFA_print(dfa1);
    IntHashSet test;
    test = "CSC";
    if (DFA_for_contains_CSC(test) == true) {
        std:cout << "The string " << test << " is accepted";
    }
    else {
        std:cout << "the string" << test << "is not accepted";
    }
    IntHashSet test2;
    test2 = "ending"
    if (DFA_for_contains_end(test2) == true){
        cout<<"The string" <<test<< "is accepted";

        else

    }
    //DFA_for_contains_CSC();
    //DFA_for_contains_end();
    //DFA_for_starts_with_vowel();
    return 0;
}




