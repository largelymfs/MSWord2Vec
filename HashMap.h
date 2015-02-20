#ifndef HASHMAP_H
#define HASHMAP_H
#include <vector>
struct Node{
	long long cnt, index;
	char* word;
	Node():cnt(0),word(NULL){}
	~Node(){
		if (word!=NULL) delete word;
	}

	void setWord(const char* w, int cnt);
};

class HashMap{
public:
	HashMap();
	~HashMap();
	void addWord(const char* word, int cnt);
	long long Hash(const char* word);
	long long searchWord(const char* word);
	long long searchWordIndex(const char* word);
	void show();
	void reduce_vocab(int min_count);
private:
	Node* content;
	const int hash_size;
	long long word_number;
};
#endif