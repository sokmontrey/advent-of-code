#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

//test: 2286
//input: 54699

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
        {"red", 0},
        {"green", 0},
        {"blue", 0}
    };

    auto games = split(input, "\n");
    transform(games.cbegin(), games.cend(), games.begin(), [](const auto& game){
        return split(game, ": ")[1];
    });

    return accumulate(games.begin(), games.end(), 0, [&bag](const auto& sum, const auto& game){
        bag["red"] = 0;
        bag["green"] = 0;
        bag["blue"] = 0;

        auto sets = split(game, "; ");
        for_each(sets.begin(), sets.end(), [&bag](const auto& set){
            auto cubes = split(set, ", ");
            for_each(cubes.begin(), cubes.end(), [&bag](const auto& cube){
                auto pick = split(cube, " ");
                string color = pick[1];
                int count = stoi(pick[0]);
                bag[color] = max(bag[color], count);
            });
        });

        return sum + bag["red"] * bag["green"] * bag["blue"];
    });
}

int main (int argc, char* argv[]) {
    string file_name = (argc>1 && strcmp(argv[1],"i")==0) ? "input.txt" : "test.txt";
    string input = getInput(file_name);
    cout << "Result: " << code(input) << endl;
    return 0;
}
