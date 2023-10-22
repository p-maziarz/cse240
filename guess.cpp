#include <iostream>
#include <fstream>
#include <string>

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
                    leaders[i].SetName(name);
                    leaders[i].SetNumGuesses(num_guesses);
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
    cout << "Welcome! Press 'q' to quit or any other key to continue:\n";
    char c;
    bool game_over = false;

    while (!game_over) {
        cin >> c;
        if (c == 'q') {
            game_over = true;
            cout << "Bye Bye!\n";
        } else {
            Player current_player;
            cout << "Enter your name: ";
            string name;
            cin >> name;
            current_player.SetName(name);

            // Implement the guessing game logic here
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
                    break; // Exit the game loop and prompt to play again or quit
                } else if (guess < target) {
                    cout << "Try a higher number.\n";
                } else {
                    cout << "Try a lower number.\n";
                }
            }
        }
        // Display and save the leaderboard at the end of each game
        leaderboard.DisplayLeaderboard();
        leaderboard.SaveLeaders("leaderboard.txt");
        cout << "Press 'q' to quit or any other key to play again: ";
    }

    return 0;
}
