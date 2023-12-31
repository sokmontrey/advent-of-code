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

// test :
// input:

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

int code(string input) {
  auto lines = split(input, ":");
  auto temp_seeds =
      vectorMap<string, ll>(split(split(lines[1], "\n")[0], " "), toLongLong);
  vector<vector<ll>> seeds;
  for (int i = 0; i < temp_seeds.size(); i += 2) {
    seeds.push_back({temp_seeds[i], temp_seeds[i] + temp_seeds[i + 1] - 1});
  }

  auto maps = vectorMap<string, string>(
      vector<string>(lines.begin() + 2, lines.end()),
      [](string each) { return split(each, "\n\n")[0]; });

  for (const auto &map : maps) {
    auto ranges = split(map, "\n");
    for (auto &seed : seeds) {
      for (const auto &range : ranges) {
        auto range_split = vectorMap<string, ll>(split(range, " "), toLongLong);
        ll destination = range_split[0], source = range_split[1],
           shift_amount = destination - source;

        ll lower = source, upper = source + range_split[2] - 1;
        ll seed_lower = seed[0], seed_upper = seed[1];
      }
    }
  }

  return 0;
  // return vectorReduce<ll, ll>(
  //     seeds, LONG_MAX, [](ll final, ll seed) { return min(final, seed); });
}

int main(int argc, char *argv[]) {
  string file_name =
      (argc > 1 && strcmp(argv[1], "i") == 0) ? "input.txt" : "test.txt";
  string input = getInput(file_name);

  int result = code(input);
  cout << "Result: " << result << endl;
  return 0;
}
