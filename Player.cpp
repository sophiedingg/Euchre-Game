    // Project UID 1d9f47bfc76643019cfbf037641defe1

    #include <iostream>
    #include <string>
    #include <cassert>
    #include <vector>
    #include <algorithm>
    #include "Player.h"

    //EFFECTS: Prints player's name to os
    std::ostream & operator<<(std::ostream &os, const Player &p) {
        os << p.get_name();
        return os;
    }

    class Human : public Player {
    private:
        std::string name;
        std::vector<Card> hand;
        void print_hand() const {
            for (int card = 0; card < static_cast<int>(hand.size()); card++) {
                std::cout << "Human player " << name << "'s hand: [" << card
                << "] " << hand[card] << std::endl;
            }
        }
    public:
        Human(std::string input_name) {
            name = input_name;
        }
        const std::string & get_name() const override {
            return name;
        }

        void add_card(const Card &c) override {
            hand.push_back(c);
            std::sort(hand.begin(), hand.end());
        }
        bool make_trump(const Card &upcard, bool is_dealer,
                            int round, std::string &order_up_suit) const override {
            print_hand();
            std::cout << "Human player " << get_name() 
            << ", please enter a suit, or \"pass\":" << std::endl;
            std::string input_move = "";
            std::cin >> input_move;
            if (round == 1) {
                if (input_move != "pass") {
                    order_up_suit = upcard.get_suit();
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                if (is_dealer) {
                    order_up_suit = input_move;
                    return true;
                }
                if (input_move != "pass") {
                    order_up_suit = input_move;   
                    return true;
                }
                else {
                    return false;
                }
            }
            return false;
        }

        void add_and_discard(const Card &upcard) override {
            print_hand();
            std::cout << "Discard upcard: [-1]" << std::endl;
            std::cout << "Human player " << get_name() 
            << ", please select a card to discard:" << std::endl;
            int discard_index = 0;
            std::cin >> discard_index;
            if (discard_index > -1) {
                hand.erase(hand.begin() + discard_index);
                add_card(upcard);
            }
        }

        Card lead_card(const std::string &trump) override {
            print_hand();
            std::cout << "Human player " << get_name() 
            << ", please select a card:" << std::endl;
            int discard_index = 0;
            std::cin >> discard_index;
            Card temp_card = hand[discard_index];
            hand.erase(hand.begin() + discard_index);
            return temp_card;
        }
        Card play_card(const Card &led_card, const std::string &trump) override {
            print_hand();
            std::cout << "Human player " << get_name() 
            << ", please select a card:" << std::endl;
            int discard_index = 0;
            std::cin >> discard_index;
            Card temp_card = hand[discard_index];
            hand.erase(hand.begin() + discard_index);
            return temp_card;
        }
        std::vector<Card> get_hand() {
            return hand;
        }
    };

    class Simple : public Player {
    private:
        std::string name;
        std::vector<Card> hand;
    public:
        Simple(std::string input_name) {
            name = input_name;
        }
        const std::string & get_name() const override {
            return name;
        }

        void add_card(const Card &c) override {
            sort(hand.begin(), hand.end());
            hand.push_back(c);
        }

        bool make_trump(const Card &upcard, bool is_dealer,
                            int round, std::string &order_up_suit) const override {
            if (round == 1) {
                int num_trump_face_cards = 0;
                for (unsigned int card = 0; card < MAX_HAND_SIZE; card++) {
                    if ((hand[card].get_suit() == upcard.get_suit() 
                    && hand[card].is_face()) 
                    || hand[card].is_left_bower(order_up_suit)) {
                        num_trump_face_cards++;
                    }
                }
                if (num_trump_face_cards >= 2) {
                    order_up_suit = upcard.get_suit();    
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                if (is_dealer) {
                    order_up_suit = Suit_next(upcard.get_suit());
                    return true;
                }
                int num_next_suit_face_cards = 0;
                for (int card = 0; card < MAX_HAND_SIZE; card++) {
                    if (hand[card].get_suit() == Suit_next(upcard.get_suit()) 
                    && hand[card].is_face()) {
                        num_next_suit_face_cards++;
                    }
                    else if (hand[card].is_left_bower(order_up_suit)) {
                        num_next_suit_face_cards++;
                    }
                }
                if (num_next_suit_face_cards > 0) {
                    order_up_suit = Suit_next(upcard.get_suit());    
                    return true;
                }
                else {
                    return false;
                }
            }
        }

        void add_and_discard(const Card &upcard) override {
            hand.push_back(upcard);
            int low_card_index = 0;
            for (unsigned int card = 1; card < hand.size(); card++) {
                if (Card_less(hand[card], hand[low_card_index], upcard.get_suit())) {
                    low_card_index = card;
                }
            }
            hand.erase(hand.begin() + low_card_index);
        }

        Card lead_card(const std::string &trump) override {
            bool has_non_trump = true;
            int index = 0;
            int size = hand.size();
            int num_trumps = 0;
            for (unsigned int card = 0; card < hand.size(); card++) {
                if (hand[card].is_trump(trump) || hand[card].is_left_bower(trump)) {
                    num_trumps++;
                }
            }
            if (num_trumps == size) {
                has_non_trump = false;
            }
            if (has_non_trump) {
                index = 0;
                while (hand[index].is_trump(trump) || hand[index].is_left_bower(trump)) {
                    index++;
                }
                for (unsigned int card = index + 1; card < hand.size(); card++) {
                    if (Card_less(hand[index], hand[card], trump) 
                    && !(hand[card].is_trump(trump)) 
                    && !(hand[card].is_left_bower(trump))) {
                        index = card;
                    }
                }
            }
            else {
                Card removed_Card = hand[get_highest_card_index(hand.size(), trump)];
                hand.erase(hand.begin() + get_highest_card_index(hand.size(), trump));
                return removed_Card;

            }
            Card removed_Card = hand[index];
            hand.erase(hand.begin() + index);
            return removed_Card;
        }

        Card play_card(const Card &led_card, const std::string &trump) override {
            bool can_follow_suit = false;
            int high_card_index = 0;
            int size = hand.size();
            while(high_card_index < size && !can_follow_suit)
            {
                if (hand[high_card_index].get_suit(trump) == led_card.get_suit(trump)) {
                    can_follow_suit = true;
                }
                else
                {
                    high_card_index++;
                }
            }
            if (can_follow_suit) {
                for (unsigned int card = 1 + high_card_index; 
                card < hand.size(); card++) {
                    if (Card_less(hand[high_card_index], hand[card], trump) && 
                        hand[card].get_suit(trump) == led_card.get_suit(trump)) {
                        high_card_index = card;
                    }
                }
            }
            else {
                Card removed_Card = 
                hand[(get_lowest_with_led(hand.size(), led_card, trump))];
                hand.erase(hand.begin() + 
                (get_lowest_with_led(hand.size(), led_card, trump)));
                return removed_Card;
            }
            Card removed_Card = hand[high_card_index];
            hand.erase(hand.begin() + high_card_index);
            return removed_Card;
        }
        std::vector<Card> get_hand() {
            return hand;
        }
        int get_lowest_card_index(int hand_size, std::string trump) {
            int low_card_index = 0;
            for (int card = 1; card < hand_size; card++) {
                if (Card_less(hand[card], hand[low_card_index], trump)) {
                    low_card_index = card;
                }
            }
            return low_card_index;
        }
        int get_highest_card_index(int hand_size, std::string trump) {
            int high_card_index = 0;
            for (int card = 1; card < hand_size; card++) {
                if (Card_less(hand[high_card_index], hand[card], trump)) {
                    high_card_index = card;
                }
            }
            return high_card_index;
        }
        int get_lowest_with_led(int hand_size, Card led, 
        std::string trump) {
            int low_card_index = 0;
            for (int card = 1; card < hand_size; card++) {
                if (Card_less(hand[card], hand[low_card_index], led, trump)) {
                    low_card_index = card;
                }
            }
            return low_card_index;
        }
    };

    //EFFECTS: Returns a pointer to a player with the given name and strategy
    //To create an object that won't go out of scope when the function returns,
    //use "return new Simple(name)" or "return new Human(name)"
    //Don't forget to call "delete" on each Player* after the game is over
    Player * Player_factory(const std::string &name, const std::string &strategy) {
        if (strategy == "Human") {
            return new Human(name);
        }
        else {
            return new Simple(name);
        }
        assert(false);
        return nullptr;
    }