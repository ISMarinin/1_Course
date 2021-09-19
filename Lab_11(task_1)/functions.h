#ifndef FUNCTIONS_H
#define FUNCTIONS_H

enum State : unsigned { Start = 0, FirstStick, DoubleQuotes, SingleQuote, SecondStick, Space, Symbols, EndWord, NewLine, End };

State fsm(const State, const char);

#endif
