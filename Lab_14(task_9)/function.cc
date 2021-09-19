#include "function.h"

/*
    Start (0)
    MoveUp (1)
    MoveRight (2)
    UpDiagonally (3)
    DownDiagonally (4)
    Finish (5)
*/

State NextState (const State currentState, unsigned i, unsigned j, unsigned n)
{
    State newState;
    switch (currentState) {
        case Start:
        {
            if (j < n - 1 && i > 0) {
				newState = MoveUp;
			}
            else {
				newState = Finish;
			}
			break;
        }
        case MoveUp:
        {
            if (i == 0 && j == n - 1) {
                newState = Finish;
            }
            else if (j == 0) {
                newState = DownDiagonally;
            }
            else if (j == n - 1) {
                newState = UpDiagonally;
            }
            break;
        }
        case DownDiagonally:
        {
            if (j == n - 1) {
                newState = MoveUp;
            }
            else if (i == n - 1) {
                newState = MoveRight;
            }
            
            else {
                newState = DownDiagonally;
            }
            break;
        }
        case MoveRight:
        {
            if (i == n - 1) {
                newState = UpDiagonally;
            }
            else if (i == 0) {
                newState = DownDiagonally;
            }
            break;
        }
        case UpDiagonally:
        {
            if (i == 0) {
                newState = MoveRight;
            }
            else if (j == 0) {
                newState = MoveUp;
            }        
            else {
                newState = UpDiagonally;
            }
            break;
        }
    }
    return newState;
}