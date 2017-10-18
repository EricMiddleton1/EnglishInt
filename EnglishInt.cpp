#include <string>
#include <cmath>
#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace std::string_literals;

string toEnglish(string);
string toEnglishRec(string);
int getCharValue(char);
void trimLeadingZeros(string&);

string toEnglish(string i) {
	bool negative = false;

	if(i.length() == 0) {
		throw runtime_error("[Error] Empty string"s);
	}

	if(i[0] == '-') {
		i = i.erase(0, 1);
		negative = true;
	}
	if(i == "0") {
		return "zero"s;
	}

	trimLeadingZeros(i);

	if(i.length() == 0) {
		throw runtime_error("[Error] Too many zeros"s);
	}

	auto english = toEnglishRec(i);

	return (negative) ? "negative "s + english : english;
}

string toEnglishRec(string i) {
	const string decimalTable[] = {
		"one"s,
		"two"s,
		"three"s,
		"four"s,
		"five"s,
		"six"s,
		"seven"s,
		"eight"s,
		"nine"s,
		"ay"s,
		"bee"s,
		"cee"s,
		"dee"s,
		"ee"s,
		"ef"s
	};
	const string teenTable[] = {
		"ten"s,
		"eleven"s,
		"twelve"s,
		"thirteen"s,
		"fourteen"s,
		"fifteen"s,
		"sixteen"s,
		"seventeen"s,
		"eighteen"s,
		"nineteen"s,
		"aylevin"s,
		"belve"s,
		"cirteen"s,
		"dorteen"s,
		"eefteen"s,
		"fixteen"s
	};
	const string tensTable[] {
		"twenty"s,
		"thirty"s,
		"forty"s,
		"fifty"s,
		"sixty"s,
		"seventy"s,
		"eighty"s,
		"ninety"s,
		"aety"s,
		"bety"s,
		"cety"s,
		"dety"s,
		"eety"s,
		"fety"s
	};
	const string levelTable[19] {
		"thousand"s,
		"million"s,
		"billion"s,
		"trillion"s,
		"quadrillion"s,
		"quintillion"s,
		"sextillion"s,
		"octillion"s,
		"nonillion"s,
		"decillion"s,
		"undecillion"s,
		"duodecillion"s,
		"tredecillion"s,
		"quattuordecillion"s,
		"sexdecillion"s,
		"septendecillion"s,
		"octodecillion"s,
		"novemdecillion"s,
		"vigintillion"s,
	};

	if(i.length() == 0) {
		return "";
	}
	else if(i.length() >= (3*20 + 1)) {
		throw runtime_error("[Error] Number too large"s);
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
			curStr = tensTable[curDigit - 2];
		}

	}
	else if(subDigit == 2) {
		curStr = decimalTable[curDigit - 1] + " hundred"s;
	}

	trimLeadingZeros(i);

	if((( (i.length() % 3) == 0) || subDigit == 0) && level > 0) {
		curStr += " "s + levelTable[level-1];
	}

	return curStr + " "s + toEnglishRec(i);
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

	throw runtime_error("[Error] Invalid character: "s + c);
}

void trimLeadingZeros(string& str) {
	int zeroCount;

	for(zeroCount = 0; (zeroCount < str.length()) && (str[zeroCount] == '0'); ++zeroCount);

	if(zeroCount > 0) {
		str.erase(0, zeroCount);
	}
}

int main(int argc, char **argv) {
	long input;
	
	if(argc != 2) {
		cout << "Usage: "s << argv[0] << " number"s << endl;

		return 1;
	}

	try {
		cout << toEnglish(argv[1]) << endl;
	}
	catch(const exception& e) {
		return 1;
	}

	return 0;
}
