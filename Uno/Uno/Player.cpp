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
    
}
void Player::subCard(int card){
    
}
vector<int> Player::getCards(){
    return cards;
}