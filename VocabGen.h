#ifndef VOCABGEN_H
#define VOCABGEN_H


#include "HashMap.h"
#include "FileReader.h"
#include "stdio.h"

// Vocabulary generator
class VocabGen{
public:
	VocabGen(const char* filename, int max_string);
	void buildVocab();								// Build the vocabulary
	void reduceVocab(int min_count);				// reduce the vocabulary
	long long searchWord(char* word);				// search the word index in the vocabulary
	std::string& searchWordContent(int index);		// search the word content using word index
	long long searchWordCnt(int index);				// search the count using word index
	long long fileSize();							// get the fileSize
	long long totalWords();							// get the total words
	~VocabGen();					
	long long size();								// totally word number in the dataset
private:
	FileReader *f;
	HashMap *h;
	const int MAX_STRING;
};


#endif