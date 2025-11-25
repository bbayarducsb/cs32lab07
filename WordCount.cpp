// WordCount.cpp

#include "WordCount.h"
#include <set>
#include <functional>

using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int numWords = 0; 
	for(auto bucket : table) {
		for(auto pair : bucket) {
			numWords += pair.second; 
		}
	}
	return numWords;
}

int WordCount::getNumUniqueWords() const {
	int numUniqueWords = 0; 
	for(auto bucket : table) {
		for(auto pair : bucket) {
			numUniqueWords++; 
		}
	}
	return numUniqueWords;
}

int WordCount::getWordCount(std::string word) const {

	word = makeValidWord(word); 
	
	int index = hash(word); 

	const std::vector<std::pair<std::string, int> >& bucket = table[index];
	for(auto &pair : bucket) {
		if(pair.first == word) {
			return pair.second; 
		}
	}
	return 0;
}
	
int WordCount::incrWordCount(std::string word) {
	//check if valid word
	word = makeValidWord(word); 

	if(word == "") {
		return 0; 
	}

	//get index of word
	int index = hash(word); 
	
	//check at that index for word 
	std::vector<std::pair<std::string, int> >& bucket = table[index];
	bool found = false; 
	int currentAmount = 0; 
	for(auto &pair : bucket) {
		if(pair.first == word) {
			pair.second++; 
			found = true; 
			currentAmount = pair.second; 
		}
	}
	if(!found) {
		std::pair<std::string, int> newPair = {word, 1};
		bucket.push_back(newPair); 
		currentAmount = 1; 
	}

	return currentAmount; 
}

int WordCount::decrWordCount(std::string word) {

	word = makeValidWord(word); 

	if(word == "") {
		return -1; 
	}
		//get index of word
	int index = hash(word); 
	
	//check at that index for word 
	std::vector<std::pair<std::string, int> >& bucket = table[index];
	int foundIndex = -1; 
	for(int i = 0; i < (int) bucket.size(); i++) {
		auto &pair = bucket[i]; 
		if(pair.first == word) {
			pair.second--; 
			foundIndex = i; 
		}
	}
	if(foundIndex == -1) {return -1;}
	if(bucket[foundIndex].second < 1) {
		bucket.erase(bucket.begin() + foundIndex); 
		return 0; 
	}
	return bucket[foundIndex].second; 
}

bool WordCount::isWordChar(char c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'); 
}

std::string WordCount::makeValidWord(std::string word) {
	std::string newWord = ""; 

	for(auto &c : word) {
		if(c >= 'A' && c <= 'Z') {
			c = c + ('a' - 'A'); 
		}
	}
	bool foundFirstAlpha = false; 
	int indexOfLastAlpha; 
	for(int i = 0; i < (int) word.size(); i++) 
	{
		if(foundFirstAlpha && (isWordChar(word[i]) || word[i] == '-' || word[i] == '\'')) {
			newWord += word[i]; 
		}
		if(!foundFirstAlpha && isWordChar(word[i])) {
			newWord += word[i]; 
			foundFirstAlpha = true;
		}
		if(isWordChar(word[i])) {
			indexOfLastAlpha = newWord.size(); 
		}
	}
	newWord = newWord.substr(0, indexOfLastAlpha); 
	return newWord; 
}


void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	std::set<pair<string, int>, std::greater<>> allWords; 
	for(auto bucket : table) {
		for(auto pair : bucket) {
			allWords.insert(pair);
		}
	}
	for(auto pair : allWords) {
		out << pair.first << "," << pair.second << endl; 
	}

}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	std::set<pair<int, string>> allWords; 
	for(auto bucket : table) {
		for(auto pair : bucket) {
			allWords.insert({pair.second, pair.first});
		}
	}
	for(auto pair : allWords) {
		out << pair.second << "," << pair.first << endl; 
	}
	
}

void WordCount::addAllWords(std::string text) {
	text += " "; 
	int start = 0; 
	int end; 
	for(int i = 0; i < text.size(); i++) {
		if(text[i] == ' ' || text[i] == '\n' || text[i] == '\t') {
			end = i; 
			incrWordCount(text.substr(start, end - start)); 
			start = end; 
		}
	}
	return;
}
