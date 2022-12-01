
/* Hitori
 *
 * Desc:
 *   This program implements a Hitori game with the game board of
 * size 5 x 5. Each square in the game board has a number from 1-5.
 * At first, each horizontal and vertical row can have several identical
 * numbers, but the purpose is to remove numbers such that each horizontal
 * and vertical row has no duplicate numbers. However, it is not possible
 * to remove numbers in adjacent squares, and none of the remaining
 * numbers (squares) can be isolated from the other ones, i.e. it is not
 * possible to remove all numbers around it (from strictly above, below,
 * left, right).
 *   At first, the user is asked, if the game board will be filled with
 * randomly drawn numbers 1-5, or with user-given 25 numbers. In the first
 * option, a seed value for the random number generator will be asked next.
 * In the latter option, the user is asked to input 25 numbers.
 *   On each round, the user is asked for coordinates, i.e. two numbers.
 * The player wins if each horizantal and vertical row has at most one
 * instance of each number 1-5. The player loses if they remove a number,
 * the adjacent number of which has already been removed or if a number
 * becomes isolated.
 *   The program checks the user-given coordinates. They must be inside the
 * game board, and the square indicated by them must have a number, i.e.
 * a number cannot be removed again.
 *   When the game ends, the program tells if the player won or lost.
 *
 * Program author
 * Name: Sanna Nykänen
 * Student number: 150384977
 * UserID: tvsany
 * E-Mail: sanna.nykanen@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */

#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

const int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';

using Gameboard = std::vector<std::vector<int>>;

// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns zero.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}


// Prints the game board with row and column numbers.
void print(const Gameboard& gameboard)
{
    cout << "=================" << endl;
    cout << "|   | 1 2 3 4 5 |" << endl;
    cout << "-----------------" << endl;
    for(int i = 0; i < BOARD_SIDE; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(int j = 0; j < BOARD_SIDE; ++j)
        {
            if(gameboard.at(i).at(j) == 0)
            {
                cout << EMPTY << " ";
            }
            else
            {
                cout << gameboard.at(i).at(j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "=================" << endl;
}


// Gameboard made from seed
void initializeRandom(Gameboard& board) {
    cout << "Enter a seed value: ";
    string seed_value_string = "";
    getline(cin, seed_value_string);
    int seed_value;
    seed_value = stoi_with_check(seed_value_string);
    default_random_engine gen(seed_value);
    std::uniform_int_distribution<int> distribution(1, 5);
    for(int y = 0; y < BOARD_SIDE; ++y ) {
        board.push_back({});

        for(int x = 0; x < BOARD_SIDE; ++x ) {
            board.at(y).push_back(distribution(gen));
        }
    }
}

// Split the input
vector<string> split(string line){
    vector<string> returnVec = {""};
    for (char c : line){
        if (c == ' ') {
           returnVec.push_back("");
        } else {
            returnVec.back() =+ c;
        }
    }
    return returnVec;
}

//Gameboard made from Input
void initializeInput(Gameboard& board) {
    string line = "";
    cout << "Input: ";
    getline(std::cin, line);
    vector<string> parts = split(line);
    for(int y = 0; y < BOARD_SIDE; ++y ) {
        board.push_back({});
        for(int x = 0; x < BOARD_SIDE; ++x ) {
            int part;
            part = stoi_with_check(parts.at(y * 5 + x));
            board.at(y).push_back(part);
        }
    }
}

bool readCoordinates(int& x, int& y) {
    string coordinates = "";

    while(true) {
        coordinates = "";
        cout << "Enter removable element (x, y): ";
        getline(cin, coordinates);
        vector temp = split(coordinates);
        if (temp.at(0) == "q" || temp.at(0) == "Q"){
            cout << "Quitting\n";
            exit(0);

        }
        int xm = stoi_with_check(temp.at(0));
        int ym = stoi_with_check(temp.at(1));
        if (xm <= 0 || ym <= 0 || xm > BOARD_SIDE || ym > BOARD_SIDE) {
            std::cout << "Out of board\n";
            continue;
        } else if(0 < xm and xm <= BOARD_SIDE and 0 < ym and ym <= BOARD_SIDE) {
            x = xm-1;
            y = ym-1;
            return true;
        }
    }
    return false;
}


//Checks is the coordinate index zero
bool isEmpty(Gameboard& board, int&x, int&y) {
    if (board.at(y).at(x) == 0) {
        cout << "Already removed\n";
        return false;
    }
    return true;
}

// Inserts zero to the removable index
bool removeCoordinate(Gameboard& board, int x, int y) {
    if (isEmpty(board, x, y) == false) {
            readCoordinates(x, y);
        }
    board.at(y).at(x) = 0;
    print(board);
    return true;
}


// Checks if number is an island
bool isIsland (Gameboard& board) {

    for (int y  = 0; y < BOARD_SIDE; ++y) {
        for (int x = 0; x < BOARD_SIDE; ++x) {
            if (board.at(y).at(x) != 0) {

                if (x-1 > 0 and board.at(y).at(x-1) != 0) {
                    continue;
                } else if (x+1 < BOARD_SIDE-1 and board.at(y).at(x+1) != 0) {
                    continue;
                } else if (y-1 > 0 and board.at(y-1).at(x) != 0){
                    continue;
                } else if (y+1 < BOARD_SIDE-1 and board.at(y+1).at(x) != 0) {
                    continue;
                } else {
                return true;
                }
            }
        }
    }
    return false;
}


// Checks is the surrounding index zero
bool noNeighbours(Gameboard& board, int& x, int& y){
    //on right
    if (x - 1 >= 0 and board.at(y).at(x-1) == 0) {
        return true;
    //on left
    } else if (x+1 < BOARD_SIDE and board.at(y).at(x+1) == 0) {
        return true;
    //below
    } else if (y-1 >= 0 and board.at(y-1).at(x) == 0) {
        return true;
    //on top
    } else if  (y+1 < BOARD_SIDE and board.at(y+1).at(x) == 0) {
        return true;
    }
    return false;
}


bool hasWon(Gameboard& board) {
    vector<unsigned int> same_numbersx = {0,0,0,0,0,0};
    vector<unsigned int> same_numbersy = {0,0,0,0,0,0};
    for(int y = 0; y < BOARD_SIDE; ++y ) {
        for(int x = 0; x < BOARD_SIDE; ++x ) {
            same_numbersx.at(board.at(y).at(x)) += 1;
            same_numbersy.at(board.at(x).at(y)) += 1;
        }
        for (unsigned long int j = 1; j < same_numbersx.size(); ++j ) {
            if (same_numbersx.at(j) > 1 or same_numbersy.at(j) > 1) {
                return false;
            }
        }
        same_numbersx.assign(6, 0);
        same_numbersy.assign(6, 0);
    }
    return true;
}


int main()
{
    Gameboard gameboard = {};
    string start = "";
    cout << "Select start (R for random, I for input): ";
    getline(cin, start);
    while (!(start == "R" || start == "Q" || start =="I" ||
             start == "r" || start == "q" || start == "i")) {
        cout << "Select start (R for random, I for input): ";
        getline(cin, start);
    }
    if (start == "R" || start == "r") {
        initializeRandom(gameboard);
        print(gameboard);
    } else if (start == "I" || start == "i") {
        initializeInput(gameboard);
        print(gameboard);
    } else if (start == "Q" || start =="q") {
        cout << "Quitting";
        return EXIT_SUCCESS;
    }
    int x = 0;
    int y = 0;


    while (not hasWon(gameboard) and not noNeighbours(gameboard,x, y)
           and readCoordinates(x, y) and removeCoordinate(gameboard, x, y)
           and not isIsland(gameboard)) {

        if (readCoordinates(x,y) == false) {
            return EXIT_SUCCESS;
        }
        removeCoordinate(gameboard, x, y);
        if (noNeighbours(gameboard,x, y)== true) {
            cout << "You lost\n";
            return EXIT_SUCCESS;
        }
        if (isIsland(gameboard) == true){
            cout << "You lost\n";
            return EXIT_SUCCESS;
        }
        if (hasWon(gameboard) == true) {
            cout << "You won\n";
            return EXIT_SUCCESS;
        }
    }
    return 0;
}