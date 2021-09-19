#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef unsigned long long BitsetType;

const unsigned maxBitsetType = sizeof(BitsetType) * 8;

struct Bitset {

    BitsetType set;

};

void init (struct Bitset*);
void makeIntersect (struct Bitset*, const struct Bitset);        //пересечение
void addElement (struct Bitset*, char);                          //добавление элемента
char lowRegister (char);                                         //понижение регистра
bool check (struct Bitset*, const struct Bitset);                

#endif