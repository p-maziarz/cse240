#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

class Player {
public:
    Player() : name(""), num_guesses(0) {}
    Player(string nm, int ng) : name(nm), num_guesses(ng) {}

    string GetName() const {
        return name;
    }

    int GetNumGuesses() const {
        return num_guesses;
    }

    void SetName(const string& nm) {
        name = nm;
    }

    void SetNumGuesses(int ng) {
        num_guesses = ng;
    }

private:
    string name;
    int num_guesses;
};

class LeaderBoard {
public:
    LeaderBoard() {
        for (int i = 0; i < NUM_LEADERS; ++i) {
            leaders[i] = Player("", 0); // Initialize players with default values
        }
        // Load leaderboard data from a file
        ReadLeaders("leaderboard.txt");
    }

    void ReadLeaders(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < NUM_LEADERS; ++i) {
                string name;
                int num_guesses;
                if (file >> name >> num_guesses) {
                    leaders[i] = Player(name, num_guesses); // Initialize the player object
                }
            }
            file.close();
        }
    }


    void InsertPlayer(const Player& player) {
        // Insert the player into the leaderboard if their score is high enough
        for (int i = 0; i < NUM_LEADERS; ++i) {
            if (player.GetNumGuesses() < leaders[i].GetNumGuesses()) {
                for (int j = NUM_LEADERS - 1; j > i; --j) {
                    leaders[j] = leaders[j - 1];
                }
                leaders[i] = player;
                break;
            }
        }
    }

    void SaveLeaders(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < NUM_LEADERS; ++i) {
                file << leaders[i].GetName() << " " << leaders[i].GetNumGuesses() << endl;
            }
            file.close();
        }
    }

    void DisplayLeaderboard() {
        cout << "Leaderboard:\n";
        for (int i = 0; i < NUM_LEADERS; ++i) {
            cout << leaders[i].GetName() << " - " << leaders[i].GetNumGuesses() << " guesses" << endl;
        }
    }

private:
    static const int NUM_LEADERS = 5;
    Player leaders[NUM_LEADERS];
};

int main() {
    LeaderBoard leaderboard;
    srand(static_cast<unsigned>(time(0))); // Seed the random number generator

    char c;
    bool game_over = false;

    while (!game_over) {
        Player current_player;

        cout << "Welcome! Press 'q' to quit or any other key to continue:\n";
        cin >> c;
        if (c == 'q') {
            game_over = true;
            cout << "Bye Bye!\n";
        } else {
            // Reset the leaderboard display flag
            bool display_leaderboard = false;

            while (true) {
                cout << "Enter your name: ";
                string name;
                cin >> name;
                current_player.SetName(name);

                int num_guesses = 0;
                int target = rand() % 100 + 1;
                int guess;

                while (true) {
                    cout << "Guess a number between 1 and 100: ";
                    cin >> guess;
                    num_guesses++;

                    if (guess == target) {
                        cout << "Congratulations! You guessed the correct number in " << num_guesses << " attempts.\n";
                        current_player.SetNumGuesses(num_guesses);
                        leaderboard.InsertPlayer(current_player);
                        display_leaderboard = true; // Set the flag to display the leaderboard
                        break; // Exit the game loop
                    } else if (guess < target) {
                        cout << "Try a higher number.\n";
                    } else {
                        cout << "Try a lower number.\n";
                    }
                }

                if (display_leaderboard) {
                    // Display and save the leaderboard after a game
                    leaderboard.DisplayLeaderboard();
                    leaderboard.SaveLeaders("leaderboard.txt");
                }

                cout << "Press 'q' to quit or any other key to play again: ";
                cin >> c;

                if (c == 'q') {
                    game_over = true;
                    break;
                }
            }
        }
    }

    return 0;
}
