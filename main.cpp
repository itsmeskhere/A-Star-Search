#include <iostream>
#include <string>
#include <vector>

#include "board.h"
#include "a_star_search.h"

using std::string;
using std::vector;

int main() {

  string board_location = "/home/itsmesk/Code/C++/C++ Nanodegree/A-Star-Search/src/1.board";

  vector<vector<State>> board = ReadBoard(board_location);
  vector<int> start_and_finish = FindStartAndFinish(board);

  int start_x = start_and_finish[0];
  int start_y = start_and_finish[1];
  int start[2] = {start_x, start_y};

  int finish_x = start_and_finish[2];
  int finish_y = start_and_finish[3];
  int finish[2] = {finish_x, finish_y};

  vector<vector<State>> solution = Search(board, start, finish);
  PrintBoard(solution);

  return 0;
}
