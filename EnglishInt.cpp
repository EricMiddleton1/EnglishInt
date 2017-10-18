#include <string>
#include <cmath>
#include <sstream>
#include <iostream>

using namespace std;

string toEnglish(string);
string toEnglishRec(string);
int getCharValue(char);

string toEnglish(string i) {
	bool negative = false;

	if(i[0] == '-') {
		i = i.erase(0, 1);
		negative = true;
	}
	if(i == "0") {
		return "zero";
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
		"a",
		"b",
		"c",
		"d",
		"e",
		"f"
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
		"a-teen",
		"b-teen",
		"c-teen",
		"d-teen",
		"e-teen",
		"f-teen"
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
		"exty",
		"fety"
	};
	const string levelTable[] {
		"thousand",
		"million",
		"billion",
		"trillion",
		"quadrillion",
		"quintillion"
	};

	if(i.length() == 0) {
		return "";
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

	throw runtime_error("[Error] Invalid character: " + c);
}

int main(int argc, char **argv) {
	long input;
	
	if(argc != 2) {
		cout << "Usage: " << argv[0] << " number" << endl;

		return 1;
	}

	cout << toEnglish(argv[1]) << endl;

	return 0;
}
