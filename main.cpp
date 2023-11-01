#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::abs;
using std::ws;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

enum class State {Empty, Obstacle, Path, Closed, Start, Finish};

const vector<vector<int>> moves = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

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


int CalculateDistanceToGoal(const int &startX, const int &startY, const int &goalX, const int &goalY) {

  return abs(goalX - startX) + abs(goalY - startY);
}


bool CheckValidCell(int x, int y, vector<vector<State>> &board) {

  bool on_board_x = (x >= 0 && x < board.size());
  bool on_board_y = (y >= 0 && y < board[0].size());

  if(on_board_x && on_board_y) {
    return board[x][y] == State::Empty;
  }
  return false;
}


void ExpandNeighbourNodes(const vector<int> &current_node, int goal[2], vector<vector<int>> &open_nodes, vector<vector<State>> &board) {

  int steps_from_start = current_node[3];

  for(int i = 0; i < moves.size(); i++) {
    int x = current_node[0] + moves[i][0];
    int y = current_node[1] + moves[i][1];

    if(CheckValidCell(x, y, board)) {
      int new_steps_from_start = steps_from_start + 1;
      int new_steps_to_goal = CalculateDistanceToGoal(x, y, goal[0], goal[1]);

      AddToOpenNodes(x, y, new_steps_from_start, new_steps_to_goal, open_nodes, board);
    }
  }
}


vector<vector<State>> Search(vector<vector<State>> &board, int start[2], int goal[2]) {

  vector<vector<int>> open_nodes;

  int steps_from_start = 0;
  int steps_to_goal = CalculateDistanceToGoal(start[0], start[1], goal[0], goal[1]);

  AddToOpenNodes(start[0], start[1], steps_from_start, steps_to_goal, open_nodes, board);

  while(open_nodes.size() > 0) {

    SortOpenNodes(&open_nodes);

    vector<int> current_node = open_nodes.back();
    open_nodes.pop_back();

    int current_node_x = current_node[0];
    int current_node_y = current_node[1];
    board[current_node_x][current_node_y] = State::Path;

    if(current_node_x == goal[0] && current_node_y == goal[1]) {
      board[start[0]][start[1]] = State::Start;
      board[goal[0]][goal[1]] = State::Finish;

      return board;
    }

    ExpandNeighbourNodes(current_node, goal, open_nodes, board);
  }

  cout << "No path found!!!" << endl;
  return vector<vector<State>>{};
}


vector<State> ParseLine(string &line) {

  istringstream line_stream(line);

  int value;
  char extra_character;
  vector<State> board_row;

  while (line_stream >> value) {
    value ? board_row.push_back(State::Obstacle) : board_row.push_back(State::Empty);
    (line_stream.peek() == ' ') ? line_stream >> ws : line_stream >> extra_character;
  }

  return board_row;
}


vector<vector<State>> ReadBoard(string &file_path) {

  ifstream file_stream(file_path);

  vector<vector<State>> board;

  if (file_stream) {
    string line;
    while (getline(file_stream, line)) {
      vector<State> board_row = ParseLine(line);
      board.push_back(board_row);
    }
  }
  else {
    cout << "File stream error!!!";
  }

  return board;
}


string CellString(State &cell) {

  switch (cell) {
    case State::Start : return "🚦 ";
    case State::Finish : return "🏁 ";
    case State::Obstacle : return "⛰️ ";
    case State::Path : return "🚗 ";
    default : return " 0 ";
  }
}


void PrintBoard(vector<vector<State>> board) {

  for(vector<State> board_row : board) {
    for(State cell : board_row) {
      cout << CellString(cell) << " ";
    }
    cout << endl;
  }

  return;
}


int main() {

  string board_location = "1.board";
  int start[2] = {0, 0};
  int goal[2] = {4, 5};

  vector<vector<State>> board = ReadBoard(board_location);
  vector<vector<State>> solution = Search(board, start, goal);
  PrintBoard(solution);

  return 0;
}
