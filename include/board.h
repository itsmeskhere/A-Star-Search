#ifndef BOARD
#define BOARD

#include <iostream>
#include <fstream>
#include <sstream>

#include "a_star_search.h"

using std::cout;
using std::endl;
using std::ws;
using std::ifstream;
using std::istringstream;

vector<State> ParseLine(string &line);

vector<vector<State>> ReadBoard(string &file_path);

vector<int> FindStartAndFinish(vector<vector<State>> board);

string CellString(State &cell);

void PrintBoard(vector<vector<State>> board);

#endif