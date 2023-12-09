#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

// test : 6
// input: 14299763833181

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

template <typename T> T vectorLCM(vector<T> &&input) {
  T result = input[0];
  for (int i = 1; i < input.size(); i++) {
    result = (result * input[i]) / __gcd(result, input[i]);
  }
  return result;
}

ll code(string input) {
  auto lines = split(input, "\n");
  auto instr = lines[0];
  map<string, pair<string, string>> m;
  vector<string> nodes;

  for (const auto &m_line : vector<string>(lines.begin() + 1, lines.end())) {
    string key = m_line.substr(0, 3);
    string left = m_line.substr(7, 3);
    string right = m_line.substr(12, 3);
    m.insert({key, {left, right}});
    if (key[2] == 'A') {
      nodes.push_back(key);
    }
  }

  return vectorLCM<ll>(vectorMap<string, ll>(nodes, [&instr, &m](string node) {
    ll count = 0;
    for (int i = 0; node[2] != 'Z'; i = i >= instr.size() - 1 ? 0 : i + 1) {
      node = instr[i] == 'L' ? m[node].first : m[node].second;
      count++;
    }
    return count;
  }));
}

int main(int argc, char *argv[]) {
  string file_name =
      (argc > 1 && strcmp(argv[1], "i") == 0) ? "input.txt" : "test.txt";
  string input = getInput(file_name);
  ll result = code(input);
  cout << "Result: " << result << endl;
  return 0;
}
