#include <string>
#include <cmath>
#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace std;

string toEnglish(string);
string toEnglishRec(string);
int getCharValue(char);

string toEnglish(string i) {
	bool negative = false;

	if(i.length() == 0) {
		throw runtime_error("[Error] Empty string");
	}

	if(i[0] == '-') {
		i = i.erase(0, 1);
		negative = true;
	}
	if(i == "0") {
		return "zero";
	}

	//Trim leading zeros
	while(i[0] == '0') {
		i.erase(0, 1);
	}

	if(i.length() == 0) {
		throw runtime_error("[Error] Too many zeros");
	}

	auto english = toEnglishRec(i);

	return (negative) ? string("negative ") + english : english;
}

string toEnglishRec(string i) {
	const string decimalTable[] = {
		"one",
		"two",
		"three",
		"four",
		"five",
		"six",
		"seven",
		"eight",
		"nine",
		"ay",
		"bee",
		"cee",
		"dee",
		"ee",
		"ef"
	};
	const string teenTable[] = {
		"ten",
		"eleven",
		"twelve",
		"thirteen",
		"fourteen",
		"fifteen",
		"sixteen",
		"seventeen",
		"eighteen",
		"nineteen",
		"aylevin",
		"belve",
		"cirteen",
		"dorteen",
		"eefteen",
		"fixteen"
	};
	const string tensTable[] {
		"ten",
		"twenty",
		"thirty",
		"forty",
		"fifty",
		"sixty",
		"seventy",
		"eighty",
		"ninety",
		"aety",
		"bety",
		"cety",
		"dety",
		"eety",
		"fety"
	};
	const string levelTable[19] {
		"thousand",
		"million",
		"billion",
		"trillion",
		"quadrillion",
		"quintillion",
		"sextillion",
		"octillion",
		"nonillion",
		"decillion",
		"undecillion",
		"duodecillion",
		"tredecillion",
		"quattuordecillion",
		"sexdecillion",
		"septendecillion",
		"octodecillion",
		"novemdecillion",
		"vigintillion",
	};

	if(i.length() == 0) {
		return "";
	}
	else if(i.length() >= (3*19)) {
		throw runtime_error("[Error] Number too large");
	}

	int digits = i.length() - 1,
		subDigit = digits % 3,
		level = digits / 3;
	
	string curStr;
	int curDigit = getCharValue(i[0]);
	i.erase(0, 1);

	if(subDigit == 0) {
		curStr = decimalTable[curDigit - 1];
	}
	else if(subDigit == 1) {
		if(curDigit == 1) {
			int value = getCharValue(i[0]);
			i.erase(0, 1);
			curStr = teenTable[value];
		}
		else {
			curStr = tensTable[curDigit - 1];
		}

	}
	else if(subDigit == 2) {
		curStr = decimalTable[curDigit - 1] + " hundred";
	}

	//Trim leading zeros
	while(i[0] == '0') {
		i.erase(0, 1);
	}

	if((( (i.length() % 3) == 0) || subDigit == 0) && level > 0) {
		curStr += string(" ") + levelTable[level-1];
	}

	return curStr + " " + toEnglishRec(i);
}

int getCharValue(char c) {
	if( (c >= '0') && (c <= '9') ) {
		return c - '0';
	}
	
	if( (c >= 'a') && (c <= 'f') ) {
		c += 'A' - 'a';
	}
	if( (c >= 'A') && (c <= 'F') ) {
		return c - 'A' + 10;
	}

	throw runtime_error(string("[Error] Invalid character: ") + c);
}

int main(int argc, char **argv) {
	long input;
	
	if(argc != 2) {
		cout << "Usage: " << argv[0] << " number" << endl;

		return 1;
	}

	try {
		cout << toEnglish(argv[1]) << endl;
	}
	catch(const exception& e) {
		cerr << e.what() << endl;

		return -1;
	}

	return 0;
}
