// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// compares right and left bowers for card less
bool Card_less_r_l(const Card &a, const Card &b,
               const std::string &trump, bool& passes);

// compares suits for card less
bool Card_less_suits(const Card &a, const Card &b,
               const std::string &trump, bool& passes);

// compares two cards of the same rank for card less
bool Card_less_same_rank(const Card &a, const Card &b,
               const std::string &trump, bool& passes);

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below

  //EFFECTS Initializes Card to the Two of Spades
  Card::Card() {
      rank = RANK_TWO;
      suit = SUIT_SPADES;
  }

  //REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
  //  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
  //  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
  //EFFECTS Initializes Card to specified rank and suit
  Card::Card(const std::string &rank_in, const std::string &suit_in) {
      rank = rank_in;
      suit = suit_in;
  }
  //EFFECTS Returns the rank
  std::string Card::get_rank() const {
      return rank;
  }

  //EFFECTS Returns the suit.  Does not consider trump.
  std::string Card::get_suit() const {
      return suit;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns the suit
  //HINT: the left bower is the trump suit!
  std::string Card::get_suit(const std::string &trump) const {
      if (this->is_left_bower(trump)) {
          return trump;
      }
      else {
          return get_suit();
      }
  }

  //EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
  bool Card::is_face() const {
      if (rank == RANK_KING || rank == RANK_QUEEN 
      || rank == RANK_JACK || rank == RANK_ACE) {
          return true;
      }
      else {
          return false;
      }
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the trump suit
  bool Card::is_right_bower(const std::string &trump) const {
      if (get_rank() == RANK_JACK && is_trump(trump) && !is_left_bower(trump)) {
          return true;
      }
      return false;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the next suit
  bool Card::is_left_bower(const std::string &trump) const {
      if (get_rank() == RANK_JACK && Suit_next(trump) == suit) {
          return true;
      }
      return false;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
  bool Card::is_trump(const std::string &trump) const {
      if (suit == trump || is_left_bower(trump)) {
          return true;
      }
      else {
          return false;
      }
  }


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:

//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
    int i = 0;
    int j = 0;
    while (lhs.get_rank() != RANK_NAMES_BY_WEIGHT[i]) {
        i++;
    }
    while (rhs.get_rank()!= RANK_NAMES_BY_WEIGHT[j]) {
        j++;
    }
    if (i >= j) {
        return false;
    }
    else {
        return true;
    }
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs)
{
    return lhs < rhs || lhs.get_rank() == rhs.get_rank();
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs)
{
    return !(lhs <= rhs);
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs)
{
    return !(lhs < rhs);
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
    return (lhs.get_rank() == rhs.get_rank()) && (lhs.get_suit() == rhs.get_suit()); 
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs)
{
    return !(lhs == rhs);
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit)
{
    if (suit == SUIT_NAMES_BY_WEIGHT[0]) {
        return SUIT_NAMES_BY_WEIGHT[2];
    }
    else if (suit == SUIT_NAMES_BY_WEIGHT[1]) {
        return SUIT_NAMES_BY_WEIGHT[3];
    }
    else if (suit == SUIT_NAMES_BY_WEIGHT[2]) {
        return SUIT_NAMES_BY_WEIGHT[0];
    }
    return SUIT_NAMES_BY_WEIGHT[1];
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card)
{
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

// compares right and left bowers for card less with led_card
bool Card_less_r_l(const Card &a, const Card &b,
               const std::string &trump, bool& passes) {
    if (a.is_right_bower(trump))
    {
        passes = true;
        return false;
        
    }
    if (b.is_right_bower(trump)) {
        passes = true;
        return true;
    }
    else if (a.is_left_bower(trump))
    {
        passes = true;
        return false;
    }
    else if (b.is_left_bower(trump)) {
        passes = true;
        return true;
    }   
    passes = false;
    return false;
}

// compares suits for card less
bool Card_less_suits(const Card &a, const Card &b,
               const std::string &trump, bool& passes) {
    if ((a.get_suit(trump) == b.get_suit(trump)) && a > b) {
        passes = true;
        return false;
    }
    else if ((a.get_suit(trump) == b.get_suit(trump)) && a < b) {
        passes = true;
        return true;
    }
    else if(a.is_trump(trump) && !b.is_trump(trump))
    {
        passes = true;
        return false;
    }
    else if(b.is_trump(trump) && !a.is_trump(trump))
    {
        passes = true;
        return true;
    }
    passes = false;
    return false;
}

bool Card_less_same_rank(const Card &a, const Card &b,
               const std::string &trump, bool& passes) {
    if (a.get_rank() == b.get_rank()) {
        int i = 0;
        int j = 0;
        while (a.get_suit() != SUIT_NAMES_BY_WEIGHT[i]) {
            i++;
        }
        while (b.get_suit() != SUIT_NAMES_BY_WEIGHT[j]) {
            j++;
        }
        if (i > j) {
            passes = true;
            return false;
        }
        else if (i < j) {
            passes = true;
            return true;
        }
    }
    passes = false;
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump)
{
    bool passes = false;
    bool return_val = false;
    if (a == b) {
        return false;
    }
    return_val = Card_less_r_l(a, b, trump, passes);
    if (passes == true) {
        return return_val;
    }
    return_val = Card_less_suits(a, b, trump, passes);
    if (passes == true) {
        return return_val;
    }
    else if (a > b && !b.is_trump(trump)) {
        passes = true;
        return false;
    }
    else if (a < b && !b.is_trump(trump)) {
        passes = true;
        return true;
    }
    return_val = Card_less_same_rank(a, b, trump, passes);
    if (passes == true) {
        return return_val;
    }
    return true;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
    bool passes = false;
    bool return_val = false;
    if (a == b) {
        return false;
    }
    return_val = Card_less_r_l(a, b,
               trump, passes);
    if (passes == true) {
                   return return_val;
               }
    const Card cards[3] = {a, b, led_card};
    return_val = Card_less_suits(a, b, trump, passes);
    if (passes == true) {
        return return_val;
    }
    if (a.get_suit(trump) == led_card.get_suit(trump) 
    && b.get_suit(trump) != led_card.get_suit(trump)) {
        return false;
    }
    else if (b.get_suit(trump) == led_card.get_suit(trump) 
    && a.get_suit(trump) != led_card.get_suit(trump)) {
        return true;
    }
    else if (a > b) {
        return false;
    }
    else if (a < b) {
        return true;
    }
    return_val = Card_less_same_rank(a, b, trump, passes);
    if (passes == true) {
        return return_val;
    }
    return true;
}
