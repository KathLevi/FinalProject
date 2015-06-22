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
    for (int i = 0; i < cards.size(); i++){
        if (card == cards[i]){
            cards[i]--;
        }
    }
}
vector<int> Player::getCards(){
    return cards;
}