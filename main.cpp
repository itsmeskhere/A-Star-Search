#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

enum class State {kEmpty, kObstacle};

string CellString(State &cell) {
  switch (cell) {
    case State::kObstacle : return "⛰️ ";
    default : return "0 ";
  }
}

vector<State> ParseLine(string &line) {
  istringstream line_stream(line);
  int value;
  char ch;
  vector<State> board_row;
  while (line_stream >> value >> ch) {
    value ? board_row.push_back(State::kObstacle) : board_row.push_back(State::kEmpty);
  }
  return board_row;
}

vector<vector<State>> ReadBoard(string file_path) {
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
  PrintBoard(ReadBoard("1.board"));
  return 0;
}