#include <iostream>
#include <random>
#include <string>

using namespace std;

class Board {
    public:
    char state[9];
    string board_str;
    int round = 0;
    int game_state = 0; // 0 = ongoing, 1 = computer won, 2 = player won, 3 = tie

    // For multiplayer:
    bool multiplayer = false;

    Board() {
        // Initialize with numbers for player to see
        for (int i = 0; i < 9; ++i) {
            state[i] = i+49;
        }
        set_board();
        cout << board_str << endl;
        for (int i = 0; i < 9; ++i) {
            state[i] = ' ';
        }
        set_board();
    }

    void set_board() {
        board_str =
        "     |     |     \n"
        "  " + string(1, state[0]) + "  |  " + string(1, state[1]) + "  |  " + string(1, state[2]) + "  \n"
        "_____|_____|_____\n"
        "     |     |     \n"
        "  " + string(1, state[3]) + "  |  " + string(1, state[4]) + "  |  " + string(1, state[5]) + "  \n"
        "_____|_____|_____\n"
        "     |     |     \n"
        "  " + string(1, state[6]) + "  |  " + string(1, state[7]) + "  |  " + string(1, state[8]) + "  \n"
        "     |     |     ";
    }

    void print_board() {
        cout << board_str << endl;
    }

    // Returns the int of the best play (1-9)
    int computer_turn(const char marker, int prev_play) {

        // For multiplayer:
        if(multiplayer) {
            int player_input;
            cout << "Your turn, you are " << marker << "s. Input a space 1-9" << endl;
            while(true) {
                cin >> player_input;
                if (state[player_input-1] != ' ') {
                    cout << "That space is taken :(";
                }
                else {
                    return player_input;
                }
            }
        }

        // Computer plays first
        if (marker == 'X') {
            if (round == 0) {
                return 1;
            }
            else if (round == 2) {
                if (state[1] == 'O' || state[3] == 'O' || state[5] == 'O' || state[7] == 'O') {
                    return 5;
                }
                else if (state[8] == 'O') {
                    return 7;
                }
                else {
                    return 9;
                }
            }
            else if (round == 4) {
                int result;
                if (result = check_for_wins(marker)) {
                    return result;
                }
                else if (result = check_for_losses(marker)) {
                    return result;
                }
                else if (state[1] == 'O' && state[6] == ' ') {
                    return 7;
                }
                else if (state[3] == 'O' && state[2] == ' ') {
                    return 3;
                }
                else {
                    for(int i = 3; i < 8; i+=4) {
                        if (state[i-1] == ' ') {
                            return i;
                        }
                    }
                    return 0;
                }
            }
            else if (round >= 6) {
                int result;
                if (result = check_for_wins(marker)) {
                    return result;
                }
                else if (result = check_for_losses(marker)) {
                    return result;
                }
                else {
                    for (int i = 0; i < 9; i++) {
                        if (state[i] == ' ') {
                            return i+1;
                        }
                        return 0;
                    }
                }
            }
        }

        // Player plays first
        else {
            if (round == 2) {
                if (state[4] == ' ') {
                    return 5;
                }
                else {
                    return 1;
                }
            }
            else if (round == 4) {
                int result;
                if (result = check_for_losses(marker)) {
                    return result;
                }
                else if (state[0] == marker) {
                    return 9;
                }
                else {
                    if ((state[2] == 'X' || state[0] == 'X') && state[7] != 'X' && state[1] == ' ') {
                        return 2;
                    }
                    else if ((state[6] == 'X' || state[8] == 'X') && state[1] != 'X' && state[7] == ' ') {
                        return 8;
                    }
                    else if (state[1] == 'X' || state[7] == 'X') {
                        if (state[3] == ' ') {
                            return 4;
                        }
                        else {
                            return 6;
                        }
                    }
                    else {
                        if (state[1] == ' ') {
                            return 2;
                        }
                        else {
                            return 8;
                        }
                    }
                }
            }
            else if (round == 6) {
                int result;
                if (result = check_for_wins(marker)) {
                    return result;
                }
                else if (result = check_for_losses(marker)) {
                    return result;
                }
                else {
                    if (state[8] == ' ') {
                        return 9;
                    }
                    else if (state[6] == ' ') {
                        return 7;
                    }
                    else if (state[2] == ' ') {
                        return 3;
                    }
                    else if (state[0] == ' ') {
                        return 1;
                    }
                    else {
                        for (int i = 0; i < 9; i++) {
                            if (state[i] == ' ') {
                               return i+1;
                            }
                        }
                    }
                }
            }
            else {
                int result;
                if (result = check_for_wins(marker)) {
                    return result;
                }
                else if (result = check_for_losses(marker)) {
                    return result;
                }
                else {
                    for (int i = 0; i < 9; i++) {
                        if (state[i] == ' ') {
                           return i+1;
                        }
                    }
                }
            }
        }
        return 0;
    }

    void next_turn() {

        set_board();
        print_board();
        round++;
    }

    int check_state() {
        // Check for a win
        if ((state[0] == state[1] && state[0] == state[2] && state[0] >= 79) || (state[3] == state[4] && state[3] == state[5] && state[3] >= 79) ||
            (state[6] == state[7] && state[6] == state[8] && state[6] >= 79) || (state[0] == state[3] && state[0] == state[6] && state[0] >= 79) ||
            (state[1] == state[4] && state[1] == state[7] && state[1] >= 79) || (state[2] == state[5] && state[2] == state[8] && state[2] >= 79) ||
            (state[0] == state[4] && state[0] == state[8] && state[0] >= 79) || (state[2] == state[4] && state[2] == state[6] && state[2] >= 79)) {
                // Check who's win it was
                if(round % 2) { 
                    return 1;
                }
                else {
                    return 2;
                }
        }

        // Check for a tie
        for(int i = 0; i < 9; i++) {
            if(state[i] == ' ') {
                return 0;
            }
        }
        return 3;
    }

    int check_for_wins(char player) {

        // Horizontal
        for(int i = 0; i < 8; i+=3) {
            if (state[i] == state[i+1] && state[i] == player && state[i+2] == ' ') {
                return i+3;
            }
        }   
        for(int i = 0; i < 8; i+=3) {
            if (state[i] == state[i+2] && state[i] == player && state[i+1] == ' ') {
                return i+2;
            }
        } 
        for(int i = 0; i < 8; i+=3) {
            if (state[i+1] == state[i+2] && state[i+1] == player && state[i] == ' ') {
                return i+1;
            }
        } 

        // Vertical
        for(int i = 0; i < 3; i++) {
            if (state[i] == state[i+3] && state[i] == player && state[i+6] == ' ') {
                return i+7;
            }
        }
        for(int i = 0; i < 3; i++) {
            if (state[i] == state[i+6] && state[i] == player && state[i+3] == ' ') {
                return i+4;
            }
        }
        for(int i = 0; i < 3; i++) {
            if (state[i+3] == state[i+6] && state[i+3] == player && state[i] == ' ') {
                return i+1;
            }
        }

        // Diagonal
        if (state[0] == state[4] && state[0] == player && state[8] == ' ') {
            return 9;
        }
        if (state[0] == state[8] && state[0] == player && state[4] == ' ') {
            return 5;
        }
        if (state[4] == state[8] && state[4] == player && state[0] == ' ') {
            return 1;
        }
        if (state[2] == state[4] && state[2] == player && state[6] == ' ') {
            return 7;
        }
        if (state[2] == state[6] && state[2] == player && state[4] == ' ') {
            return 5;
        }
        if (state[4] == state[6] && state[4] == player && state[2] == ' ') {
            return 3;
        }
        
        return 0;
    }

    int check_for_losses(char player) {
        if (player == 'X') {
            return check_for_wins('O');
        }
        else {
            return check_for_wins('X');
        }
    }

    void reset() {
        for(int i = 0; i < 9; i++) {
            state[i] = ' ';
        }
        round = 0;
        set_board();
        multiplayer = false;
    }

};

int main() {

    char player_marker;
    char computer_marker;
    int player_input;
    int coin;

    cout << "Welcome to Tic-Tac-Toe. Prepare to be defeated." << endl;

    // Initialize game board
    Board board;
    cout << "Type the cooresponding number to play in that square." << endl;

    while(true) {

    // Decide who plays first
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> flip(0, 1); 

    coin = flip(gen); // 0 = player, 1 = computer

    if (coin) {
        cout << "You are playing Os, and will play second." << endl;
        player_marker = 'O';
        computer_marker = 'X';
    }
    else {
        cout << "You are playing Xs, and will play first." << endl;
        board.round = 1;
        player_marker = 'X';
        computer_marker = 'O';
        
    }

    string s;
    cout << "Press y when you want to begin the game" << endl;
    cin >> s;
    if (s == "s") {
        board.reset();
        continue;
    }
    else if (s == "m") {
        board.multiplayer = true;
        cout << "You have entered MULTIPLAYER MODE" << endl;
    }


    board.print_board();
        
        while(true) {
            // Player's turn
            if (board.round % 2) {
                cout << "Your turn, you are " << player_marker << "s. Input a space 1-9" << endl;
                cin >> player_input;
                if (board.state[player_input-1] != ' ') {
                    cout << "That space is taken :(";
                    continue;
                }
                board.state[player_input-1] = player_marker;
            }

            // Computer's turn
            else {
                cout << "Computer's turn" << endl;
                int play;
                if (play = board.computer_turn(computer_marker, player_input)) {
                    board.state[play-1] = computer_marker;
                }
                else {
                    cout << "Oepsie Poepsie you just did a fuckie wuckie uwu " << play << endl;
                }
            }

            board.next_turn();

            board.game_state = board.check_state();
            if(board.game_state) {
                break;
            }
        }

        if (board.game_state == 1) {
            cout << "You lose lol. Get wrecked." << endl;
        }
        else if (board.game_state == 2) {
            cout << "You won somehow. Did you cheat?" << endl;
        }
        else {
            cout << "Tie. Good job, this is the best possible outcome for you" << endl;
        }
        cout << "Would you like to play again? [y/n]" << endl;
        string ans;
        cin >> ans;
        if (ans[0] != 'y') {
            cout << "Good game :)" << endl;
            break;
        }
        else {
            board.reset();
        }
    }
    return 0;
}