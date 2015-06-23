#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Player.h"
#include "Stack.h"
using namespace std;

//go through rules to make sure they make sense with the digital game
void Welcome();
void ObjectOfTheGame();
void HowToPlay();
void FunctionsOfTheActionCards();
void GoingOut();
void Scoring();
void WinningTheGame();
int PlayerCard();
int CompCard(vector<int> cards, int discard);
bool TestCard(int card, int discard);
void DiscardPile(int discard);
//Special two player rules:
//1. Playing a Reverse card acts like a Skip. The player who plays the Reverse may immediately play another card.
//2. The person playing a Skip card may immediately play another card.
//3. When one person plays a Draw Two card and the other player has drawn the 2 cards, the play is back to the first person. The same principle applies to the Wild Draw Four card.

//scoring:
//The first player to get rid of his/her cards receives points for cards left in opponents’ hands as follows:
//All number cards (0-9) . . . . . . . . . . . . . Face Value
//Draw Two. . . . . . . . . . . . . . . . . . . . . . . . 20 Points
//Reverse . . . . . . . . . . . . . . . . . . . . . . . . . 20 Points
//Skip . . . . . . . . . . . . . . . . . . . . . . . . . . . . 20 Points
//Wild . . . . . . . . . . . . . . . . . . . . . . . . . . . . 50 Points
//Wild Draw Four . . . . . . . . . . . . . . . . . . . 50 Points
const int NUMBER_OF_CARDS = 108;
string colors[4] = {"Red", "Blue", "Green", "Yellow"};
string ranks[15]  = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Draw Two", "Skip", "Reverse", "Wild", "Wild Draw Four"};

int main(){
    
    Welcome();
    
    //Begin a new game
    cout << "Hello and Welcome to Uno. What would you like to be known by? ";
    string name;
    cin >> name;
    cout << "Nice to have you playing today, " << name << "." << endl;
    Player p1 (name, 0);
    Player comp ("Computer", 0);
    
    //create text files for player/ high schores
    string filename = name+".txt";
    fstream player (filename, ios::beg | ios::out);
    if (player.fail()){
        cout << "Could not open file: " << filename << endl;
        return 0;
    }
    player << name << endl;
    player.close();
    fstream hs ("HighScores.txt", ios::beg | ios::out);
    if (hs.fail()){
        cout << "Could not open file: HighScores.txt" <<endl;
        return 0;
    }
    hs << "High Scores\n" << endl;
    hs.close();
    
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
        unsigned long size = discard.size();
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
            discard.push_back(p1.getCards()[choice]); //put the played card on top of the discard deck
            p1.subCard(p1.getCards()[choice]); //subtract used card from players hand
        }
        else{
        //If the player doesn’t have a card to match the one on the DISCARD pile, he/she must take a card from the DRAW pile.
            p1.addCard(draw.pop()); //draw
            cout << "That card cannot be played. You have drawn a new card." << endl;;
        }
        
        DiscardPile(discard[size]);
        cout << "\n\nComputer's turn" << endl; //Computers turn
            int cc = CompCard(comp.getCards(), discard[size]);
            //output what the computer does on it's turn
        if (TestCard(comp.getCards()[cc], discard[size]) == true){
//something is wrong around this point and I dont know what it is
            discard.push_back(comp.getCards()[cc]); //put the played card on top of the discard deck
            comp.subCard(comp.getCards()[cc]); //subtract used card from computers hand
        }
        else{
            cout << "The computer has drawn a card." << endl;  //draw
            comp.addCard(draw.pop());
        }
        
        
    } while (!draw.empty() || !p1.getCards().empty()|| !comp.getCards().empty());
    //repeat until one player runs out of cards OR when the deck is empty



//action cards
    
//scoring
//save to the files and to the players classes

}

void Welcome(){
    //Welcome and introduction to the game
    cout << "Welcome to the game of Uno!";
    char choice = 'y';
    do{
        cout << "\nPlease choose a menu option below: \n\t1) Object Of the Game\n\t2) How to Play\n\t3) Functions of the Action Cards\n\t4) Going Out\n\t5) Scoring\n\t6) Winning the Game\n\t7) I already know how to play\nYour choice: ";
        int menuOption;
        cin >> menuOption;
        
        switch (menuOption)
        {
            case 1: ObjectOfTheGame();
                cout << "\n\nWould you like to choose another menu option?(y or n) ";
                cin >> choice;
                break;
            case 2: HowToPlay();
                cout << "\n\nWould you like to choose another menu option?(y or n) ";
                cin >> choice;
                break;
            case 3: FunctionsOfTheActionCards();
                cout << "\n\nWould you like to choose another menu option?(y or n) ";
                cin >> choice;
                break;
            case 4: GoingOut();
                cout << "\n\nWould you like to choose another menu option?(y or n) ";
                cin >> choice;
                break;
            case 5: Scoring();
                cout << "\n\nWould you like to choose another menu option?(y or n) ";
                cin >> choice;
                break;
            case 6: WinningTheGame();
                cout << "\n\nWould you like to choose another menu option?(y or n) ";
                cin >> choice;
                break;
            case 7: cout << "\nGreat! Let's get started." << endl;
                choice = 'n';
                break;
            default: cout << "\nThat is not a valid menu item, plesae try again.\n";
        }
    } while (choice == 'y');
    //CLEAR SCREEN
}
void ObjectOfTheGame(){
    cout << "\nObject of the Game\n\tTo be the first player to run out of cards. Points are scored by getting rid of all the cards in your hand before your opponent(s). You score points for cards left in your opponents’ hands." << endl;
}
void HowToPlay(){
    cout << "How to Play\nEvery player picks a card. The person who picks the highest number deals. Action Cards count as zero for this part of the game.\nOnce the cards are shuffled each player is dealt 7 cards.\nThe remainder of the deck is placed face down to form a DRAW pile. The top card of the DRAW pile is turned over to begin a DISCARD pile. If an Action Card is the first one turned up from the DRAW pile, certain rules apply (See FUNCTIONS OF ACTION CARDS).\nThe person to the left of the dealer starts play. He/she has to match the card on the DISCARD pile, either by number, color or symbol. For example, if the card is a red 7, the player must put down a red card or any color 7. Alternatively, the player can put down a Wild card (See FUNCTIONS OF ACTION CARDS).\nIf the player doesn’t have a card to match the one on the DISCARD pile, he/she must take a card from the DRAW pile.\nPlayers may choose not to play a playable card from their hand. If so, the player must draw a card from the DRAW pile." << endl;
}
void FunctionsOfTheActionCards(){
    cout << "\nFunctions of the Action Cards\n";
    cout << "Draw Two Card\n\tWhen this card is played, the next person to play must draw 2 cards and miss his/her turn. This card can only be played on matching colors and other Draw Two cards. If turned up at the beginning of play, the same rule applies." << endl;
    cout << "Reverse Card\n\t This simply reverses direction of play. Play to changes direction to the right, and vice versa. The card may only be played on a matching color or on another Reverse card. If this card is turned up at the beginning of play, the dealer goes first, then play moves to the right instead of the left." << endl;
    cout << "Skip Card\n\t The next player to play after this card has been laid loses his/her turn and is \"skipped\". The card may only be played on a matching color or on another Skip card. If a Skip card is turned up at the beginning of play, the player to the left of the dealer is \"skipped\", hence the player to the left of that player commences play." << endl;
    cout << "Wild Card\n\tThe person playing this card calls for any color to continue the play, including the one currently being played, if so desired. A Wild card can be played at any time - even if the player has another playable card in the hand. If a Wild card is turned up at the beginning of play, the person to the left of the dealer determines the color, which continues play." << endl;
    cout << "Wild Draw Four Card\n\t This is the best card to have. The person who plays it calls the color that continues play. Also, the next player has to pick up 4 cards from the DRAW pile and miss his/her turn. Unfortunately, the card can only be played when the player holding it does not have a card in his/her hand to match the color on the DISCARD pile. If the player holds matching numbers or Action Cards, however, the Wild Draw Four card may be played. A player holding a Wild Draw Four may choose to bluff and play the card illegally, but if he/she is caught certain rules apply (See PENALTIES). If this card is turned up at the beginning of play, it is returned to the deck and another card is picked." << endl;
}
void GoingOut(){
    cout << "\nGoing Out\n\tOnce a player has no cards left, the hand is over. Points are scored (see SCORING) and play starts over again. If the last card played in a hand is a Draw Two or Wild Draw Four card, the next player must draw the 2 or 4 cards respectively. These cards are counted when the points are totalled. If no player is out of cards by the time the DRAW pile is depleted, the player with the least amount of points wins." << endl;
}
void Scoring(){
    cout << "\nScoring\n\tThe first player to get rid of his/her cards receives points for cards left in opponents’ hands as follows:\n\tAll number cards (0-9) . . . . . . . . . . . . . Face Value\n\tDraw Two. . . . . . . . . . . . . . . . . . . . . . . . 20 Points\n\tReverse . . . . . . . . . . . . . . . . . . . . . . . . . 20 Points\n\tSkip . . . . . . . . . . . . . . . . . . . . . . . . . . . . 20 Points\n\tWild . . . . . . . . . . . . . . . . . . . . . . . . . . . . 50 Points\n\tWild Draw Four . . . . . . . . . . . . . . . . . . . 50 Points" << endl;
}
void WinningTheGame(){
    cout << "\nWinning The Game\n\tThe WINNER is the first player to reach 500 points. However, the game may be scored by keeping a running total of the points each player is caught with at the end of each hand. When one player reaches 500 points, the player with the lowest points is the winner." << endl;
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
        cout << "Wild" << endl;
        return true;
    }
    else if (ranks[discard % 15] == ranks[card % 15]){
        cout << "True Rank" << endl;
        return true;
    }
    else if (colors[discard % 4] == colors[card % 4]){
        cout << "True Color" << endl;
        return true;
    }
    else{
        cout << "False... Draw" << endl;
        return false;
    }
}
void DiscardPile(int discard){
     cout << "\nThe face up card is: " << endl;
    
    if (ranks[discard % 15] == "Wild" || ranks[discard % 15] == "Wild Draw Four")
        cout << ranks[discard % 15] << endl;
    
    else
        cout << ranks[discard % 15] << " " << colors[discard % 4] << endl;
}