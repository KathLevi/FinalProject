#include "Welcome.h"

void Welcome:: Intro(){
    //Welcome and introduction to the game
    char choice = 'y';
    do{
        cout << "\nPlease choose a menu option below: \n\t1) Object Of the Game\n\t2) How to Play\n\t3) Functions of the Action Cards\n\t4) Going Out\n\t5) Scoring\n\t6) Winning the Game\n\t7) I already know how to play\nYour choice: ";
        int menuOption;
        cin >> menuOption;
        
        switch (menuOption)
        {
            case 1: Welcome::ObjectOfTheGame();
                cout << "\n\nWould you like to choose another menu option?(y or n) ";
                cin >> choice;
                break;
            case 2: Welcome::HowToPlay();
                cout << "\n\nWould you like to choose another menu option?(y or n) ";
                cin >> choice;
                break;
            case 3: Welcome::FunctionsOfTheActionCards();
                cout << "\n\nWould you like to choose another menu option?(y or n) ";
                cin >> choice;
                break;
            case 4: Welcome::GoingOut();
                cout << "\n\nWould you like to choose another menu option?(y or n) ";
                cin >> choice;
                break;
            case 5: Welcome::Scoring();
                cout << "\n\nWould you like to choose another menu option?(y or n) ";
                cin >> choice;
                break;
            case 6: Welcome::WinningTheGame();
                cout << "\n\nWould you like to choose another menu option?(y or n) ";
                cin >> choice;
                break;
            case 7: cout << "\nGreat! Let's get started." << endl;
                choice = 'n';
                break;
            default: cout << "\nThat is not a valid menu item, plesae try again.\n";
        }
    } while (choice == 'y');
}
void Welcome::ObjectOfTheGame(){
    cout << "\nObject of the Game\n\tTo be the first player to run out of cards. Points are scored by getting rid of all the cards in your hand before your opponent(s). You score points for cards left in your opponents’ hands." << endl;
}
void Welcome::HowToPlay(){
    cout << "\nHow to Play\nOnce the cards are shuffled each player is dealt 7 cards.\nThe remainder of the deck is placed face down to form a DRAW pile. The top card of the DRAW pile is turned over to begin a DISCARD pile. If an Action Card is the first one turned up from the DRAW pile, you must play another action card or sacrifice your turn.\nThe first player has to match the card on the DISCARD pile, either by number, color or symbol. For example, if the card is a red 7, the player must put down a red card or any color 7. Alternatively, the player can put down a Wild card (See FUNCTIONS OF ACTION CARDS).\nIf the player doesn’t have a card to match the one on the DISCARD pile, he/she must take a card from the DRAW pile.\nPlayers may choose not to play a playable card from their hand. If so, the player must draw a card from the DRAW pile." << endl;
}
void Welcome::FunctionsOfTheActionCards(){
    cout << "\nFunctions of the Action Cards\n";
    cout << "Draw Two Card\n\tWhen this card is played, the next person to play must draw 2 cards. This card can only be played on matching colors and other Draw Two cards. If turned up at the beginning of play, the same rule applies." << endl;
    cout << "Reverse Card\n\t This simply reverses direction of play. Play to changes direction to the right, and vice versa. The card may only be played on a matching color or on another Reverse card. If this card is turned up at the beginning of play, the dealer goes first, then play moves to the right instead of the left.\n(In a two player game, the reverse card acts as a skip)." << endl;
    cout << "Skip Card\n\t The next player to play after this card has been laid loses his/her turn and is \"skipped\". The card may only be played on a matching color or on another Skip card. If a Skip card is turned up at the beginning of play, you must play a similar card but there are no consequences." << endl;
    cout << "Wild Card\n\tThe person playing this card calls for any color to continue the play, including the one currently being played, if so desired. A Wild card can be played at any time - even if the player has another playable card in the hand. If a Wild card is turned up at the beginning of play, the player must play a wild card or sacrifice thier turn." << endl;
    cout << "Wild Draw Four Card\n\t This is the best card to have. The person who plays it calls the color that continues play. Also, the next player has to pick up 4 cards from the DRAW pile. If this card is turned up at the beginning of play, the player must play another Wild Draw Four card or sacrifice their turn." << endl;
}
void Welcome::GoingOut(){
    cout << "\nGoing Out\n\tOnce a player has no cards left, the hand is over. Points are scored (see SCORING) and play starts over again. If the last card played in a hand is a Draw Two or Wild Draw Four card, the next player must draw the 2 or 4 cards respectively. These cards are counted when the points are totalled. If no player is out of cards by the time the DRAW pile is depleted, the player with the least amount of points wins." << endl;
}
void Welcome::Scoring(){
    cout << "\nScoring\n\tThe first player to get rid of his/her cards receives points for cards left in opponents’ hands as follows:\n\tAll number cards (0-9) . . . . . . . . . . . . . 5 Points\n\tDraw Two. . . . . . . . . . . . . . . . . . . . . . . . 20 Points\n\tReverse . . . . . . . . . . . . . . . . . . . . . . . . . 20 Points\n\tSkip . . . . . . . . . . . . . . . . . . . . . . . . . . . . 20 Points\n\tWild . . . . . . . . . . . . . . . . . . . . . . . . . . . . 50 Points\n\tWild Draw Four . . . . . . . . . . . . . . . . . . . 50 Points" << endl;
}
void Welcome::WinningTheGame(){
    cout << "\nWinning The Game\n\tThe WINNER is the player with the highest amount of points at the end of every game combined, or at the end of just one game." << endl;
}