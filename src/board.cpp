#include "board.h"

vector<State> ParseLine(string &line) {

  istringstream line_stream(line);

  int value;
  char extra_character;
  vector<State> board_row;

  while (line_stream >> value) {
    switch (value)
    {
      case -1 : board_row.push_back(State::Obstacle);
        break;
      case 0 : board_row.push_back(State::Empty);
        break;
      case 1 : board_row.push_back(State::Start);
        break;
      case 100 : board_row.push_back(State::Finish);
        break;
    }
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


vector<int> FindStartAndFinish(vector<vector<State>> board) {

  vector<int> start_and_finish(4);

  for (int i=0; i < board.size(); i++) {
    for (int j=0; j < board[0].size(); j++) {

      if (board[i][j] == State::Start) {

        start_and_finish[0] = i;
        start_and_finish[1] = j;
      }
      else if (board[i][j] == State::Finish) {

        start_and_finish[2] = i;
        start_and_finish[3] = j;
      }
    }
  }

  return start_and_finish;
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
