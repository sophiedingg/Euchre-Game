// Project UID 1d9f47bfc76643019cfbf037641defe1
    
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Pack.h"
#include "Card.h"
#include <string>
#include <cstring>

class Game {
    public:
        Player** get_player() {
            return player;
        }
        int get_handNumber() {
            return handNumber;
        }
        int get_finalScore() {
            return finalScore;
        }
        std::string get_trump() {
            return trump;
        }
        void print_header(int argc, char * argv[]){
            for (int i = 0; i < argc; i++) { std::cout << argv[i] << " "; }
            std::cout << std::endl;
        }

        // instantiates all the players
        void set_players(char * argv[]) {
            for(int i = 0 ; i < 4; i++) {
                name = argv[4 + 2*i];
                strategy = argv[5 + 2*i];
                player[i] = Player_factory(name, strategy); 
            }
        }

        void set_final_score(char * argv[]) {
            finalScore = atoi(argv[3]);
        }

        void increment_handNumber() {
            handNumber++;
        }
        
        // dealing the cards
        void dealHands(Pack &pack){
            for(int i = 0; i < 3; i++)
            {
                player[(handNumber + 1) % 4]->add_card(pack.deal_one());
            }
            for(int i = 0; i < 2; i++)
            {
                player[(handNumber + 2) % 4]->add_card(pack.deal_one());
            }
            for(int i = 0; i < 3; i++)
            {
                player[(handNumber + 3) % 4]->add_card(pack.deal_one());
            }
            for(int i = 0; i < 2; i++)
            {
                player[(handNumber) % 4]->add_card(pack.deal_one());
            }

            for(int i = 0; i < 2; i++)
            {
                player[(handNumber + 1) % 4]->add_card(pack.deal_one());
            }
            for(int i = 0; i < 3; i++)
            {
                player[(handNumber + 2) % 4]->add_card(pack.deal_one());
            }
            for(int i = 0; i < 2; i++)
            {
                player[(handNumber + 3) % 4]->add_card(pack.deal_one());
            }
            for(int i = 0; i < 3; i++)
            {
                player[(handNumber) % 4]->add_card(pack.deal_one());
            }

            std::cout << player[handNumber % 4]->get_name() 
            << " deals" << std::endl;
        }

        // prints out the upcard
        void print_upcard(Card upcard) {
            std::cout << upcard.get_rank() << " of " << upcard.get_suit() 
            << " turned up" << std::endl;
        }

        // making trump
        void makingTrump(Card &upcard, bool &orderedUp) {
            int round = 1, index = 0;
            bool makeTrump = false, isDealer = false, ordering = false;
            std::string upcardSuit = upcard.get_suit();
            while(!makeTrump && index < 4) {
                if(index == 3) {
                    isDealer = true;
                }
                makeTrump = player[(handNumber + 1 + 
                index) % 4]->make_trump(upcard, isDealer, 
                round, upcardSuit);
                if(!makeTrump) {
                    std::cout << player[(handNumber + 1 + index) 
                    % 4]->get_name() << " passes" << std::endl;
                    index++;
                }
            }
            if (makeTrump) {
                std::cout << player[(handNumber + 1 + index) % 4]->get_name() 
                << " orders up " << upcardSuit << std::endl << std::endl;
                player[handNumber % 4]->add_and_discard(upcard);
                trump = upcardSuit;
                if((handNumber%2 == 0 && index %2 == 1) 
                || (handNumber%2 == 1 && index%2 == 0)) {
                    orderedUp = true;
                }
            }
            round++;
            index = 0;
            isDealer = false;
            while(!makeTrump) {
                ordering = true;
                if (index == 3) {
                    isDealer = true;
                }
                makeTrump = player[(handNumber + 1 + index) % 
                4]->make_trump(upcard, isDealer, round, upcardSuit);
                if (index == 3) {   
                    trump = Suit_next(upcard.get_suit());
                    std::cout << player[(handNumber + 1 + index) % 4]->get_name() 
                    << " orders up " << trump << std::endl << std::endl;
                }
                else if (makeTrump) {
                    trump = Suit_next(upcard.get_suit());
                    std::cout << player[(handNumber + 1 + index) % 4]->get_name() 
                    << " orders up " << trump << std::endl << std::endl;
                }
                else {
                    std::cout << player[(handNumber + 1 + index) % 
                    4]->get_name() << " passes" << std::endl;
                }
                index++;
            }
            if(ordering) {
                if((handNumber%2 == 0 && index %2 == 0) 
                || (handNumber%2 == 1 && index%2 == 1)) {
                    orderedUp = true;
                }
            }
        }

        // playing the game for the first round
        int playGameRound1() {
            Card cards[4];
            cards[(handNumber + 1) % 4] = player[(handNumber + 1) 
            % 4]->lead_card(trump);
            std::cout << cards[(handNumber + 1) % 4] << " led by " 
            << player[(handNumber + 1) % 4]->get_name() << std::endl;
            for (int i = 2; i <= 4; i++) {
                cards[(handNumber + i) % 4] = player[(handNumber + i) % 
                4]->play_card(cards[(handNumber + 1) % 4], trump);
                std::cout << cards[(handNumber + i) % 4] << " played by " 
                << player[(handNumber + i) % 4]->get_name() << std::endl;
            }
            int high_card_index = 0;
            for (int card = 1; card < 4; card++) {
                if (Card_less(cards[high_card_index], cards[card], 
                cards[(handNumber + 1) % 4], trump)) {
                    high_card_index = card;
                }
            }
            std::cout << player[high_card_index]->get_name() 
            << " takes the trick" << std::endl << std::endl;
            return high_card_index;
        }
        void delete_players() {
            for (int i = 0; i < 4; i++) {
                delete player[i];
            }
        }
    private:
        Player *player[4];
        std::string name = "";
        std::string strategy = "";
        std::string packName = "";
        std::string trump = "";
        int handNumber = 0;
        int finalScore = 0;  
};

//void dealHands(Player* player[], int handnumber, Pack &pack);
void printWinner(int score1, int score2, Player* player[]);
int check_tricks(int team1tricks, int team2tricks, 
bool ordered);
void calculateScore(int &trick_value, int &team1scores, int &team2scores, 
Player* player[]);
Card getUpcard(Pack &pack);
void score_incrementer(int& index, int& team1tricks, int& team2tricks);
void playGame(Player* player[], const int &handnumber, 
const std::string &trump, int array[]);
void set1(int &winner_index, int &team1trick, int &team2trick, int array[]);
void set2(int &winner_index, int &team1trick, int &team2trick, int array[]);
void print_error(bool &prints);
void check(int argc, char * argv[], bool &prints);

int main(int argc, char * argv[])
{
    bool prints = false;
    check(argc, argv, prints);
    if (prints) { return -1; }
    Game *e = new Game;
    e->print_header(argc, argv);
    int team1score = 0, team2score = 0, finalScore = atoi(argv[3]);
    e->set_final_score(argv);
    std::ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
        std::cout << "Error opening" << argv[1] << std::endl;
    }
    Pack pack(ifs);
    e->set_players(argv);
    while(team1score < finalScore && team2score < finalScore) {
        int team1trick = 0, team2trick = 0;
        bool orderedUp = false;
        pack.reset();
        if (strcmp(argv[2], "shuffle") == 0) { pack.shuffle(); }
        std::cout << "Hand " << e->get_handNumber() << std::endl;
        e->dealHands(pack);
        Card upcard = getUpcard(pack);
        e->print_upcard(upcard);
        e->makingTrump(upcard, orderedUp);
        // playing first round, person to the right of the dealer wins
        int winner_index = e->playGameRound1();
        score_incrementer(winner_index, team1trick, team2trick);
        // playing last four rounds
        int array[3] = {winner_index, team1trick, team2trick};
        playGame(e->get_player(), e->get_handNumber(), e->get_trump(), array);
        set2(winner_index, team1trick, team2trick, array);
        int trick_val = check_tricks(team1trick, team2trick, orderedUp);
        calculateScore(trick_val, team1score, team2score, e->get_player());
        e->increment_handNumber();
    }
    printWinner(team1score, team2score, e->get_player());
    //Deletes all players
    e->delete_players();
    delete e;
    return 0;
}

void printWinner(int score1, int score2, Player* player[])
{
    if(score1 > score2)
    {
        std::cout << player[0]->get_name() << " and " 
        << player[2]->get_name() << " win!" << std::endl;
    }

    else
    {
        std::cout << player[1]->get_name() << " and " 
        << player[3]->get_name() << " win!" << std::endl;;
    }
}

int check_tricks(int team1tricks, int team2tricks, bool ordered) {
    if(ordered && team1tricks > team2tricks) {
        if (team1tricks == 5) {
            return 1;
        }
        else {
            return 2;
        }
    }
    else if(ordered && team1tricks < team2tricks) {
        return 3;
    }
    else if(!ordered && team1tricks < team2tricks) {
        if (team2tricks == 5) {
            return 4;
        }
        else {
            return 5;
        }
    }
    else {
        return 6;
    }
}

void calculateScore(int &trick_value, 
int &team1scores, int &team2scores, Player* player[])
 {
     if(trick_value == 1 || trick_value == 2)
     {
         std::cout << player[0]->get_name() << " and " << player[2]->get_name() 
         << " win the hand" << std::endl; 
         if(trick_value == 1)
         {
             team1scores = team1scores + 2;
             std::cout << "march!" << std::endl;
         }
         else {
             team1scores++;
         }
     }

     else if(trick_value == 3)
     {
         team2scores = team2scores + 2;
         std::cout << player[1]->get_name() << " and " 
         << player[3]->get_name() 
         << " win the hand" << std::endl;
         std::cout << "euchred!" << std::endl; 
     }

     else if(trick_value == 4 || trick_value == 5)
     {
         std::cout << player[1]->get_name() << " and " 
         << player[3]->get_name()
         << " win the hand" << std::endl; 
         if(trick_value == 4)
         {
             team2scores = team2scores + 2;
             std::cout << "march!" << std::endl;
         }
         else {
             team2scores++;
         }
     }

     else
     {
         team1scores = team1scores + 2;
         std::cout << player[0]->get_name() << " and " 
         << player[2]->get_name() << " win the hand" << std::endl;
         std::cout << "euchred!" << std::endl; 
     }

     std::cout << player[0]->get_name() << " and " 
     << player[2]->get_name() << " have " 
     << team1scores << " points" << std::endl;
     std::cout << player[1]->get_name() << " and " 
     << player[3]->get_name() << " have " 
     << team2scores << " points" << std::endl << std::endl;
 }

 Card getUpcard(Pack &pack)
 {
     return pack.deal_one();
 }

void score_incrementer(int& index, int& team1tricks, int& team2tricks) {
    if (index % 2 == 0)
    {
        team1tricks++;
    }
    else
    {
        team2tricks++;
    }
}

void playGame(Player* player[], const int &handnumber, 
const std::string &trump, int array[]) {
    int round = 1;
    int *ptr = array;
    int winner_index = *ptr;
    ptr = ptr + 1;
    int team1tricks = *ptr;
    ptr = ptr + 1;
    int team2tricks = *ptr;
    while (round <= 4) {
        Card cards[4];
        int leadcard_index = winner_index % 4;
        cards[winner_index % 4] = player[winner_index % 
        4]->lead_card(trump);
        std::cout << cards[winner_index % 4] << " led by " 
        << player[winner_index % 4]->get_name() << std::endl;
        for (int i = 1; i < 4; i++) {
            cards[(winner_index + i) % 4] = player[(winner_index + i) % 
            4]->play_card(cards[winner_index % 4], trump);
            std::cout << cards[(winner_index + i) % 4] << " played by " 
            << player[(winner_index + i) % 4]->get_name() << std::endl;
        }
        winner_index = 0;
        for (int card = 1; card < 4; card++) {
            if (Card_less(cards[winner_index], cards[card], 
            cards[leadcard_index], trump)) {
                winner_index = card;
            }
        }
        std::cout << player[winner_index]->get_name() 
        << " takes the trick" << std::endl << std::endl;
        if (winner_index % 2 == 0)
        {
            team1tricks++;
        }
        else
        {
            team2tricks++;
        }
        round++;
    }
    ptr = array;
    *ptr = winner_index;
    ptr++;
    *ptr = team1tricks;
    ptr++;
    *ptr = team2tricks;
}

void set2(int &winner_index, int &team1trick, int &team2trick, int array[]) {
    int *ptr = array;
    winner_index = *ptr;
    ptr++;
    team1trick = *ptr;
    ptr++;
    team2trick = *ptr;
}

void check(int argc, char * argv[], bool &prints) {
    int i = 0;
    if (argc != 12) { 
        print_error(prints); 
        }
    else if (atoi(argv[3]) < 1 || atoi(argv[3]) > 100) { 
        print_error(prints); 
    }
    else if ((strcmp(argv[2], "shuffle") != 0) && (strcmp(argv[2], "noshuffle") != 0)) { 
        print_error(prints); 
    }
    else {
        while (i < 4) {
            if ((strcmp(argv[5 + 2*i], "Human") != 0) 
            && (strcmp(argv[5 + 2*i], "Simple") != 0)) {
                print_error(prints); 
                i = 5;
            }
            i++;
        }
    }
}

void print_error(bool &prints) {
    prints = true;
    std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;
}

