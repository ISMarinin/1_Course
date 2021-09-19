#include <stdio.h>
#include "function.h"

void init (struct Bitset* bs)
{
    bs->set = 0;
}

void makeIntersect (struct Bitset* bs, const struct Bitset r)
{
    bs->set = bs->set & r.set;
}

void addElement (struct Bitset* bs, char element)
{
     bs->set = bs->set | (1u << (element - 'a')); 
}

bool check (struct Bitset* word, const struct Bitset vowel)
{
    makeIntersect(word, vowel);
    if (vowel.set == word->set) {
        return true;
    }
    else {
        return false;
    }
    
}

char lowRegister (char smb) 
{
    if (smb >= 65 && smb <= 90)
        return smb += 32;
    return smb;
}