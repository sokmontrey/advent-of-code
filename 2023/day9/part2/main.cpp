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

// test : 2
// input: 889

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

ll getNextTerm(vector<ll> seq) {
  vector<ll> diffs(seq.size() - 1);
  bool is_zero = true;
  for (int i = 1; i < seq.size(); i++) {
    ll num = seq[i] - seq[i - 1];
    if (num != 0)
      is_zero = false;
    diffs[i - 1] = num;
  }
  return is_zero ? seq.back() : getNextTerm(diffs) + seq.back();
}

ll code(string input) {
  auto lines = split(input, "\n");
  auto seqs = vectorMap<string, vector<ll>>(lines, [](string line) {
    auto term = vectorMap<string, ll>(split(line, " "), toLongLong);
    reverse(term.begin(), term.end());
    return term;
  });
  return vectorReduce<vector<ll>, ll>(
      seqs, 0, [](ll acc, vector<ll> seq) { return getNextTerm(seq) + acc; });
}

int main(int argc, char *argv[]) {
  string file_name =
      (argc > 1 && strcmp(argv[1], "i") == 0) ? "input.txt" : "test.txt";
  string input = getInput(file_name);
  ll result = code(input);
  cout << "Result: " << result << endl;
  return 0;
}
