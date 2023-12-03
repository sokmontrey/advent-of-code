#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <ranges>

//test: 8
//input: 2593

using namespace std;

vector<string> split(const string& input, const string& delimiter) {
    vector<string> result;
    size_t start = 0;
    size_t end = input.find(delimiter);
    while (end != string::npos) {
        result.push_back(input.substr(start, end - start));
        start = end + delimiter.length();
        end = input.find(delimiter, start);
    }
    if (start != input.length()) result.push_back(input.substr(start, end));
    return result;
}

string getInput(string filename) {
    ifstream file(filename);
    stringstream str;
    str << file.rdbuf();
    return str.str();
}

int code(string input){
    map<string, int> bag{
        {"red", 12},
        {"green", 13},
        {"blue", 14}
    };

    auto games = split(input, "\n");
    transform(games.cbegin(), games.cend(), games.begin(), [](const auto& game){
        return split(game, ": ")[1];
    });

    auto valid = views::iota(1, static_cast<int>(games.size()+1))
        | views::filter([&games, &bag](const auto& i){ 
            auto game = games[i-1];
            auto sets = split(game, "; ");
            return all_of(sets.begin(), sets.end(), [&bag](const auto& set){
                auto cubes = split(set, ", ");
                return all_of(cubes.begin(), cubes.end(), [&bag](const auto& cube){
                    auto pick = split(cube, " ");
                    return bag[pick[1]] >= stoi(pick[0]);
                });
            });
        });
    return accumulate(valid.begin(), valid.end(), 0);
}

int main (int argc, char* argv[]) {
    string file_name = (argc>1 && strcmp(argv[1],"i")==0) ? "input.txt" : "test.txt";
    string input = getInput(file_name);
    cout << "Result: " << code(input) << endl;
    return 0;
}
