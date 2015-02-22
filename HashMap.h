#ifndef HASHMAP_H
#define HASHMAP_H
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

class HashMap{
public:
	HashMap();
	~HashMap();
	void addWord( char* word, int cnt);
	void addWord(const char* word, int cnt);
	long long Hash( char* word);
	long long Hash(const char* word);
	long long searchWord( char* word);
	long long searchWordIndex( char* word);
	void show();
	void reduce_vocab(int min_count);
	long long size();
	long long searchWordCnt(int index);
	std::string& searchWordContent(int index);
private:
	Node* content;
	int hash_size;
	long long word_number;
	std::vector<std::string> strlist;
	std::vector<int> cntlist;
};
#endif
