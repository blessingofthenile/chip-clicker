#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// Function to calculate the total value of a hand
int calculateHandValue(const vector<int>& hand) {
    int sum = 0;
    int numAces = 0;

    for (int card : hand) {
        if (card == 1) {  // Ace
            sum += 11;
            numAces++;
        } else if (card > 10) {  // Face cards
            sum += 10;
        } else {
            sum += card;
        }
    }

    // Adjust for aces
    while (sum > 21 && numAces > 0) {
        sum -= 10;
        numAces--;
    }

    return sum;
}

// Function to display the current state of the game
void displayGameState(const vector<int>& playerHand, const vector<int>& dealerHand, bool showAll) {
    cout << "Your hand: ";
    for (int card : playerHand) {
        cout << card << " ";
    }
    cout << "  (Total: " << calculateHandValue(playerHand) << ")" << endl;

    cout << "Dealer's hand: ";
    if (showAll) {
        for (int card : dealerHand) {
            cout << card << " ";
        }
        cout << "  (Total: " << calculateHandValue(dealerHand) << ")" << endl;
    } else {
        cout << dealerHand[0] << " ?" << endl;
    }
}

// Function to perform the player's turn
void playerTurn(vector<int>& playerHand, vector<int>& deck) {
    char choice;

    while (true) {
        displayGameState(playerHand, deck, false);

        cout << "Do you want to 'hit' (h) or 'stand' (s)? ";
        cin >> choice;

        if (choice == 'h') {
            // Draw a card and add it to the player's hand
            playerHand.push_back(deck.back());
            deck.pop_back();

            // Check for bust
            if (calculateHandValue(playerHand) > 21) {
                displayGameState(playerHand, deck, false);
                cout << "Bust! You lose." << endl;
                break;
            }
        } else if (choice == 's') {
            break;
        } else {
            cout << "Invalid choice. Please enter 'h' or 's'." << endl;
        }
    }
}

// Function to perform the dealer's turn
void dealerTurn(vector<int>& dealerHand, vector<int>& deck) {
    while (calculateHandValue(dealerHand) < 17) {
        dealerHand.push_back(deck.back());
        deck.pop_back();
    }

    displayGameState(dealerHand, deck, true);

    if (calculateHandValue(dealerHand) > 21) {
        cout << "Dealer bust! You win." << endl;
    } else {
        cout << "Dealer stands." << endl;
    }
}

int main() {
    // Seed for random shuffle
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialize the deck
    vector<int> deck;
    for (int i = 1; i <= 13; ++i) {
        for (int j = 0; j < 4; ++j) {
            deck.push_back(i);
        }
    }

    // Shuffle the deck
    random_shuffle(deck.begin(), deck.end());

    // Deal initial cards
    vector<int> playerHand;
    vector<int> dealerHand;
    playerHand.push_back(deck.back());
    deck.pop_back();
    dealerHand.push_back(deck.back());
    deck.pop_back();
    playerHand.push_back(deck.back());
    deck.pop_back();
    dealerHand.push_back(deck.back());
    deck.pop_back();

    // Player's turn
    playerTurn(playerHand, deck);

    // Dealer's turn (if player didn't bust)
    if (calculateHandValue(playerHand) <= 21) {
        dealerTurn(dealerHand, deck);
    }

    // Determine the winner
    int playerTotal = calculateHandValue(playerHand);
    int dealerTotal = calculateHandValue(dealerHand);

    if (playerTotal <= 21 && (dealerTotal > 21 || playerTotal > dealerTotal)) {
        cout << "Congratulations! You win!" << endl;
    } else if (playerTotal == dealerTotal) {
        cout << "It's a tie!" << endl;
    } else {
        cout << "Sorry, you lose." << endl;
    }

    return 0;
}
