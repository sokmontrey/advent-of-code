#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// test: 13
// input: 23235

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

  return accumulate(lines.begin(), lines.end(), 0, [](int sum, string line) {
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
    return sum + pow(2, count - 1);
  });
}

int main(int argc, char *argv[]) {
  string file_name =
      (argc > 1 && strcmp(argv[1], "i") == 0) ? "input.txt" : "test.txt";
  string input = getInput(file_name);
  int result = code(input);
  cout << "Result: " << result << endl;
  return 0;
}
