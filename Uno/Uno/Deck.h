#ifndef __Uno__Deck__
#define __Uno__Deck__

#include <stdio.h>
#include <string>
#include "Card.h"
using namespace std;

class Deck{
private:
    Card card;
    string deck;
public:
    Deck(Card card);
    
};

#endif
