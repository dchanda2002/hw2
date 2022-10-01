#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
	rawWords = trim(rawWords);
	std::set<string> wordsSet;
	unsigned int currentIndex = 0;
	for(unsigned int i = 0; i < rawWords.size(); ++i){
		if(ispunct(rawWords[i]) || isspace(rawWords[i])){
			int substrLength = i - currentIndex;
			string newWord = rawWords.substr(currentIndex, substrLength);
			if(newWord.size() > 1){
				newWord = convToLower(newWord);
				wordsSet.insert(newWord);
			}
			currentIndex  = i + 1;
		} 
	}

	// The last word needs to be manually added since the string has been trimmed
	
	string finalWord = rawWords.substr(currentIndex);
	finalWord = convToLower(finalWord);
	wordsSet.insert(finalWord);
	return wordsSet;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
