/*  COMP.CS.100 Project 2: GAME STATISTICS
 *
 * This program reads game statistics saved in file.
 * First program asks user to enter file name. Program reads the
 * file to map data structure.
 *
 * Acts as a game statistics with n commands:
 * ALL_GAMES - Prints all known game names
 * GAME <game name> - Prints all players playing the given game
 * ALL_PLAYERS - Prints all known player names
 * PLAYER <player name> - Prints all games the given player plays
 * ADD_GAME <game name> - Adds a new game
 * ADD_PLAYER <game name> <player name> <score> - Adds a new player with the
 * given score for the given game, or updates the player's score if the player
 * already playes the game
 * REMOVE_PLAYER <player name> - Removes the player from all games
 *
 *  The data file's lines should be in format game_name;player_name;score
 * Otherwise the program execution terminates instantly (but still gracefully).
 *
 * Program author
 * Name: Sanna Nykänen
 * Student number: 150384977
 * UserID: tvsany
 * E-Mail: sanna.nykanen@tuni.fi
 *
 * */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

using GAMES = map<string, map<string, int>>;

const string FILE_NOT_READ_TEXT = "Error: File could not be read.",
             INPUT_FILE_PROMPT = "Give a name for input file: ",
             FILE_FORMAT_INVALID_TEXT = "Error: Invalid format in file.",
             ALL_GAMES_PRINTOUT_TEXT = "All games in alphabetical order: ",
             INPUT_ERROR_TEXT = "Error: Invalid input.",
             PLAYER_NOT_FOUND_TEXT = "Error: Player could not be found.";

// Casual split func, if delim char is between "'s, ignores it.
vector<string> split( const string& str, char delim = ';' )
{
    vector<string> result = {""};
    bool inside_quatation = false;
    for ( auto current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quatation = not inside_quatation;
        }
        else if ( current_char == delim and not inside_quatation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

// Function checks that file format consist of three different informations
// and game name or gamer name is not empty
bool line_is_ok(vector<string> const &line_parts){
    return line_parts.size() == 3
           && !line_parts.at(0).empty()
           && !line_parts.at(1).empty();
}

// Function asks filename, reads the file to defined datastructure
bool read_file_input(GAMES &scoreboard) {
    string filename = "";

    cout << INPUT_FILE_PROMPT;
    getline(cin, filename);

    ifstream file(filename);
    if(!file){
        cout << FILE_NOT_READ_TEXT << endl;
        return false;
    }
    string line = "";
    vector<string> line_parts;
    while (getline(file, line)){
        line_parts = split(line);
        if (!line_is_ok(line_parts)){
            cout << FILE_FORMAT_INVALID_TEXT << endl;
            file.close();
            return false;
        }
        string gamename = line_parts.at(0),
               player = line_parts.at(1),
               points_str = line_parts.at(2);

        if (scoreboard.find(gamename) == scoreboard.end()) {
            scoreboard.insert({gamename, {}});
        }
        scoreboard.at(gamename).insert({player, stoi(points_str)});
    }
    return true;
}

// Function prints all games saved to the map
void print_all_games(GAMES const &scoreboard) {
    cout << ALL_GAMES_PRINTOUT_TEXT << endl;
    for(auto &entry : scoreboard){
        cout << entry.first << endl;
    }
}

// Function finds user input game and prints scores and players.
// Goes through the map, saves information in printable format to
// different temporary map.
void print_game_scores(GAMES const &scoreboard, string gname) {
    map<int, vector<string>> printed_scores;
    if (scoreboard.find(gname) != scoreboard.end()){
        cout << "Game " << gname << " has these scores and players, listed in ascending order: " << endl;

        for (auto &scores : scoreboard.at(gname)) {
            string player = scores.first;
            int score = scores.second;
            if (printed_scores.find(score) != printed_scores.end()){
                printed_scores.at(score).push_back(player);
            } else {
                printed_scores.insert({score, {player}});
            }
        }

        for (auto &scores : printed_scores) {
            cout << scores.first << " : ";
            if (scores.second.size() > 1){
                for (unsigned int i = 0; i < scores.second.size(); i++){
                    if (i == scores.second.size()-1){
                        cout << scores.second.at(i) << endl;
                    } else {
                        cout << scores.second.at(i) << ", ";
                    }

                }
            } else {
                cout << scores.second.at(0) << endl;
            }
        }
    } else {
        cout << "Error: Game could not be found." << endl;
    }
}

// Fuction goes throught map and saves player names
// to set for printing in alphabetical order.
void print_all_players(GAMES const &scoreboard) {
    cout << "All players in alphabetical order: " << endl;
    set<string> players = {};
    for (auto &ent1: scoreboard) {
        for (auto const &ent2 : ent1.second) {
            string name = "";
            name = ent2.first;
            players.insert(name);
        }
    }
    for (auto &names : players){
        cout << names << endl;
    }
}

// Gets input player name, goes trough the map and prints out what games player plays
void print_player_games(GAMES const &scoreboard, string player) {
    set<string> games = {};
    for (auto &ent1: scoreboard) {
        auto const game = ent1;
        for (auto const &ent2 : ent1.second) {

        if (ent2.first == player) {
            games.insert(ent1.first);
        }
        }
    }
    if (games.empty()) {
        cout << PLAYER_NOT_FOUND_TEXT << endl;
    } else {
        cout << "Player " << player << " playes the following games: " << endl;
        for (auto &names : games){
            cout << names << endl;
        }
    }
}

// Check does game already exist in the list. If not,
// game is added to the list
void add_game(GAMES &scoreboard, string newgame) {
    if (scoreboard.find(newgame) != scoreboard.end()){
        cout << "Error: Already exists." << endl;
    } else {
        scoreboard.insert({newgame, {}});
        cout << "Game was added." << endl;
    }
}

// Function adds player to asked game. If player already exisist in a game,
// player's score is updated
void add_player(GAMES &scoreboard, string game, string player, string score_str) {

        if (scoreboard.find(game) == scoreboard.end()){
            cout << "Error: Game could not be found." << endl;
        } else {
            bool player_added = false;
            for (auto &ent1: scoreboard) {
                if (ent1.second.find(player) != ent1.second.end()){
                    scoreboard.at(game).at(player) = stoi(score_str);
                } else {
                    scoreboard.at(game).insert({player, stoi(score_str)});
                    player_added = true;
                }
            }
            if (player_added){
            cout << "Player was added." << endl;
            }
        }
}

// Function takes in scoreboard and player name
// and deletes player from every game
void remove_player(GAMES &scoreboard, string player){
    bool player_deleted = false;
    for (auto &ent1: scoreboard) {
        if (ent1.second.find(player) != ent1.second.end()){
            ent1.second.erase(ent1.second.find(player));
            player_deleted = true;
        }
    }
    if (player_deleted) {
        cout << "Player was removed from all games." << endl;
    } else {
        cout << PLAYER_NOT_FOUND_TEXT << endl;
    }
}

// Reads user input, runs the programm as long as user types "Quit"
bool play_game(GAMES &scoreboard) {
    string user_input = "";
    cout << "games> ";
    getline(cin, user_input);
    if (user_input.empty()) {
        cout << INPUT_ERROR_TEXT << endl;
        return true;
    }

    vector<string> parts = {};
    parts = split(user_input, ' ');

    string command = "";
    for(char& c : parts.at(0)) {
        command += toupper(c);
    }

    if (command == "QUIT") {
        return false;
        //exit(0);
    } else if (command == "ALL_GAMES"){
        print_all_games(scoreboard);
    } else if (command == "GAME"){
        if (parts.size() < 2){
            cout << INPUT_ERROR_TEXT << endl;
            return true;
        }
        string gamename = parts.at(1);
        print_game_scores(scoreboard, gamename);
    } else if (command == "ALL_PLAYERS") {
        print_all_players(scoreboard);
    } else if (command == "PLAYER"){
        string playername = parts.at(1);
        print_player_games(scoreboard, playername);
    } else if (command == "ADD_GAME"){
        string newgame = parts.at(1);
        add_game(scoreboard, newgame);
    } else if (command == "ADD_PLAYER"){
        unsigned int required_input_size = 4;
        if (parts.size() != required_input_size) {
            cout << INPUT_ERROR_TEXT << endl;
            return true;
        }
        string gamename = parts.at(1);
        string player = parts.at(2);
        string score_str = parts.at(3);
        add_player(scoreboard, gamename, player, score_str);
    } else if (command == "REMOVE"){
        string player = parts.at(1);
        remove_player(scoreboard, player);
    } else {
        cout << INPUT_ERROR_TEXT << endl;
    }
    return true;
}


int main()
{
    //Database used: map<string, map<string, int>>
    //game name, player, points
    GAMES scoreboard;
    if (!read_file_input(scoreboard)) {
        return EXIT_FAILURE;
    }
    while (play_game(scoreboard)) {
    }
    return EXIT_SUCCESS;

}