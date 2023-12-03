#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <numeric>
#include <map>

//test: 281
//input: 38834

using namespace std;

vector<string> split(string s, string d){
    vector<string> result;
    size_t pos = 0;
    while ((pos = s.find(d)) != string::npos) {
        result.push_back(s.substr(0, pos));
        s.erase(0, pos + d.length());
    }
    return result;
}
string getInput(string filename) {
    std::ifstream file(filename);
    std::stringstream str;
    str << file.rdbuf();
    return str.str();
}
string replace(string input, string search, string replace){
    size_t pos = 0;
    while((pos = input.find(search, pos)) != string::npos){
        input.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return input;
}

map<string, string> digits{
    {"zero", "0"},
    {"one", "1"},
    {"two", "2"},
    {"three", "3"},
    {"four", "4"},
    {"five", "5"},
    {"six", "6"},
    {"seven", "7"},
    {"eight", "8"},
    {"nine", "9"}
};
string replaceFirstDigit(string s){
    size_t pos = -1;
    string c = "";
    for (auto& [word, digit] : digits){
        size_t p = s.find(word);
        if (p != string::npos && p < pos){
            pos = p;
            c = digit;
        }
    }
    if (pos == string::npos) return s;
    return s.substr(0, pos) + c + s.substr(pos + c.length());
}
string replaceLastDigit(string s){
    int pos = -1;
    string c = "";
    for (auto& [word, digit] : digits){
        int p = s.rfind(word);
        if (p != string::npos && p > pos){
            pos = p;
            c = digit;
        }
    }
    if (pos < 0) return s;
    return s.substr(0, pos) + c + s.substr(pos + c.length());
}

int code(string input){
    vector<string> cals = split(input, "\n");

    return accumulate(cals.begin(), cals.end(), 0, [](int total, auto& cal){
        cal = replaceFirstDigit(cal);
        cal = replaceLastDigit(cal);
        int i, j;
        for (i=0; i<cal.size(); i++) if (cal[i] >= '0' && cal[i] <= '9') break;
        for (j=cal.size()-1; j>=0; j--) if (cal[j] >= '0' && cal[j] <= '9') break;
        return total + stoi(string{cal[i], cal[j]});
    });
}

int main (int argc, char* argv[]) {
    string file_name = (argc>1 && strcmp(argv[1],"i")==0) ? "input.txt" : "test.txt";
    string input = getInput(file_name);
    cout << code(input) << endl;
    return 0;
}
