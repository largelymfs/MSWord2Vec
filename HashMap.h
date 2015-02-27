#ifndef HASHMAP_H
#define HASHMAP_H
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Hash Table Node
struct Node{
	long long cnt, index;
	char* word;
	Node():cnt(0),word(NULL){}
	~Node(){
		if (word!=NULL) delete word;
	}

	void setWord(char* w, int cnt);
	void setWord(const char* w, int cnt);
};

//Hash Table
class HashMap{
public:
	HashMap();
	~HashMap();
	void addWord( char* word, int cnt);						// add a word into the table
	void addWord(const char* word, int cnt);				
	long long Hash( char* word);							// calculate hash
	long long Hash(const char* word);
	long long searchWord( char* word);						// search the position of a word
	long long searchWordIndex( char* word);					// search the index of a word
	void show();											// print it out
	void reduce_vocab(int min_count);						// reduce all the words appears only little times
	long long size();										// word number in the table
	long long searchWordCnt(int index);						// search the counts of a word
	long long totalWords();									// the total word times in the dataset
	std::string& searchWordContent(int index);				// search the word of an index
private:
	long long total_words;
	Node* content;
	int hash_size;
	long long word_number;
	std::vector<std::string> strlist;
	std::vector<int> cntlist;
};
#endif
