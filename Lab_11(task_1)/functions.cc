#include "functions.h"
#include <stdio.h>
#include <cctype>

State fsm(const State currentState, const char currentSymbol)
{
    State newState;
    switch(currentState) {
        //Start(0)
        //FirstStick(1)
        //DoubleQuotes(2)
        //SingleQuote(3)
        //SecondStick(4)
        //Space(5)
        //Symbols(6)
        //EndWord(7)
        //NewLine(8)
        //End(9)
        case Start:
        {
            if (currentSymbol == '/') {
                newState = FirstStick;
            }
            else if (currentSymbol == '\"') {
                newState = DoubleQuotes;
            }
            else if (currentSymbol == '\'') {
                newState = SingleQuote;;
            }
            else if (isalpha(currentSymbol) ||
            isdigit(currentSymbol) || (!isalpha(currentSymbol) && !isdigit(currentSymbol)) &&
            currentSymbol != '/' && currentSymbol != '\'' && currentSymbol != '\"') {
                newState = Start;
            }
            break;
        }
        case FirstStick:
        {
            if (currentSymbol == '/') {
                newState = SecondStick;
            }
            else if (isalpha(currentSymbol) ||
            isdigit(currentSymbol) || (!isalpha(currentSymbol) && !isdigit(currentSymbol)) &&
            currentSymbol != '/' ) {
                newState = Start;
        }
        break;
        }
        case DoubleQuotes:
        {
            if (currentSymbol == '\"') {
                newState = Start;
            }
            else if (isalpha(currentSymbol) ||
            isdigit(currentSymbol) || (!isalpha(currentSymbol) && !isdigit(currentSymbol)) &&
            currentSymbol != '\"' ) {
                newState = DoubleQuotes;
        }
        break;
        }
        case SingleQuote:
        {
            if (currentSymbol == '\'') {
                newState = Start;
            }
            else if (isalpha(currentSymbol) ||
            isdigit(currentSymbol) || (!isalpha(currentSymbol) && !isdigit(currentSymbol)) &&
            currentSymbol != '\'') {
                newState = DoubleQuotes;
            }
        break;
        }
        case SecondStick:
        {
        if (currentSymbol == ' ') {
            newState = Space;
        }
        else if (isalpha(currentSymbol) || isdigit(currentSymbol)) {
            newState = Symbols;
        }
        break;
        }
        case Space:
        {
            if (currentSymbol == ' ') {
                newState = Space;
            }
            else if (isalpha(currentSymbol) || isdigit(currentSymbol)) {
                newState = Symbols;
            }
            break;
        }
        case Symbols:
        {
            if (isalpha(currentSymbol) || isdigit(currentSymbol)) {
                newState = Symbols;
            }
            else if (currentSymbol == ' ') {
                newState = EndWord;
            }
            else if (currentSymbol == '\n') {
                newState = NewLine;
            }
            else if (currentSymbol == EOF) {
                newState = End;
            }
            break;
        }
        case EndWord:
        {
            if (isalpha(currentSymbol) || isdigit(currentSymbol)) {
                newState = Symbols;
            }
            else if (currentSymbol == ' ') {
                newState = Space;
            }
            else if (currentSymbol == '/') {
                newState = FirstStick;
            }
            break;
        }
        case NewLine:
        {
            if (currentSymbol == '/') {
                newState = FirstStick;
            }
            else {
                newState = Start;
            }
                break;
        }
    }
    return newState;
}