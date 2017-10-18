#include <string>
#include <cmath>
#include <sstream>
#include <iostream>

using namespace std;

string toEnglishRec(long);

string toEnglish(long i) {
	bool negative = false;

	if(i == 0) {
		return "zero";
	}
	else if(i < 0) {
		i *= -1;
		negative = true;
	}

	auto english = toEnglishRec(i);

	return (negative) ? string("negative ") + english : english;
}

int getDigitCount(long i) {
	if(i == 0) {
		return 1;
	}
	else {
		return log10(i) + 1.;
	}
}

int getDigit(long i, int digit) {
	int divisor;

	for(divisor = 1; digit > 1; --digit) {
		divisor *= 10;
	}

	return i / divisor;
}

int removeDigit(long& val) {
	int count = getDigitCount(val);
	int divisor = 1;

	for(int i = 1; i < count; ++i) {
		divisor *= 10;
	}

	int removed = val / divisor;
	val %= divisor;

	return removed;
}


string toEnglishRec(long i) {
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

	if(i == 0) {
		return "";
	}

	int digits = getDigitCount(i) - 1,
		subDigit = digits % 3,
		level = digits / 3;
	
	string curStr;

	if(subDigit == 0) {
		int curDigit = removeDigit(i);
		
		curStr = decimalTable[curDigit - 1];

		if(level > 0) {
			//curStr += string(" ") + levelTable[level-1];
		}
	}
	else if(subDigit == 1) {
		int curDigit = removeDigit(i);

		if(curDigit == 1) {
			curDigit = 10*curDigit + removeDigit(i);
			curStr = teenTable[curDigit - 10];

			if(level > 0) {
				//curStr += string(" ") + levelTable[level-1];
			}
		}
		else {
			curStr = tensTable[curDigit - 1];
		}

	}
	else if(subDigit == 2) {
		int curDigit = removeDigit(i);

		curStr = decimalTable[curDigit - 1] + " hundred";
	}
	

	if(((getDigitCount(i) != digits) || subDigit == 0) && level > 0) {
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

	stringstream ss(argv[1]);

	ss >> input;

	cout << toEnglish(input) << endl;

	return 0;
}
