#include "Player.h"

Player::Player(string name, int score){
    this->name = name;
    this->score = score;
}

void Player::setName(string name){
    this->name = name;
}

string Player::getName(){
    return name;
}

int Player::getScore(){
    return score;
}

void Player::changeScore(int NewScore){
    score+=NewScore;
}

void Player::addCard(int card){
    cards.push_back(card);
}
void Player::subCard(int card){
    int index;
    for (int i = 0; i < cards.size(); i++){
        if (cards[i] == card){
            index = i;
            break;
        }
    }
    for (; index < cards.size(); index++){
        cards[index] = cards[index+1];
    }
    unsigned long size = cards.size();
    cards.pop_back();
}
vector<int> Player::getCards(){
    return cards;
}