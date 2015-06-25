#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Player.h"
#include "Stack.h"
#include "Welcome.h"
using namespace std;

int PlayerCard();
int CompCard(vector<int> cards, int discard);
bool TestCard(int card, int discard);
int Wild(int discard);
int WildComp(int discard);
void DiscardPile(int discard);
int Score(vector<int> p1Cards, vector<int> compCards);

const int NUMBER_OF_CARDS = 108;
string colors[4] = {"Red", "Blue", "Green", "Yellow"};
string ranks[15]  = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Draw Two", "Skip", "Reverse", "Wild", "Wild Draw Four"};

int main(){
    
    //Begin a new game
    cout << "Hello and Welcome to Uno. What would you like to be known by? ";
    string name;
    cin >> name;
    cout << "Nice to have you playing today, " << name << "." << endl;
    Player p1 (name, 0);
    Player comp ("Computer", 0);
    
    Welcome w1;
    w1.Intro();
system("CLS");
    
    //create text file for player to keep track of scores
    string filename = name+" Scores.txt";
    fstream player (filename, ios::beg | ios::out);
    if (player.fail()){
        cout << "Could not open file: " << filename << endl;
        return 0;
    }
    player << name << endl;
    player.close();
    
    char again = 'y';
    do{
        //shuffle the cards
//make the cards more accurate with the ranks/colors
        //initialize
        vector<int> deck(NUMBER_OF_CARDS);
        for (int i = 0; i < NUMBER_OF_CARDS; i++){
            deck[i] = i;
        }
        //shuffle
        srand(time(0));
        for (int i = 0; i < NUMBER_OF_CARDS; i++){
            int index = rand() % NUMBER_OF_CARDS;
            int temp = deck[i];
            deck[i] = deck[index];
            deck[index] = temp;
        }
        
        //add the cards from the vector to a stack
        Stack<int>draw;
        for (int i = 0; i < NUMBER_OF_CARDS; i++){
            draw.push(deck[i]);
        }
        //empty deck
        deck.clear();
        
        //Once the cards are shuffled each player is dealt 7 cards
        //deal the cards to player and computer
        for (int i = 0; i < 7; i++){
            p1.addCard(draw.pop());
        }
        for (int i = 0; i < 7; i++){
            comp.addCard(draw.pop());
        }
        
        //The remainder of the deck is placed face down to form a DRAW pile. The top card of the DRAW pile is turned over to begin a DISCARD pile
        vector<int> discard;
        discard.push_back(draw.pop());
        //playing the game
        do{
            unsigned long size = discard.size()-1;
            DiscardPile(discard[size]);
            
            cout << "\n\n" <<name << "'s turn" << endl; //Users turn
            cout << "\nYour cards are: " << endl; //outputs the users cards
            for (int i = 0; i < p1.getCards().size(); i++){
                if (ranks[p1.getCards()[i] % 15] != "Wild" && ranks[p1.getCards()[i] % 15] != "Wild Draw Four")
                {
                    cout << i << ") " << ranks[p1.getCards()[i] % 15] << " " << colors[p1.getCards()[i] % 4] << endl;
                }
                else
                    cout << i << ") " << ranks[p1.getCards()[i] % 15] << endl;
            }
            int choice = PlayerCard();
            if (TestCard(p1.getCards()[choice], discard[size]) == true){
                discard.push_back(p1.getCards()[choice]); //put the played card on top of the discard deck
                if (ranks[p1.getCards()[choice] % 15] == "Draw Two"){
                    comp.addCard(draw.pop());
                    comp.addCard(draw.pop());
                }
                if (ranks[p1.getCards()[choice] % 15] == "Wild Draw Four"){
                    comp.addCard(draw.pop());
                    comp.addCard(draw.pop());
                    comp.addCard(draw.pop());
                    comp.addCard(draw.pop());
                    discard.push_back(Wild(discard[size]));
                    size++;
                }
                if (ranks[p1.getCards()[choice] % 15] == "Wild"){
                    discard.push_back(Wild(discard[size]));
                    size++;
                }
                if (ranks[p1.getCards()[choice] % 15] == "Skip" || ranks[p1.getCards()[choice] % 15] == "Reverse"){
//could be a better way to do the skip/ reverse cards
                    discard.push_back(p1.getCards()[choice]);//put the played card on top of the discard deck
                    size++;
                    p1.subCard(p1.getCards()[choice]);
                    DiscardPile(discard[size]);
                    
                    cout << "\n\n" <<name << "'s turn" << endl; //Users turn
                    cout << "Your cards are: " << endl; //outputs the users cards
                    for (int i = 0; i < p1.getCards().size(); i++){
                        if (ranks[p1.getCards()[i] % 15] != "Wild" && ranks[p1.getCards()[i] % 15] != "Wild Draw Four")
                        {
                            cout << i << ") " << ranks[p1.getCards()[i] % 15] << " " << colors[p1.getCards()[i] % 4] << endl;
                        }
                        else
                            cout << i << ") " << ranks[p1.getCards()[i] % 15] << endl;
                    }
                    int choice = PlayerCard();
                    if (TestCard(p1.getCards()[choice], discard[size]) == true){
                        if (ranks[p1.getCards()[choice] % 15] == "Draw Two"){
                            comp.addCard(draw.pop());
                            comp.addCard(draw.pop());
                        }
                        if (ranks[p1.getCards()[choice] % 15] == "Wild Draw Four"){
                            comp.addCard(draw.pop());
                            comp.addCard(draw.pop());
                            comp.addCard(draw.pop());
                            comp.addCard(draw.pop());
                            discard.push_back(Wild(discard[size]));
                        }
                        if (ranks[p1.getCards()[choice] % 15] == "Wild"){
                            discard.push_back(Wild(discard[size]));
                        }
                        size++;
                    }
                    else{
                        //If the player doesn’t have a card to match the one on the DISCARD pile, he/she must take a card from the DRAW pile.
                        p1.addCard(draw.pop()); //draw
                        cout << "That card cannot be played. You have drawn a new card." << endl;;
                    }
                }
                p1.subCard(p1.getCards()[choice]); //subtract used card from players hand
                if (p1.getCards().size() == 0)
                    break;
                size++;
            }
            else{
                //If the player doesn’t have a card to match the one on the DISCARD pile, he/she must take a card from the DRAW pile.
                p1.addCard(draw.pop()); //draw
                cout << "That card cannot be played. You have drawn a new card." << endl;;
            }
            
//            DiscardPile(discard[size]);
            cout << "\n\nComputer's turn" << endl; //Computers turn
            int cc = CompCard(comp.getCards(), discard[size]);
            //output what the computer does on it's turn
            if (TestCard(comp.getCards()[cc], discard[size]) == true){
                discard.push_back(comp.getCards()[cc]); //put the played card on top of the discard deck
                if (ranks[comp.getCards()[cc] % 15] == "Draw Two"){
                    p1.addCard(draw.pop());
                    p1.addCard(draw.pop());
                }
                if (ranks[comp.getCards()[cc] % 15] == "Wild Draw Four"){
                    p1.addCard(draw.pop());
                    p1.addCard(draw.pop());
                    p1.addCard(draw.pop());
                    p1.addCard(draw.pop());
                    discard.push_back(WildComp(discard[size]));
                }
                if (ranks[comp.getCards()[cc] % 15] == "Wild")
                    discard.push_back(WildComp(discard[size]));
                if (ranks[comp.getCards()[cc] % 15] == "Skip" || ranks[comp.getCards()[cc] % 15] == "Reverse"){
//could be a better way to do the skip/ reverse cards
                    discard.push_back(comp.getCards()[cc]); //put the played card on top of the discard deck
                    size++;
                    comp.subCard(comp.getCards()[cc]);
//                    DiscardPile(discard[size]);
                    cout << "\n\nComputer's turn" << endl; //Computers turn
                    int cc = CompCard(comp.getCards(), discard[size]);
                    //output what the computer does on it's turn
                    if (TestCard(comp.getCards()[cc], discard[size]) == true){
                        if (ranks[comp.getCards()[cc] % 15] == "Draw Two"){
                            p1.addCard(draw.pop());
                            p1.addCard(draw.pop());
                        }
                        if (ranks[comp.getCards()[cc] % 15] == "Wild Draw Four"){
                            p1.addCard(draw.pop());
                            p1.addCard(draw.pop());
                            p1.addCard(draw.pop());
                            p1.addCard(draw.pop());
                            discard.push_back(WildComp(discard[size]));
                        }
                        if (ranks[comp.getCards()[cc] % 15] == "Wild")
                            discard.push_back(WildComp(discard[size]));
                    }
                    else{
                        cout << "The computer has drawn a card." << endl;  //draw
                        comp.addCard(draw.pop());
                    }
                }
                comp.subCard(comp.getCards()[cc]); //subtract used card from computers hand
                if (comp.getCards().size() == 0)
                    break;
            }
            else{
                cout << "The computer has drawn a card." << endl;  //draw
                comp.addCard(draw.pop());
            }
            
system("CLS");
        }while (!draw.empty() || (p1.getCards().size() != 0) || (comp.getCards().size() != 0));
        //repeat until one player runs out of cards OR when the draw deck is empty
        
system("CLS");
        //tell who wins and deal out the scores
        if (p1.getCards().empty() || p1.getCards().size() < comp.getCards().size())
        {
            cout << endl <<name << " wins!" << endl;
            p1.changeScore(Score(p1.getCards(), comp.getCards()));
            cout << name << " receives " << p1.getScore() << " points." << endl;
        }
        else
        {
            cout << "Computer wins!" << endl;
            comp.changeScore(Score(p1.getCards(), comp.getCards()));
            cout << "The Computer reveives " << comp.getScore() << " points." << endl;
        }
        
        //make both hands and the decks empty again
        p1.cards.clear();
        comp.cards.clear();
        do{
            draw.pop();
        }while (!draw.empty());
        discard.clear();
        
        //save the scores to the files
        player.open(filename, ios::beg | ios::app);
        player << Score(p1.getCards(), comp.getCards()) << endl;
        player.close();

        cout << "Play again? (y or n)";
        cin >> again;
        again = tolower(again);
system("CLS");
    }while(again == 'y');
    
    cout << "\nThank you for playing, " << name << "! Come back soon!" << endl << endl;
    cout << "\tYour score was " << p1.getScore() << endl;
    cout << "\tThe computers score was " << comp.getScore() << endl;
    return 0;
}

int PlayerCard(){
    cout << "Which card would you like to play? ";
    int choice;
    cin >> choice;
    return choice;
}
int CompCard(vector<int> cards, int discard){
    int choice = 0;
    for (int i = 0; i < cards.size(); i++){
        if (ranks[cards[i] % 15] == "Wild" || ranks[cards[i] % 15] == "Wild Draw Four"){
            choice = i;
            cout << "The computer played " << ranks[cards[i] % 15] << endl;
            break;
        }
        else if ((ranks[discard % 15] == ranks[cards[i] % 15]) || (colors[discard % 4] == colors[cards[i] % 4])){
            choice = i;
            cout << "The computer played " << ranks[cards[i] % 15] << " " << colors[cards[i] % 4] << endl;
            break;
        }
    }
    return choice;
}
//test cards function
//match the card on the DISCARD pile, either by number, color or symbol
bool TestCard(int card, int discard){
    if (ranks[card % 15] == "Wild" || ranks[card % 15] == "Wild Draw Four"){
        return true;
    }
    else if (ranks[discard % 15] == ranks[card % 15]){
        return true;
    }
    else if (colors[discard % 4] == colors[card % 4]){
        return true;
    }
    else{
        return false;
    }
}
int Wild(int discard){
    cout << "What color would you like to choose?\n\t1) Red\n\t2) Blue\n\t3) Green\n\t4) Yellow" << endl;
    int choice;
    cin >> choice;
    if (choice == 1){
        discard = 0;
        cout << "Red" << endl;
    }
    if (choice == 2){
        discard = 1;
        cout << "Blue" << endl;
    }
    if (choice == 3){
        discard = 2;
        cout << "Green" << endl;
    }
    if (choice == 4){
        discard = 3;
        cout << "Yellow" << endl;
    }
    return discard;
}
int WildComp(int discard){
    int choice = (rand() % 3) +1;
    
    if (choice == 1){
        discard = 0;
        cout << "Red" << endl;
    }
    if (choice == 2){
        discard = 1;
        cout << "Blue" << endl;
    }
    if (choice == 3){
        discard = 2;
        cout << "Green" << endl;
    }
    if (choice == 4){
        discard = 3;
        cout << "Yellow" << endl;
    }
    return discard;
}
void DiscardPile(int discard){
    cout << "\nThe face up card is: " << endl;
    
    if (ranks[discard % 15] == "Wild" || ranks[discard % 15] == "Wild Draw Four")
        cout << ranks[discard % 15] << endl;
    
    else
        cout << ranks[discard % 15] << " " << colors[discard % 4] << endl;
}
int Score(vector<int> p1Cards, vector<int> compCards){
    int score = 0;
    if (p1Cards.size() != 0){
        for (int i = 0; i <= p1Cards.size()-1; i++){
            if (ranks[p1Cards[i] % 15] == "Wild" || ranks[p1Cards[i] % 15] == "Wild Draw Four")
                score += 50;
            else if (ranks[p1Cards[i] % 15] == "Reverse" || ranks[p1Cards[i] % 15] == "Skip" || ranks[p1Cards[i] % 15] == "Draw Two")
                score +=20;
            else
                score += 5;
        }
    }
    if (compCards.size() != 0){
        for (int i = 0; i <= compCards.size()-1; i++){
            if (ranks[compCards[i] % 15] == "Wild" || ranks[compCards[i] % 15] == "Wild Draw Four")
                score += 50;
            else if (ranks[compCards[i] % 15] == "Reverse" || ranks[compCards[i] % 15] == "Skip" || ranks[compCards[i] % 15] == "Draw Two")
                score +=20;
            else
                score += 5;
        }
    }
    return score;
}

