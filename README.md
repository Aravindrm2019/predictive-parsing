Compiler Lab Tools
This project implements:

Removal of Left Recursion
Left Factoring
FIRST Set Computation
FOLLOW Set Computation
How to Run
Place grammar in grammar_input.txt
Run:
python left_recursion.py python left_factoring.py python first_follow.py

Grammar Format
Use:

for epsilon
-> for production | for alternatives

Example:

S -> A B
A -> A a | b
B -> b