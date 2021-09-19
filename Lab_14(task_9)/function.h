#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MaxSize 10

enum State: unsigned {Start = 0, MoveUp, MoveRight, UpDiagonally, DownDiagonally, Finish};

State NextState (const State , unsigned, unsigned, unsigned);

#endif