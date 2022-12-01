/* Game named 2048
 *
 * Desc:
 * This program is made for game called 2048 with board size 4 x 4.
 * Idea of the game is to get 2048 to one square.
 * Game is played by moving gameboard numbers to combine them.
 * To squares with same value are combined together when user moves
 * gameboard numbers. Two twos will become four and two fours
 * will become eight etc. Game is lost if the gameboard is full of
 * numbers, no combinations are possible and none of the squares
 * has the value of 2048.
 *
 * To play the game user has to set up seed value.
 * User can also change maximum points, default is 2048.
 * User has to click "start" button to start the game. Program
 * fills numbers to the gameboard radomly.
 * Game is played with using arrow buttons: up, left, down, right.
 * Timer starts when user has clicked start button.
 *
 * User can reset the game any time. In this case user has to give new
 * seed number and press start to start the game. The timer will start
 * from zero.
 * Program will tell by printing text and changing the main window
 * backgroud color about win or lose situations.
 *
 * Program author
 * Name: Sanna Nykänen
 * Student number: 150384977
 * UserID: tvsany
 * E-Mail: sanna.nykanen@tuni.fi
 *
 * */
#include "gameboard.hh"
#include <iostream>

GameBoard::GameBoard()
{
}

GameBoard::~GameBoard()
{
    for(unsigned int y = 0; y < board_.size(); ++y)
    {
        for(unsigned int x = 0; x < board_.at(y).size(); ++x)
        {
            delete board_.at(x).at(y);
            board_.at(x).at(y) = nullptr;
        }
    }
}

void GameBoard::init_empty()
{
    std::vector<NumberTile*> row;
    for( int i = 0; i < SIZE; ++i)
    {
        row.push_back(nullptr);
    }
    for( int i = 0; i < SIZE; ++i)
    {
        board_.push_back(row);
    }
}

void GameBoard::fill(int seed)
{
    randomEng_.seed(seed);
    distribution_ = std::uniform_int_distribution<int>(0, SIZE - 1);

    // Wiping out the first random number (which is almost almost 0)
    distribution_(randomEng_);

    for( auto y = 0; y < SIZE; ++y )
    {
        for( auto x = 0; x < SIZE; ++x )
        {
            board_.at(y).at(x) = new NumberTile(0, std::make_pair(y, x), this);
        }
    }

    for( int i = 0 ; i < SIZE ; ++i )
    {
        new_value();
    }
}

void GameBoard::new_value(bool check_if_empty)
{
    if( check_if_empty and is_full() ){
        // So that we will not be stuck in a forever loop
        return;
    }
    int random_x = 0;
    int random_y = 0;
    do
    {
        random_x = distribution_(randomEng_);
        random_y = distribution_(randomEng_);
    } while( not board_.at(random_y).at(random_x)->new_value(NEW_VALUE) );
}

void GameBoard::print() const
{
    for( auto y : board_ )
    {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for( auto x : y )
        {
            x->print(PRINT_WIDTH);
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

bool GameBoard::move(Coords dir, int goal)
{
    bool has_won = false;
    for( unsigned y = 0; y < board_.size(); ++y )
    {
        for( unsigned x = 0; x < board_.front().size(); ++x )
        {
            int directed_y = dir.first > 0 ? board_.size() - y - 1 : y;
            int directed_x = dir.second > 0 ? board_.back().size() - x - 1 : x;
            if( board_.at(directed_y).at(directed_x)->move(dir, goal) )
            {
                has_won = true;
            }
        }
    }
    for( auto &row : board_ )
    {
        for( auto &tile : row )
        {
            tile->reset_turn();
        }
    }
    return has_won;
}

NumberTile* GameBoard::get_item(Coords coords)
{
    return board_.at(coords.first).at(coords.second);
}

// Function sets the values of vector as nullptrs
void GameBoard::emptyVector()
{
    for (unsigned int i = 0; i<board_.size(); i++){
        for (unsigned int j = 0; j<board_.size(); j++){
            board_.at(i).at(j) = nullptr;
        }
    }
}

bool GameBoard::is_full() const
{
    for( auto y : board_ )
    {
        for( auto x : y )
        {
            if( x->is_empty() )
            {
                return false;
            }
        }
    }
    return true;
}
