#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "a_star_search.h"

using std::cout;
using std::endl;
using std::abs;
using std::string;
using std::vector;

bool CompareNodes(const vector<int> &open_node_1, const vector<int> &open_node_2) {

  int steps_from_start_node_1 = open_node_1[2];
	int steps_from_goal_node_1 = open_node_1[3];
	int steps_from_start_node_2 = open_node_2[2]; 
	int steps_from_goal_node_2 = open_node_2[3];

  return (steps_from_start_node_1 + steps_from_goal_node_1) > (steps_from_start_node_2 + steps_from_goal_node_2);
}


void SortOpenNodes(vector<vector<int>> *open_nodes) {

  sort(open_nodes->begin(), open_nodes->end(), CompareNodes);

  return;
}


void AddToOpenNodes(int x, int y, int steps_from_start, int steps_to_goal, vector<vector<int>> &open_nodes, vector<vector<State>> &board) {

  open_nodes.push_back({x, y, steps_from_start, steps_to_goal});
  board[x][y] = State::Closed;

  return;
}


int CalculateDistance(const int &startX, const int &startY, const int &goalX, const int &goalY) {

  return abs(goalX - startX) + abs(goalY - startY);
}


bool CheckValidCell(int x, int y, vector<vector<State>> &board) {

  bool on_board_x = (x >= 0 && x < board.size());
  bool on_board_y = (y >= 0 && y < board[0].size());

  if (on_board_x && on_board_y) {
    if (board[x][y] == State::Empty || board[x][y] == State::Start || board[x][y] == State::Finish) {

      return true;
    }
  }
  return false;
}


void ExpandNeighbourNodes(const vector<int> &current_node, int start[2], int goal[2], vector<vector<int>> &open_nodes, vector<vector<State>> &board) {

  int steps_from_start = current_node[2];

  for (int i = 0; i < moves.size(); i++) {
    int x = current_node[0] + moves[i][0];
    int y = current_node[1] + moves[i][1];

    if (CheckValidCell(x, y, board)) {
      int new_steps_from_start = steps_from_start + 1;
      int new_steps_to_goal = CalculateDistance(x, y, goal[0], goal[1]);

      AddToOpenNodes(x, y, new_steps_from_start, new_steps_to_goal, open_nodes, board);
    }
  }
}


vector<vector<State>> Search(vector<vector<State>> &board, int start[2], int goal[2]) {

  vector<vector<int>> open_nodes;

  int steps_from_start = 0;
  int steps_to_goal = CalculateDistance(start[0], start[1], goal[0], goal[1]);

  AddToOpenNodes(start[0], start[1], steps_from_start, steps_to_goal, open_nodes, board);

  while (open_nodes.size() > 0) {

    SortOpenNodes(&open_nodes);

    vector<int> current_node = open_nodes.back();
    open_nodes.pop_back();

    int current_node_x = current_node[0];
    int current_node_y = current_node[1];

    board[current_node_x][current_node_y] = State::Path;

    if (current_node_x == goal[0] && current_node_y == goal[1]) {

      board[start[0]][start[1]] = State::Start;
      board[goal[0]][goal[1]] = State::Finish;

      return board;
    }

    ExpandNeighbourNodes(current_node, start, goal, open_nodes, board);
  }

  cout << "No path found!!!" << endl;
  return vector<vector<State>>{};
}