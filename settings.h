#pragma once

#include <map>
#include <list>
#include <string>

using namespace std;

struct Pair {
	Pair(string f = "", string s = "") {
		first = f;
		second = s;
	}
	bool operator==(Pair c) {
		return first == c.first;
	}

	string first;
	string second;
};

void fillOperatots(map<string, string>& op) {
	op["<"] = "O1";
	op[">"] = "O2";
	op["="] = "O3";
	op[":="] = "O4";
	op[";"] = "O5";
}

void fillKeyWords(map<string, string>& kw) {
	kw["if"] = "K1";
	kw["else"] = "K2";
	kw["then"] = "K3";
}


void fillRomanNumbers(map<string, string>& kw) {
	kw["regex"] = "^M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$";
	kw["value"] = "R";
}


void fillMembers(map<string, map<string, string>>& m) {
	map<string, string> operators;
	fillOperatots(operators);
	m["Operator"] = operators;
	map<string, string> keyWords;
	fillKeyWords(keyWords);
	m["Key word"] = keyWords;
	map<string, string> comms;

}


bool find(list<Pair> l, string c) {
	for (auto it = l.begin(); it != l.end(); it++) {
		if (it->first == c) {
			return true;
		}
	}
	return false;
}

void fillResults(map<string, list<Pair>>& m) {
	list<Pair> l1;
	m["Operator"] = l1;

	list<Pair> l2;
	m["Key word"] = l2;

	list<Pair> l3;
	m["Comment"] = l3;

	list<Pair> l4;
	m["Roman number"] = l4;

	list<Pair> l5;
	m["Invalid identifier"] = l5;
	
	list<Pair> l6;
	m["Identifier"] = l6;
}



