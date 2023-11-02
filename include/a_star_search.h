#ifndef A_STAR_SEARCH
#define A_STAR_SEARCH

#include <vector>
#include <string>

using std::vector;
using std::string;

enum class State {Empty, Obstacle, Path, Closed, Start, Finish};

const vector<vector<int>> moves = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

bool CompareNodes(const vector<int> &open_node_1, const vector<int> &open_node_2);

void SortOpenNodes(vector<vector<int>> *open_nodes);

void AddToOpenNodes(int x, int y, int steps_from_start, int steps_to_goal, vector<vector<int>> &open_nodes, vector<vector<State>> &board);

int CalculateDistance(const int &startX, const int &startY, const int &goalX, const int &goalY);

bool CheckValidCell(int x, int y, vector<vector<State>> &board);

void ExpandNeighbourNodes(const vector<int> &current_node, int start[2], int goal[2], vector<vector<int>> &open_nodes, vector<vector<State>> &board);

vector<vector<State>> Search(vector<vector<State>> &board, int start[2], int goal[2]);

#endif