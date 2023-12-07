#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// test: 30
// input: 5920640

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

bool isDigit(char c) { return isdigit(c); }

int code(string input) {
  vector<string> lines = split(input, "\n");
  vector<int> copies(lines.size(), 1);

  for (int i = 0; i < lines.size(); i++) {
    auto line = lines[i];
    auto splited = split(line, " | ");

    auto winning_numbers = split(split(splited[0], ": ")[1], " ");
    auto my_numbers = split(splited[1], " ");

    set<string> winning_set;
    for (const auto &number : winning_numbers) {
      if (!number.empty()) {
        winning_set.insert(number);
      }
    }

    int count = 0;
    for (const auto &number : my_numbers) {
      if (!number.empty() && winning_set.count(number) > 0) {
        count++;
      }
    }

    int amount = copies[i];
    for (int j = i + 1; j <= i + count && j < copies.size(); j++) {
      copies[j] += copies[i];
    }
  }
  return accumulate(copies.begin(), copies.end(), 0);
}

int main(int argc, char *argv[]) {
  string file_name =
      (argc > 1 && strcmp(argv[1], "i") == 0) ? "input.txt" : "test.txt";
  string input = getInput(file_name);
  int result = code(input);
  cout << "Result: " << result << endl;
  return 0;
}
