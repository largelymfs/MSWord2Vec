#ifndef VOCABGEN_H
#define VOCABGEN_H


#include "HashMap.h"
#include "FileReader.h"
#include "stdio.h"

class VocabGen{
public:
	VocabGen(const char* filename, int max_string);
	void buildVocab();
	void reduceVocab(int min_count);
	long long searchWord(char* word);
	std::string& searchWordContent(int index);
	long long searchWordCnt(int index);
	long long fileSize();
	long long totalWords();
	~VocabGen();
	long long size();
private:
	FileReader *f;
	HashMap *h;
	const int MAX_STRING;
};


#endif