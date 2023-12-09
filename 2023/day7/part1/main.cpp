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

// test : 6440
// input: 249748283

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

int ord(char c) {
  map<char, int> m{{'A', 12}, {'K', 11}, {'Q', 10}, {'J', 9}, {'T', 8},
                   {'9', 7},  {'8', 6},  {'7', 5},  {'6', 4}, {'5', 3},
                   {'4', 2},  {'3', 1},  {'2', 0}};
  return m[c];
}

bool compareOrd(const string &a, const string &b) {
  for (int i = 0; i < a.size(); i++) {
    if (ord(a[i]) != ord(b[i])) {
      return ord(a[i]) < ord(b[i]);
    }
  }
  return 0;
}

// five of a kind: 6 AAAAA 1
// four of a kind: 5 AAAAB 2
// full house: 4 AAABB 2
// three of a kind: 3 AAABC 3
// two pair: 2 AABBC 3
// one pair: 1 AABCD 4
// high card: 0 ABCDE 5
int cardRank(string card) {
  map<char, int> m;
  for (const auto &c : card) {
    m[c]++;
  }
  if (m.size() == 1) {
    return 6;
  }
  if (m.size() == 2) {
    for (const auto &p : m)
      if (p.second == 4)
        return 5;
    return 4;
  }
  if (m.size() == 3) {
    for (const auto &p : m)
      if (p.second == 3)
        return 3;
    return 2;
  }
  if (m.size() == 4) {
    return 1;
  }
  return 0;
}

ll code(string input) {
  auto lines = split(input, "\n");
  auto hands = vectorMap<string, vector<string>>(
      lines, [](string line) { return split(line, " "); });

  map<string, ll> m;
  vector<vector<string>> rank(7);

  for (const auto &hand : hands) {
    auto cards = hand[0];

    m[cards] = stoll(hand[1]);
    rank[cardRank(cards)].push_back(cards);
  }

  for (auto &r : rank) {
    sort(r.begin(), r.end(),
         [](string &a, string &b) { return compareOrd(a, b); });
  }
  ll count = 1;
  ll sum = 0;
  for (auto &r : rank) {
    for (auto &c : r) {
      sum += m[c] * count++;
    }
  }

  return sum;
}

int main(int argc, char *argv[]) {
  string file_name =
      (argc > 1 && strcmp(argv[1], "i") == 0) ? "input.txt" : "test.txt";
  string input = getInput(file_name);
  ll result = code(input);
  cout << "Result: " << result << endl;
  return 0;
}
