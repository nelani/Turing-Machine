included:
turing.cpp
input.txt
output.txt
test.txt
Makefile

Assignment 7

In this assignment you will need to build a Turing Machine that accepts an input tape and a transition
function and then executes it. The input file and the transition function must be in separate files. You may
use additional files as necessary but be sure to document their purpose and how they are used.

transition file:

The transition function is presented as a table provided by the user in a separate file. The file will have one
line for each transition. Each line will have 5 components separated by one or more blank characters: The
5 components are:
1. The current state.
2. The expected input token under the read-write head.
3. The value to write on the tape at the current location.
4. The action to be taken by the read-write head after read and writing has completed.
5. The next state (i.e., the state we transition to).
The actions taken by the read-write read are:
1. L: move left one space
2. R: move right one space
3. S: remain stationary (i.e., do not move)
There are times when you do not care what the current value at the read-write head is, or you do not wish
to over-write the value with a new value. In these cases, we will use the token ‘%” to represent the fact that
the expected input token under the read-write head may be anything, and/or to represent the fact that the
current value at the read-write head will not be over-written.

The first line of the transition function indicates the accept states of the Machine

Input file:

The first line of the input file indicates the number of strings to be tested
The next lines are the strings
