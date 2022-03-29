// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

TEST(euchre_test_1) {
    Player * Tom = Player_factory("Tom", "Simple");
    Card led_card = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card upcard = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);

    Tom->add_card(ten_diamonds);
    Tom->add_card(ten_hearts);

    ASSERT_EQUAL(Tom->play_card(jack_diamonds, "Hearts"), ten_hearts);
    delete Tom;
}

TEST(test_player_insertion) {
  // Create a Human player
  Player * human = Player_factory("NotRobot", "Human");

  // Print the player using the stream insertion operator
  ostringstream oss1;
  oss1 << * human;

  // Verify that the output is the player's name
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  // Create a Simple player
  Player * alice = Player_factory("Alice", "Simple");

  // Print the player using the stream insertion operator
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  // Clean up players that were created using Player_factory()
  delete human;
  delete alice;
}

TEST(test_player_get_name) {
  // Create a player and verify that get_name() returns the player's name
  Player * alice = Player_factory("Alice", "Simple");
  ASSERT_EQUAL(alice->get_name(), "Alice");
  delete alice;
}

TEST(test_simple_player_make_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  delete bob;
}

TEST(make_trump) {
    Player * Player_1 = Player_factory("Player 1", "Simple");
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ace_clubs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card upcard = Card(Card::RANK_ACE, Card::SUIT_HEARTS);

    Player_1->add_card(jack_diamonds);
    Player_1->add_card(queen_diamonds);
    Player_1->add_card(nine_spades);
    Player_1->add_card(ten_spades);
    Player_1->add_card(ace_clubs);

    bool is_dealer = true;
    string suit = "Hearts";
    Player_1->make_trump(upcard, is_dealer, 1, suit);

    delete Player_1;
}

TEST(simple_player_make_trump_two_face_cards) {
    Player * Tom = Player_factory("Tom", "Simple");
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ace_clubs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card upcard = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    Tom->add_card(jack_diamonds);
    Tom->add_card(queen_diamonds);
    Tom->add_card(nine_spades);
    Tom->add_card(ten_spades);
    Tom->add_card(ace_clubs);

    bool is_dealer = true;
    string suit = "Diamonds";
    
    ASSERT_TRUE(Tom->make_trump(upcard, is_dealer, 1, suit));

    delete Tom;
}

TEST(simple_player_make_trump_one_face_card_upcard_is_not_face) {
    Player * Tom = Player_factory("Tom", "Simple");
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ace_clubs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card upcard = Card(Card::RANK_NINE, Card::SUIT_CLUBS);

    Tom->add_card(jack_diamonds);
    Tom->add_card(queen_diamonds);
    Tom->add_card(nine_spades);
    Tom->add_card(ten_spades);
    Tom->add_card(ace_clubs);

    bool is_dealer = true;
    string suit = "Clubs";
    ASSERT_FALSE(Tom->make_trump(upcard, is_dealer, 1, suit));

    delete Tom;
}

TEST(simple_player_make_trump_three_face_cards) {
    Player * Tom = Player_factory("Tom", "Simple");
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ace_clubs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card upcard = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    Tom->add_card(jack_diamonds);
    Tom->add_card(queen_diamonds);
    Tom->add_card(king_diamonds);
    Tom->add_card(ten_spades);
    Tom->add_card(ace_clubs);

    bool is_dealer = true;
    string suit = "Diamonds";
    ASSERT_TRUE(Tom->make_trump(upcard, is_dealer, 1, suit));

    delete Tom;
}

TEST(simple_player_make_trump_round_2_one_face_card) {
    Player * Tom = Player_factory("Tom", "Simple");
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card upcard = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    Tom->add_card(nine_diamonds);
    Tom->add_card(queen_diamonds);
    Tom->add_card(king_diamonds);
    Tom->add_card(ten_spades);
    Tom->add_card(ace_hearts);

    bool is_dealer = true;
    string suit = "Hearts";
    ASSERT_TRUE(Tom->make_trump(upcard, is_dealer, 2, suit));

    delete Tom;
}

TEST(simple_player_make_trump_round_2_no_face_cards) {
    Player * Tom = Player_factory("Tom", "Simple");
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card upcard = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    Tom->add_card(nine_diamonds);
    Tom->add_card(queen_diamonds);
    Tom->add_card(king_diamonds);
    Tom->add_card(ten_spades);
    Tom->add_card(ace_diamonds);

    bool is_dealer = false;
    string suit = "Hearts";
    ASSERT_FALSE(Tom->make_trump(upcard, is_dealer, 2, suit));

    delete Tom;
}

TEST(simple_player_make_trump_round_2_left_bower) {
    Player * Tom = Player_factory("Tom", "Simple");
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card upcard = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    Tom->add_card(nine_diamonds);
    Tom->add_card(queen_diamonds);
    Tom->add_card(king_diamonds);
    Tom->add_card(jack_diamonds);
    Tom->add_card(ace_diamonds);

    bool is_dealer = true;
    string suit = "Hearts";
    ASSERT_TRUE(Tom->make_trump(upcard, is_dealer, 2, suit));

    delete Tom;
}

TEST(simple_player_make_trump_round_2_trump_non_face_cards) {
    Player * Tom = Player_factory("Tom", "Simple");
    Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card upcard = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    Tom->add_card(nine_hearts);
    Tom->add_card(queen_diamonds);
    Tom->add_card(king_diamonds);
    Tom->add_card(jack_spades);
    Tom->add_card(ace_diamonds);

    bool is_dealer = false;
    string suit = "Hearts";

    ASSERT_FALSE(Tom->make_trump(upcard, is_dealer, 2, suit));

    delete Tom;
}


TEST(simple_player_make_trump_round_2_screw_dealer) {
    Player * Tom = Player_factory("Tom", "Simple");
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card upcard = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    Tom->add_card(nine_spades);
    Tom->add_card(queen_diamonds);
    Tom->add_card(king_diamonds);
    Tom->add_card(jack_spades);
    Tom->add_card(ace_diamonds);

    bool is_dealer = true;
    string suit = "Hearts";

    ASSERT_TRUE(Tom->make_trump(upcard, is_dealer, 2, suit));

    delete Tom;
}

TEST(simple_player_add_and_discard_upcard) {
    Player * Tom = Player_factory("Tom", "Simple");
    Card led_card = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card upcard = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);

    Tom->add_card(ten_diamonds);
    Tom->add_card(queen_diamonds);
    Tom->add_card(king_diamonds);
    Tom->add_card(ace_diamonds);
    Tom->add_card(jack_diamonds);
    
    Tom->add_and_discard(upcard);
    
    // should have discarded the nine of diamonds

    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_DIAMONDS) != upcard);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_DIAMONDS) != upcard);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_DIAMONDS) != upcard);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_DIAMONDS) != upcard);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_DIAMONDS) != upcard);

    delete Tom;
}

TEST(simple_player_add_and_discard_all_trump_suits_and_left_bower) {
    Player * Tom = Player_factory("Tom", "Simple");
    Card led_card = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card upcard = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);

    Tom->add_card(nine_diamonds);
    Tom->add_card(queen_diamonds);
    Tom->add_card(king_diamonds);
    Tom->add_card(jack_diamonds);
    Tom->add_card(jack_hearts);
    
    Tom->add_and_discard(upcard);

    // should have discarded nine of diamonds

    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_DIAMONDS) != nine_diamonds);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_DIAMONDS) != nine_diamonds);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_DIAMONDS) != nine_diamonds);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_DIAMONDS) != nine_diamonds);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_DIAMONDS) != nine_diamonds);
    
    delete Tom;
}

TEST(simple_player_add_and_discard_all_off_suits) {
    Player * Tom = Player_factory("Tom", "Simple");
    Card led_card = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card nine_clubs = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card upcard = Card(Card::RANK_NINE, Card::SUIT_HEARTS);

    Tom->add_card(ten_diamonds);
    Tom->add_card(nine_clubs);
    Tom->add_card(nine_spades);
    Tom->add_card(jack_clubs);
    Tom->add_card(ace_spades);
    
    Tom->add_and_discard(upcard);

    // should have discarded nine of spades
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_DIAMONDS) != nine_spades);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_DIAMONDS) != nine_spades);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_DIAMONDS) != nine_spades);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_DIAMONDS) != nine_spades);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_DIAMONDS) != nine_spades);

    delete Tom;
}

TEST(simple_player_add_and_discard_upcard_is_right_bower) {
    Player * Tom = Player_factory("Tom", "Simple");
    Card led_card = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card queen_hearts = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card upcard = Card(Card::RANK_JACK, Card::SUIT_HEARTS);

    Tom->add_card(queen_hearts);
    Tom->add_card(king_hearts);
    Tom->add_card(ace_hearts);
    Tom->add_card(jack_diamonds);
    Tom->add_card(ace_spades);
    
    Tom->add_and_discard(upcard);

    // should have discarded ace of spades
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_HEARTS) != ace_spades);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_HEARTS) != ace_spades);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_HEARTS) != ace_spades);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_HEARTS) != ace_spades);
    ASSERT_TRUE(Tom->play_card(led_card, Card::SUIT_HEARTS) != ace_spades);

    delete Tom;
}

TEST(simple_player_play_card_trump_vs_lead) {
    Player * Tom = Player_factory("Tom", "Simple");
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card upcard = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);

    Tom->add_card(nine_diamonds);
    Tom->add_card(queen_diamonds);
    Tom->add_card(king_diamonds);
    Tom->add_card(ace_spades);
    Tom->add_card(jack_spades);
    
    Tom->add_and_discard(upcard);
    
    delete Tom;
}

TEST(leadcard) {
    Player * Jerry = Player_factory("Jerry", "Simple");
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);

    // testing to see if you play the highest trump card not including right and left bowers
    Jerry->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Jerry -> lead_card(Card::SUIT_SPADES), Card(Card::RANK_ACE, Card::SUIT_SPADES));
    delete Jerry;

    // checking lead with right bower
    Jerry = Player_factory("Jerry", "Simple");
    Jerry->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Jerry -> lead_card(Card::SUIT_SPADES), Card(Card::RANK_JACK, Card::SUIT_SPADES));
    delete Jerry;

    // checking lead with left bower
    Jerry = Player_factory("Jerry", "Simple");
    Jerry->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    Jerry->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Jerry -> lead_card(Card::SUIT_SPADES), Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    delete Jerry;

    // hearts vs spades --> no trump cards
    Jerry = Player_factory("Jerry", "Simple");
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    Jerry->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Jerry -> lead_card(Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    delete Jerry;

    // hearts vs spades --> has right bower only
    Jerry = Player_factory("Jerry", "Simple");
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    Jerry->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    Jerry->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Jerry -> lead_card(Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_HEARTS)); 
    delete Jerry;

    // hearts vs spades --> has left bower only
    Jerry = Player_factory("Jerry", "Simple");
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    Jerry->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Jerry -> lead_card(Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    delete Jerry;

    // spades vs clubs --> two trump cards
    Jerry = Player_factory("Jerry", "Simple");
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    Jerry->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    Jerry->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Jerry -> lead_card(Card::SUIT_HEARTS), Card(Card::RANK_ACE, Card::SUIT_SPADES));  
    delete Jerry;     

    // test three of same rank and two trumps
    Jerry = Player_factory("Jerry", "Simple");
    Jerry->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    Jerry->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    Jerry->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    Jerry->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    ASSERT_EQUAL(Jerry -> lead_card(Card::SUIT_HEARTS), Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));  
    delete Jerry;   

    // trump cards listed first
    // same test cards are added in different order: spades vs clubs --> two trump cards
    Jerry = Player_factory("Jerry", "Simple");
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    Jerry->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    Jerry->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    Jerry->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Jerry -> lead_card(Card::SUIT_HEARTS), Card(Card::RANK_ACE, Card::SUIT_SPADES));  
    delete Jerry;    

    // trump cards listed last
    // same test cards are added in different order: spades vs clubs --> two trump cards
    Jerry = Player_factory("Jerry", "Simple");
    Jerry->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    Jerry->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    ASSERT_EQUAL(Jerry -> lead_card(Card::SUIT_HEARTS), Card(Card::RANK_ACE, Card::SUIT_SPADES));  
    delete Jerry;   
}

TEST(cardplay) {
    //Tests playcard function with all regular trump
    Player * Jerry = Player_factory("Jerry", "Simple");
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Jerry->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Jerry -> play_card(queen_diamonds, Card::SUIT_SPADES), Card(Card::RANK_NINE, Card::SUIT_SPADES));
    delete Jerry;
   
    //Tests playcard function with four regular trump and right bower
    Jerry = Player_factory("Jerry", "Simple");
    Jerry->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Jerry -> play_card(queen_diamonds, Card::SUIT_SPADES), Card(Card::RANK_NINE, Card::SUIT_SPADES));
    delete Jerry;

    //Tests playcard function with four regular trump and left bower
    Jerry = Player_factory("Jerry", "Simple");
    Jerry->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    Jerry->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Jerry -> play_card(queen_diamonds, Card::SUIT_SPADES), Card(Card::RANK_NINE, Card::SUIT_SPADES));
    delete Jerry;

    //Tests playcard function with all led cards
    Jerry = Player_factory("Jerry", "Simple");
    Jerry->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    Jerry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Jerry -> play_card(Card(Card::RANK_JACK, Card::SUIT_SPADES), Card::SUIT_DIAMONDS), Card(Card::RANK_ACE, Card::SUIT_SPADES));
    delete Jerry;

    //Tests playcard function with all led cards and left bower
    Player * Werry = Player_factory("Jerry", "Simple");
    Werry->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    Werry->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    Werry->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    Werry->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    Werry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Werry -> play_card(Card(Card::RANK_JACK, Card::SUIT_SPADES), Card::SUIT_DIAMONDS), Card(Card::RANK_ACE, Card::SUIT_SPADES));
    delete Werry;

    //Tests playcard function with all nonled/trump cards
    Player * Derry = Player_factory("Jerry", "Simple");
    Derry->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    Derry->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    Derry->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    Derry->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    Derry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Derry -> play_card(queen_diamonds, Card::SUIT_CLUBS), Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    delete Derry;

    //Tests playcard function with nonled and led cards
    Player * Berry = Player_factory("Jerry", "Simple");
    Berry->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    Berry->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    Berry->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Berry->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    Berry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Berry -> play_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES), Card::SUIT_HEARTS), Card(Card::RANK_ACE, Card::SUIT_SPADES));
    delete Berry;

    Player * Merry = Player_factory("Jerry", "Simple");
    Merry->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    Merry->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    Merry->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    Merry->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    Merry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Merry -> play_card(queen_diamonds, Card::SUIT_HEARTS), Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    delete Merry;

    Player * Lerry = Player_factory("Jerry", "Simple");
    Lerry->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    Lerry->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    Lerry->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    Lerry->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    Lerry->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Lerry -> play_card(Card(Card::RANK_KING, Card::SUIT_CLUBS), Card::SUIT_DIAMONDS), Card(Card::RANK_NINE, Card::SUIT_SPADES));
    delete Lerry;
}

TEST(play_card_left_bower_is_led_card_suit)
{
    Player * Tom = Player_factory("Tom", "Simple");
    Card led_card = Card(Card::RANK_NINE, Card::SUIT_SPADES);

    Tom->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    Tom->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    Tom->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    Tom->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Tom->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));

    ASSERT_EQUAL(Tom -> play_card(led_card, Card::SUIT_CLUBS), Card(Card::RANK_TEN, Card::SUIT_SPADES));
    delete Tom;
}

TEST(addCardFunction_playCard1)
{
    Player * Lerry = Player_factory("Jerry", "Simple");
    Lerry->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Lerry -> play_card(Card(Card::RANK_KING, Card::SUIT_CLUBS), Card::SUIT_DIAMONDS), Card(Card::RANK_NINE, Card::SUIT_SPADES));
    delete Lerry;
}

TEST(leadCard1)
{
    Player * Lerry = Player_factory("Jerry", "Simple");
    Lerry->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Lerry -> lead_card(Card::SUIT_DIAMONDS), Card(Card::RANK_NINE, Card::SUIT_SPADES));
    delete Lerry;
}

TEST(playCard3)
{
    Player * Isabel = Player_factory("Jerry", "Simple");
    Isabel->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Isabel->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    Isabel->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    ASSERT_EQUAL(Isabel -> play_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS), Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    ASSERT_EQUAL(Isabel -> play_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS), Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Isabel -> play_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS), Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    delete Isabel;
}

TEST(leadCard3)
{
    Player * Isabel = Player_factory("Jerry", "Simple");
    Isabel->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Isabel->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    Isabel->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    ASSERT_EQUAL(Isabel -> lead_card(Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Isabel -> lead_card(Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    ASSERT_EQUAL(Isabel -> lead_card(Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    delete Isabel;
}

TEST(lead_and_play_Card3)
{
    Player * Isabel = Player_factory("Isabel", "Simple");
    Isabel->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Isabel->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    Isabel->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    ASSERT_EQUAL(Isabel -> lead_card(Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Isabel -> play_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS), Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    ASSERT_EQUAL(Isabel -> play_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS), Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    delete Isabel;
}

TEST(addDiscardSimplePlayer)
{
    Player * Jess = Player_factory("Jerry", "Simple");
    Jess->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Jess->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    Jess->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    ASSERT_EQUAL(Jess -> lead_card(Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_SPADES));
    delete Jess;
}

// simple player has all hearts, but the order up suit is spades


TEST_MAIN()
