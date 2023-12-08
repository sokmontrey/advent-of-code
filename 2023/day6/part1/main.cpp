#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

// test : 352
// input: 741000

#define ll long long int

using namespace std;

template <typename K, typename V> class IntervalMap {
public:
  void insert(K a, K b, V value) { m.insert({a, {b, value}}); }

  V find(K key) const {
    auto it = m.upper_bound(key);
    if (it == m.begin()) {
      return 0;
    }
    --it;
    if (key > it->second.first) {
      return 0;
    }
    return it->second.second;
  }

  int size() const { return m.size(); }

private:
  map<K, std::pair<K, V>> m;
};

vector<string> split(const string &input, const string &delimiter) {
  vector<string> result;
  size_t start = 0;
  size_t end = input.find(delimiter);
  while (end != string::npos) {
    string substr = input.substr(start, end - start);
    if (substr.size() > 0)
      result.push_back(substr);
    start = end + delimiter.length();
    end = input.find(delimiter, start);
  }
  if (start != input.size()) {
    string substr = input.substr(start, end);
    if (substr.size() > 0)
      result.push_back(substr);
  }
  return result;
}

template <typename A, typename B>
vector<B> vectorMap(vector<A> &&input, function<B(A)> func) {
  vector<B> result;
  transform(input.cbegin(), input.cend(), back_inserter(result), func);
  return result;
}

template <typename A, typename B>
vector<B> vectorMap(vector<A> &input, function<B(A)> func) {
  vector<B> result;
  transform(input.cbegin(), input.cend(), back_inserter(result), func);
  return result;
}

template <typename A>
void vectorTransform(vector<A> &input, function<A(A)> func) {
  transform(input.cbegin(), input.cend(), input.begin(), func);
}

template <typename A>
void vectorTransform(vector<A> &&input, function<A(A)> func) {
  transform(input.cbegin(), input.cend(), input.begin(), func);
}

template <typename A, typename B>
B vectorReduce(vector<A> &input, B init, function<B(B, A)> func) {
  return accumulate(input.cbegin(), input.cend(), init, func);
}

string getInput(string filename) {
  ifstream file(filename);
  stringstream str;
  str << file.rdbuf();
  return str.str();
}

bool isDigit(char c) { return isdigit(c); }

ll toLongLong(string input) { return stoll(input); }

template <typename A> A *quadraticRoots(A a, A b, A c) {
  static A result[2];
  A d = b * b - 4 * a * c;
  if (d < 0) {
    return nullptr;
  }
  A x1 = (-b + sqrt(d)) / (2 * a);
  A x2 = (-b - sqrt(d)) / (2 * a);
  result[0] = x1;
  result[1] = x2;
  return result;
}

int code(string input) {
  vector<string> lines = split(input, "\n");
  auto times =
      vectorMap<string, ll>(split(split(lines[0], ": ")[1], " "), toLongLong);
  auto distance =
      vectorMap<string, ll>(split(split(lines[1], ": ")[1], " "), toLongLong);

  ll result = 1;
  for (int i = 0; i < times.size(); i++) {
    auto root = quadraticRoots<double>(-1, times[i], -distance[i]);
    double x1 = ceil(root[0]);
    double x2 = floor(root[1]);
    result *= x2 - x1 + 1;
  }

  return result;
}

int main(int argc, char *argv[]) {
  string file_name =
      (argc > 1 && strcmp(argv[1], "i") == 0) ? "input.txt" : "test.txt";
  string input = getInput(file_name);
  int result = code(input);
  cout << "Result: " << result << endl;
  return 0;
}
