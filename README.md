# smallCalculator
extension of smallParser work, dragon book chapter 2, parsing infix input to postfix, then calculating

# Install
if you have the general linux wsl prequesits, it should be enough,
if anything is missing install it, 
after that build it:
```
git clone https://github.com/XiiiC/smallCalculator
cd smallCalculator
g++ -std=c++14 parser.hpp main.cpp -o parser
./parser
```
currently just takes infix notation, converting it to postfix
next step is creating calculations
dragon book chapter 2 example 2.8
