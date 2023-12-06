#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
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

    map<string, int> m;
    for_each(winning_numbers.begin(), winning_numbers.end(),
             [&m](string number) {
               if (number != "")
                 m[number] = 0;
             });

    int count = accumulate(
        my_numbers.begin(), my_numbers.end(), 0, [&m](int sum, string number) {
          if (number != "" && m.find(number) != m.end() && m[number] == 0) {
            m[number] = 1;
            sum++;
          }
          return sum;
        });
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
