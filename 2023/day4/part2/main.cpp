#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
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
  vector<int> v(lines.size(), 1);

  for (int i = 0; i < lines.size(); i++) {
    auto line = lines[i];
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

    //horible
    int amount = v[i];
    for (int j = i + 1; j <= i + count && j < v.size(); j++) {
      v[j] += v[i];
    }
  }
  return accumulate(v.begin(), v.end(), 0);
}

int main(int argc, char *argv[]) {
  string file_name =
      (argc > 1 && strcmp(argv[1], "i") == 0) ? "input.txt" : "test.txt";
  string input = getInput(file_name);
  int result = code(input);
  cout << "Result: " << result << endl;
  return 0;
}
