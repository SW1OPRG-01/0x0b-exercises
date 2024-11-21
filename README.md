# 0x0B Exercises
This week, there are two exercises available: If you don't feel completely confident about the topics of the course, start with Exercise 0x00 (and then attempt Exercise 0x10).

If you're up for something a bit more challenginh, skip Exercise 0x00 and go straight to Exercise 0x10 (there are also some extra challenge tasks here). It's important to approach them in small steps by following the STREAM process described in Chapter 13 of the book.

## Exercise 0x00 – The `Amount` class
Create a class that represents "an amount". The amount is in a given currency, for example, an object of the class can represent the price of a liter of milk - 13.50 DKK.

The class `Amount` should be able to:
1. Be instantiated (constructor) - either without a value but with a currency, or with a value and a currency.
2. Another amount can be added (in the same currency, otherwise an error message is given).
3. An amount can be converted to another currency (i.e., value and currency are changed), here the other currency and exchange rate are specified.
4. It can be printed out, i.e., return a string corresponding to the amount.

You should follow the STREAM process, that is, follow the individual steps and always make sure that your code can be compiled. Before you start the process, it might be a good idea to draw a UML diagram for the `Amount` class (note that you have not yet decided on what attributes the class should have, so that part of the class will be empty).

## Exercise 0x10 – The board game of `Catch & Run`
This exercise is a bit larger than usual, as it should illustrate the STREAM process. You must complete the exercise by following the steps in the STREAM process, so that you end up having implemented the entire solution.

It's very important, that you do it in small incremental steps. The proposed solution contains roughly 250 lines of code (comments included), so it's something that cannot (should not) be done in "one go". 

Use the "wish fairy" as much as you can - if you want to do something, find out what needs to be known to figure it out (i.e., method parameters, helper methods) and what you want to achieve (i.e., the return type from the private method). Create the method with an "empty" implementation and use it. Test to make sure everything still compiles, and then return to implement the private method.

You should program a class in C++ that represents a game called "Catch & Run". 

The game is a simplified version of the well-known game Ludo, where players move their pieces on a game board by rolling a die. You shall NOT create a graphical interface, but a mechanism to print the game board on the terminal.

Your class should have a number of members and methods that take into account the different rules that apply to Catch & Run.

The rules are as follows:
- A piece can have one of four colors: Red, Yellow, Green, or Blue.
- A player is Red, Yellow, Green, or Blue and has three pieces in this color (e.g. an integer in the range of 1 to 3).
- A piece has a position on the game board, which can be an integer in the range of 0 to 24.
- There can be at most one piece per position on the game board, except position 0, which is the starting position and position 24, which is "home" (the piece has reached the goal).
- A piece can be moved by rolling a die (i.e., a number between 1 and 6). If the die shows a certain number, the piece can be moved the number of squares corresponding to the number. When rolled, the player chooses which piece to move (1-3).
- If a piece lands on a position where another color piece is already present, the other piece is sent back to the starting position (square 0).
- A piece cannot be moved, if there is already a piece of the same color in the position it wants to move to (if the player tries, the piece remains in place).
- A player may roll the die again, if they roll a 6.
- A piece has "home" when it lands on square 24. The last position must be hit "precisely" (i.e., the roll must match so that it lands on position 24). If there is only one piece left and the roll means that the piece "goes past" square 24, the piece is not moved.
- If there are situations not covered by the above, decide for yourself what the rule should be - and remember to document it (by extending the specification).

The game must have at least four methods:
- `print()`: Prints the game board indicating which pieces are where
- `roll()`: Returns a random number between 1 and 6
- `move(player, pieceNr, roll)`: Takes a player (red, yellow, green, or blue), which piece is desired to be moved, and what is rolled and moves the player's specified piece according to the rules above
- `won()`: Is there a player who has won?

**_Challenge tasks_**
- Refactor the proposed solution, so that there are three classes: A Piece, a Game Board, and a Player. The Player has a name that can be printed out when the game is played. The Game Board contains a series of pieces placed on squares, and can move a piece to a given square. A piece can have a color.
- Expand the Ludo game so that there can be up to four pieces on each square (of the same color). The following additional rules should apply:
  - If there is one or more pieces of the same color as the player who rolls, the piece can be placed there.
  - If there are two or more pieces of a different color, send the piece home.