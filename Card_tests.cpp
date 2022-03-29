// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

TEST(euchre_test) {
    Card led = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(ace_hearts, jack_hearts, led,
                           Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(jack_hearts, ace_hearts, led,
                           Card::SUIT_HEARTS));
}

TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

TEST(test_card_suit_and_rank) {
    Card two_spades = Card();
    ASSERT_EQUAL(two_spades.get_rank(), Card::RANK_TWO);
    ASSERT_EQUAL(two_spades.get_suit(), Card::SUIT_SPADES);

    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_EQUAL(three_spades.get_rank(), Card::RANK_THREE);
    ASSERT_EQUAL(three_spades.get_suit(), Card::SUIT_SPADES);
    ASSERT_EQUAL(three_spades.get_suit(Card::SUIT_CLUBS), Card::SUIT_SPADES);
}

TEST(test_card_type) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    
    ASSERT_FALSE(three_spades.is_face());
    ASSERT_FALSE(three_spades.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(three_spades.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(three_spades.is_trump(Card::SUIT_CLUBS));
    ASSERT_TRUE(jack_spades.is_right_bower(Card::SUIT_SPADES));
    ASSERT_TRUE(jack_clubs.is_left_bower(Card::SUIT_SPADES));
    ASSERT_TRUE(jack_spades.is_face());
    ASSERT_TRUE(jack_spades.is_trump(Card::SUIT_SPADES));
}

TEST(test_card_comparison) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(three_spades < three_spades);
    ASSERT_TRUE(three_spades <= three_spades);
    ASSERT_FALSE(three_spades > three_spades);
    ASSERT_TRUE(three_spades >= three_spades);
    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_FALSE(three_spades != three_spades);
    
    ASSERT_TRUE(three_spades < jack_spades);
    ASSERT_TRUE(three_spades <= jack_spades);
    ASSERT_FALSE(three_spades > jack_spades);
    ASSERT_FALSE(three_spades >= jack_spades);
    ASSERT_FALSE(three_spades == jack_spades);
    ASSERT_TRUE(three_spades != jack_spades);
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);
}

TEST(test_Card_less_self) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(Card_less(three_spades, three_spades, Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(three_spades, three_spades, three_spades,
                           Card::SUIT_CLUBS));
}

TEST(test_card_insertion) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}

TEST(lead_is_trump) {
    Card led = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card nine_clubs = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);  
    ASSERT_FALSE(Card_less(nine_clubs, jack_hearts, led,
                           Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(jack_hearts, nine_clubs, led,
                           Card::SUIT_CLUBS));                       
}

TEST(lead_and_not_lead) {
    Card led = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card nine_clubs = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);  
    ASSERT_FALSE(Card_less(nine_clubs, jack_hearts, led,
                           Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(jack_hearts, nine_clubs, led,
                           Card::SUIT_SPADES));                       
}


TEST(diamonds_vs_clubs) {
    Card led = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(ten_clubs, ten_diamonds, led,
                           Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(ten_diamonds, ten_clubs, led,
                           Card::SUIT_HEARTS));
}

TEST(diamonds_vs_hearts) {
    Card led = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(ten_hearts, ten_diamonds, led,
                           Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(ten_diamonds, ten_hearts, led,
                           Card::SUIT_SPADES));                     
}

TEST(diamonds_vs_spades) {
    Card led = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(ten_spades, ten_diamonds, led,
                           Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(ten_diamonds, ten_spades, led,
                           Card::SUIT_HEARTS));
}

TEST(clubs_vs_hearts) {
    Card led = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(ten_hearts, ten_clubs, led,
                           Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(ten_clubs, ten_hearts, led,
                           Card::SUIT_SPADES));
}

TEST(clubs_vs_spades) {
    Card led = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(ten_spades, ten_clubs, led,
                           Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(ten_clubs, ten_spades, led,
                           Card::SUIT_HEARTS));
}

TEST(hearts_vs_spades) {
    Card led = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(ten_spades, ten_hearts, led,
                           Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(ten_hearts, ten_spades, led,
                           Card::SUIT_CLUBS));
}

TEST(left_bower_vs_trump_suit) {
    Card led = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card left_bower = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card ace_clubs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(ace_clubs, left_bower, led,
                           Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(left_bower, ace_clubs, led,
                           Card::SUIT_CLUBS));
}

TEST(right_bower_vs_left_bower) {
    Card led = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card right_bower = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card left_bower = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(left_bower, right_bower, led,
                           Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(right_bower, left_bower, led,
                           Card::SUIT_SPADES));
}

TEST(high_spade_vs_low_diamond) {
    Card led = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(nine_diamonds, ace_spades, led,
                           Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(ace_spades, nine_diamonds, led,
                           Card::SUIT_HEARTS));
}

TEST(ifstatement1){
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card three_diamonds = Card(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    Card five_hearts = Card(Card::RANK_FIVE, Card::SUIT_HEARTS);

    //Tests to see if right bower is higher than left bower
    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, jack_diamonds, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(jack_spades, jack_clubs, jack_diamonds, Card::SUIT_SPADES));
   
   //Tests to see if left bower is higher than led card
    ASSERT_TRUE(Card_less(jack_diamonds, jack_clubs, queen_diamonds, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(jack_clubs, jack_diamonds, queen_diamonds, Card::SUIT_SPADES));
   
    //Tests to see if trump is higher than led card
    ASSERT_TRUE(Card_less(jack_diamonds, nine_spades, queen_diamonds, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(nine_spades, jack_diamonds, queen_diamonds, Card::SUIT_SPADES));
   
    //Tests to see if card is higher when both are trump
    ASSERT_TRUE(Card_less(ten_spades, queen_spades, queen_diamonds, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(queen_spades, ten_spades, queen_diamonds, Card::SUIT_SPADES));
    
    //Tests to see if trump is higher than led card
    ASSERT_TRUE(Card_less(three_diamonds, jack_spades, queen_diamonds, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(jack_spades, three_diamonds, queen_diamonds, Card::SUIT_SPADES));
    
    //Tests to see if led card is higher than normal card
    ASSERT_TRUE(Card_less(five_hearts, three_diamonds, queen_diamonds, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(three_diamonds, five_hearts, queen_diamonds, Card::SUIT_SPADES));
}

TEST(ifstatement2){
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card three_diamonds = Card(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    Card five_hearts = Card(Card::RANK_FIVE, Card::SUIT_HEARTS);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    
    //Tests to see if right bower is higher than left bower
    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(jack_spades, jack_clubs, Card::SUIT_SPADES));
   
    //Tests to see if card is higher when both are trump
    ASSERT_TRUE(Card_less(ten_spades, queen_spades, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(queen_spades, ten_spades, Card::SUIT_SPADES));
    
    ASSERT_TRUE(Card_less(jack_diamonds, jack_clubs, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(jack_clubs, jack_diamonds, Card::SUIT_SPADES));

    ASSERT_TRUE(Card_less(jack_diamonds, queen_diamonds, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(queen_diamonds, jack_diamonds, Card::SUIT_SPADES));

    ASSERT_TRUE(Card_less(jack_diamonds, queen_diamonds, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(queen_diamonds, jack_diamonds, Card::SUIT_SPADES));
}    



// Add more test cases here

TEST_MAIN()
