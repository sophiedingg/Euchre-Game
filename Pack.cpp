// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include <array>
#include <string>
#include <cassert>

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
    for (int s = 0;s < NUM_SUITS; s++) {
        for (int r = 7; r < NUM_RANKS; r++) {
            Card c(RANK_NAMES_BY_WEIGHT[r], SUIT_NAMES_BY_WEIGHT[s]);
            cards[(s * (PACK_SIZE / NUM_SUITS)) + (r - 7)] = c;
        }
    }
    next = 0;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
    for (int i = 0; i < PACK_SIZE; i++) {
        std::string rank = "";
        std::string suit = "";
        std::string junk = "";
        pack_input >> rank >> junk >> suit;
        Card c(rank, suit);
        cards[i] = c;
    }
    next = 0;
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    std::string temp_Suit = cards[next].get_suit();
    std::string temp_Rank = cards[next].get_rank();
    Card temp(temp_Rank, temp_Suit);
    next++;
    return temp;
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    std::array<Card, PACK_SIZE> temp1;
    std::array<Card, PACK_SIZE> temp2;
    for(int i = 0; i < (PACK_SIZE/2); i++){
        temp1[2*i] = cards[PACK_SIZE/2 + i];
        temp1[2*i + 1] = cards[i];
    }
    for(int i = 1; i < 7; i++) {
        for(int j = 0; j < (PACK_SIZE/2); j++) {
            if (i%2 == 0) {
                temp1[2*j] = temp2[PACK_SIZE/2 + j];
                temp1[2*j + 1] = temp2[j];
            }
            else {
                temp2[2*j] = temp1[PACK_SIZE/2 + j];
                temp2[2*j + 1] = temp1[j];
            }

        }
    }
    cards = temp1;
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const{
    if (next == PACK_SIZE) {
        return true;
    }
    return false;
}
