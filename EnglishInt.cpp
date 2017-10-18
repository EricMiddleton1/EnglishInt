#include <string>
#include <cmath>
#include <sstream>
#include <iostream>

using namespace std;

string toEnglishRec(string);

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
		"nine"
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
		"nineteen"
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
		"ninety"
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
	int curDigit = i[0] - '0';
	i.erase(0, 1);

	if(subDigit == 0) {
		curStr = decimalTable[curDigit - 1];
	}
	else if(subDigit == 1) {
		if(curDigit == 1) {
			curDigit = 10*curDigit + (i[0] - '0');
			curStr = teenTable[curDigit - 10];

			i.erase(0, 1);
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

int main(int argc, char **argv) {
	long input;
	
	if(argc != 2) {
		cout << "Usage: " << argv[0] << " number" << endl;

		return 1;
	}

	cout << toEnglish(argv[1]) << endl;

	return 0;
}
