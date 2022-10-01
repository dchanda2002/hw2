## Homework Assignment 2 ##

 - Name: Dwaipayan Chanda
 - Email: dchanda@usc.edu

To run the program, simply type `make` while within the `hw2` directory. The Makefile will compile all code.

To run the file, type `./amazon [filename]` where "[filename]" refers to the input data file (containing the products and users).

Within the program, the menu interface directs you to the use of each command. (AND, OR, ADD, VIEWCART, BUYCART, QUIT).

### A few notes: ###

1. The commands (first word you input) are case-sensitive. The search terms (everything after) are not. EXCEPTION: QUIT takes in a specific, case-sensitive file name.
2. Anything you input that has more than the needed number of terms will cut off input at the correct number of terms. For example, for the database.txt input file given, if you type `ADD aturing 1 23` or `ADD aturing 1 men`, in both cases it will only take the first three values as input, `ADD`, `aturing`, and `1`, not anything past that.
 







