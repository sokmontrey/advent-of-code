#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <numeric>

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
int code(string input){
    vector<string> cals = split(input, "\n");
    return accumulate(cals.begin(), cals.end(), 0, [](int total, auto& cal){
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
