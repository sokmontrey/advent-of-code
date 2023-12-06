#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// test: 467835
// input: 84907174

using namespace std;

vector<string> split(const string &input, const string &delimiter) {
  vector<string> result;
  size_t start = 0;
  size_t end = input.find(delimiter);
  while (end != string::npos) {
    result.push_back(input.substr(start, end - start));
    start = end + delimiter.length();
    end = input.find(delimiter, start);
  }
  if (start != input.length())
    result.push_back(input.substr(start, end));
  return result;
}

string getInput(string filename) {
  ifstream file(filename);
  stringstream str;
  str << file.rdbuf();
  return str.str();
}

bool isGear(vector<string> &lines, int row, int col) {
  if (row < 0 || col < 0)
    return false;
  if (row >= lines.size() || col >= lines[row].size())
    return false;
  return lines[row][col] == '*';
}

bool isDigit(char c) { return c >= '0' && c <= '9'; }

bool checkDigit(vector<string> lines, int row, int col) {
  if (row < 0 || col < 0)
    return false;
  if (row >= lines.size() || col >= lines[row].size())
    return false;
  return isDigit(lines[row][col]);
}

vector<int> getNumber(vector<string> lines, int row, int col) {
  if (row < 0 || row >= lines.size())
    return vector<int>{};
  bool is_splited = !checkDigit(lines, row, col);

  string left = "", right = "";
  int i = col;
  while (checkDigit(lines, row, --i))
    left = lines[row][i] + left;
  i = col;
  while (checkDigit(lines, row, ++i))
    right = right + lines[row][i];

  return vector<int>{is_splited ? (left == "" ? 1 : stoi(left))
                                : stoi(left + lines[row][col] + right),
                     is_splited ? (right == "" ? 1 : stoi(right)) : 1};
}

int code(string input) {
  vector<string> lines = split(input, "\n");

  int sum = 0;

  for (int row = 0; row < lines.size(); row++) {
    for (int col = 0; col < lines[row].size(); col++) {
      if (isGear(lines, row, col)) {
        int count = 0;
        for (int i = -1; i <= 1; i++) {
          if (checkDigit(lines, row + i, col))
            count++;
          else
            count += checkDigit(lines, row + i, col - 1) +
                     checkDigit(lines, row + i, col + 1);
        }

        if (count == 2) {
          int temp = 1;
          for (int i = -1; i <= 1; i++) {
            vector<int> top = getNumber(lines, row + i, col);
            temp *= top[0] * top[1];
          }
          sum += temp;
        }
      }
    }
  }

  return sum;
}

int main(int argc, char *argv[]) {
  string file_name =
      (argc > 1 && strcmp(argv[1], "i") == 0) ? "input.txt" : "test.txt";
  string input = getInput(file_name);
  cout << "Result: " << code(input) << endl;
  return 0;
}
