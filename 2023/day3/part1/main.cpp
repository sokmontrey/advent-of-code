#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//test: 4361
//input: 528799

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

bool isSpecial(vector<string> &lines, int row, int col) {
  if (row < 0 || col < 0)
    return false;
  if (row >= lines.size() || col >= lines[row].size())
    return false;
  return !isdigit(lines[row][col]) && lines[row][col] != '.';
}

bool isDigit(char c) { return c >= '0' && c <= '9'; }

int code(string input) {
  vector<string> lines = split(input, "\n");

  int sum = 0;
  for (int row = 0; row < lines.size(); row++) {
    bool last = false;
    bool valid = false;
    string number = "";

    for (int col = 0; col < lines[row].size(); col++) {
      bool current = isSpecial(lines, row, col) ||
                     isSpecial(lines, row - 1, col) ||
                     isSpecial(lines, row + 1, col);

      if (isDigit(lines[row][col])) {
        valid = last || current || valid;
        number += lines[row][col];
      } else if (number != "") {
        valid = current || valid;
        sum += valid ? stoi(number) : 0;
        number = "";
        valid = false;
      }
      last = current;
    }
    sum += (number != "" && valid) ? stoi(number) : 0;
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
