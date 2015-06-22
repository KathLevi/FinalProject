#ifndef __Uno__Card__
#define __Uno__Card__

#include <stdio.h>
#include <string>

using namespace std;

class Card{
private:
    string suit;
    string rank;
    int cardNumber;
public:
    void setSuit(int cardNumber);
    void setRank(int cardNumber);
    string getSuit();
    string getRank();
};

#endif
