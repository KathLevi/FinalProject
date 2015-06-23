#ifndef __Uno__Player__
#define __Uno__Player__

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

class Player{
private:
    string name;
    int score;

public:
    vector <int> cards;
    Player(string name, int score);
    void setName(string name);
    string getName();
    int getScore();
    void changeScore(int NewScore);
    void addCard(int cards);
    void subCard(int cards);
    vector<int> getCards();
    
};

#endif
