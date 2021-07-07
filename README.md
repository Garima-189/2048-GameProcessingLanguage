# 2048-GameProcessingLanguage

Parser- translater for 2048 game programming language.
The project has three parts :
1. Scanner (scanner.l)
2. Parser-translator(parser.ypp)
3. Driver code(game.cpp)
(Header file(header.h) and makefile is also attached.)


Steps for running the program :
1. make
2. ./scanner 2>output.txt type (type can be either 1 or 2, make an empty output.txt file)
3. Whenever you want to break out, press Ctrl + C.

Followed by this, usual interaction with the user continues and whenever it encounters an error,
it adds -1 to stderr file.

The code takes as a command line argument value 1 or 2 for the type of implementation.
If the command line argument is 1 :

The implementation of type 1 is that whenever a tile gets assigned to value 0 in between it will
be considered as an empty tile only.
For example - if we have something like 4 2 2 4, SUBTRACT RIGHT. will make it 0 0 4 4.

If the command line argument is 2 :
The implementation of type 1 is that whenever a tile gets assigned to value 0 in between, it will
still be treated as a tile and will be removed in the next iteration.
For example - if we have something like 4 2 2 4, SUBTRACT RIGHT. will make it 0 4 0 4.

Scanner : Scanner is responsible for scanning the input and breaking it down into the
corresponding lexemes. We define keywords first followed by numbers and variables(and
special case for invalid variable names). We also ignore spaces by doing nothing when we
encounter more than one of them. We use the variable yylval to pass data from the lexer to the
parser by assigning it yytext. We therefore define YYSTYPE as char* to allow for both variable
names and numbers to be passed. We also return an enum token which is defined in header file
which is one output of the bison program.
Parser:Parser contains the grammar rules and it checks those rules and interprets our statements. The
initial block has all the header files.
Different tokens have been used :
●
●
●
●
For operations: ADD, SUBTRACT, MULTIPLY, DIVIDE
For directions : LEFT, RIGHT, UP, DOWN
Other keyword tokens : VAR, IS, VALUE, IN, ASSIGN, TO
Extra tokens : FULLSTOP, NEWLINE, VARIABLE, NUMBER, COMMA
Additional define parse.error verbose has been used so that errors are specified in a better way.
GRAMMAR RULES
1. Input: |Input Sentence
The extra Input so that it does not just match one production rule and ends. Without using Input,
it checks the first rule we give, after the second rule it starts giving Syntax errors even if they are
valid.
ADD – terminal,
2. Sentence : operator direction end
operator, direction and end are non terminals. It is for handling the grammar rules like -
ADD LEFT. , MULTIPLY RIGHT., etc.
| operator direction NEWLINE
This is the repetition of the same rule used above and end has been replaced with NEWLINE.
This is to take care of similar grammar rules without full stop so that it can identify errors like the
grammar rule is fine but it doesn’t use full stop at the end.
It is for handling the grammar rules like -
|VAR variables IS num COMMA num end
This is to handle rules like VAR name IS 1,1. So that it assigns the name to the tile at 1,1. It
gives an error if 1,1 is empty. Also, it will check if num, num is out of range, that is it’s some
value except 1,2,3,4 it will give Out of Bounds error.
|VAR variables is num COMMA num NEWLINE
This is the repetition of the same rule used above, for handling rule ending without full stop.
|ASSIGN num TO num, num end
This is for assigning a number to a particular tile. It handles rules like ASSIGN 5 TO 1,1.
Here, 1,1 is in the valid range, so it will work fine. If it would be something like 5,6, it will give out
of bounds error.
|ASSIGN num TO num, num NEWLINE
This is again for checking if a valid rule is without full stop.|VALUE IN num, num end
This is for getting the value stored in a particular row, col index on board.
It gives out of bounds error if the value goes beyond 4 or is less than or equal to 0.
|VALUE IN num, num NEWLINE
This is again for checking if a valid rule is without full stop.
|VARIABLE NEWLINE
This is for checking if any random rule which doesn’t exist is given.
3. end : FULLSTOP NEWLINE
Each valid rule has a “.” at the end and is followed by a newline character.
4. num : NUMBER
It maps num to the terminal NUMBER.
5. operator : ADD|SUBTRACT|MULTIPLY|DIVIDE
Operator can be ADD, SUBTRACT, MULTIPLY, DIVIDE, so by this rule we change wherever
there is operator to the given values which are terminals.
6. direction : LEFT|RIGHT|DOWN|UP
Direction can be LEFT, RIGHT, DOWN, UP which are terminals, so by this rule we change
direction to the given values, which are terminals.

Driver :

The driver contains the definitions for all the content that has been declared in the header
variables. It also contains the definitions for the board state which is a vector of vectors and the
symbol table which is a map of C++ STL. To index into the map the key used is the pair that is
used to describe the coordinates of the variable and the value associated with it is a vector of
strings containing all the names for that tile.
Functions which are called in the parser such as deleteName, assignName, getName,
getBoardState, addTileValue, printBoard are defined here and as these functions reference a
global variable from this file directly we do not require to make extern variables which can be
referenced from the parser and the lexer directly. We provide helper functions such as
getEmptyTiles, emptySlotsLeft etc each implementing a mechanic of the game (which are called
from other functions as well). Additionally, we have definitions for moveUp, moveDown,
moveLeft and moveRIght which takes the operator as a parameter and performs the requisiteoperation. The decision about which of these functions to be called is handled by the function
move using the parameter moveDirection.
In main random number generation to system time so that we get a different game each time.
We start the game by generating a random tile and call function yyparse. Yyparse is responsible
for handling the bulk of the work. It internally calls yylex and parses the input. To terminate the
input file press Ctrl+C.
The file name is parser.ypp so that after compilation it generates a .cpp file.

