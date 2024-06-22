#ifndef EXAMPLESORT_H
#define EXAMPLESORT_H

#include <vector>

// Revision History:
// Rev. 2 - 90/02/11 Modified by Joe Smith
// - to add third parameter to function sort.
// (Note: It is also good to document WHY each
// particular change was made).
// Rev. 1 - 89/03/19 Original by R. Tront
//----------------------------------------------------------
// This module hides the implementation of the sorting algorithms. The exported
// function is called qualified by a flag as to whether the data to be sorted is
// mostly sorted already. The algorithm used for unsorted data may in future need
// to change depending on the database size. Cmpt 275: You should also mention in
// the module header comment, in addition to what is being hidden/abstracted, why
// these functions and other attributes are together. i.e. the nature of the
// cohesion.
//----------------------------------------------------------

enum Sorted { Almost, NotVery }; // self-explanatory
enum WasAlready { OK, OrNot }; // indicates whether array was already sorted

// Sort is a useful function which will sort an integer vector, and given
// information via the second parameter, will use a different strategy depending on
// whether the data is almost sorted already, or not. Variable 'already' returns
// whether the input vector was already sorted. i.e. didn't need sorting.
void sort(std::vector<int>& data, Sorted sortedness, WasAlready& already);
// The parameters of a function should be listed one per line as shown above,
// with a comment giving info on whether it is an input parameter, an input and
// output parameter, or solely an output parameter. You can't tell this simply by
// whether they are reference/pointer parameters or not! After each function
// definition, there should be at least a 1 paragraph description of the function:
// what it does, how to use it, what its restrictions are, etc. You do not have to
// suggest what internal algorithm a function will use. This interface file is an
// advertisement of only how another programmer should use an exported function.

void otherProc();

#endif // EXAMPLESORT_H
#include "ExampleSort.h"

//----------------------------------------------------------
// Function: sort
// Parameters:
// - data: std::vector<int>& (in/out) - the data to be sorted
// - sortedness: Sorted (in) - this parameter is a hint to the sort routine
// - already: WasAlready& (out) - returns whether the input vector was already sorted
//----------------------------------------------------------
void sort(std::vector<int>& data, Sorted sortedness, WasAlready& already) {
    // Implementation of the sort function
    // My choice is brace on the same line as the name.
    // And function names start with a lower case letter.
    // int i = 3; // my choice is indenting function and loop blocks by 3 spaces.
}

//----------------------------------------------------------
// Function: otherProc
// Description: Example of another function definition
//----------------------------------------------------------
void otherProc() {
    // Implementation of otherProc
}
