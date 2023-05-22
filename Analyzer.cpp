#include <iostream>
#include <fstream>
#include "settings.h"
#include <regex>
#include <cctype>

#define max_lenght 16
#define regex_id "[a-z,A-Z]{1}[a-z,A-Z,.,_,-,1-9]*"

using namespace std;

static int romanCounter = 1;
static int idCounter = 1;


map<string, map<string, string>> members;
map<string, list<Pair>> result;
map<string, string> romanNumbers;


bool checkMember(string c) {
    for (auto& map : members)
    {
        auto item = map.second.find(c);
        if (item != map.second.end()) {
            if (!find(result[map.first], c)) {
                result[map.first].push_back(Pair(c, item->second));
            }
            return true;
        }
    }
    return false;
}

bool checkRomanNumber(string c) {
    regex r = regex(romanNumbers["regex"]);
    if (regex_match(c, r) && c != "") {
        if (!find(result["Roman number"], c)) {
            result["Roman number"].push_back(Pair(c, romanNumbers["value"] + std::to_string(romanCounter)));
            romanCounter++;
        }
        c.clear();
        return true;
    }
    return false;
}

void checkIdentifier(string c) {
    if (c.size() > max_lenght) {
        if (!find(result["Invalid identifier"], c)) 
        result["Invalid identifier"].push_back(Pair(c, "Invalid length"));
    }
    else if (!regex_match(c, regex(regex_id))) {
        if (!find(result["Invalid identifier"], c))
        result["Invalid identifier"].push_back(Pair(c, "Invalid name"));
    }
    else {
        if (!find(result["Identifier"], c)) {
            result["Identifier"].push_back(Pair(c, "I" + std::to_string(idCounter)));
            idCounter++;
        }
    }
}

void identify(string c) {
    if (c == "" || c == " " && c == "\n") {
        return;
    }
    if (checkMember(c)) {
        return;
    }
    if (checkRomanNumber(c)) {
        return;
    }
    checkIdentifier(c);
}

void out() {
    for (auto& list : result)
    {
        for (auto it = list.second.begin(); it != list.second.end(); it++) {
            cout << "token: " << it->first << ", type: " << list.first << ", value: " << it->second << endl;
        }
    }
}



int main()
{
    fillMembers(members);
    fillResults(result);
    fillRomanNumbers(romanNumbers);
    string line;
    ifstream in("input.txt");
    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            string c;
            for (int i = 0; i < line.size(); i++) {
                c += line[i];
                string checkOperator(1, line[i]);
                if (line[i] == ' ') {
                    c.pop_back();
                }
                if ((line[i] == ' ' || i == line.size() - 1) && c != "") {
                    identify(c);
                    c.clear();
                    continue;
                }
                else if (c.find(":=") != std::string::npos) {
                    if (!find(result["Operator"], c))
                        result["Operator"].push_back(Pair(":=", members["Operator"][":="]));
                    c.pop_back();
                    c.pop_back();
                    identify(c);
                    c.clear();
                    continue;
                }
                else if (members["Operator"].find(checkOperator) != members["Operator"].end()) {
                    if (!find(result["Operator"], c))
                        result["Operator"].push_back(Pair(checkOperator, members["Operator"][checkOperator]));
                    c.pop_back();
                    identify(c);
                    c.clear();
                    continue;
                }
                if (c.find("//") != std::string::npos) {
                    c.pop_back();
                    c.pop_back();
                    identify(c);
                    break;
                }

            }
        }
    }
    out();
    in.close();
    return 0;
}

