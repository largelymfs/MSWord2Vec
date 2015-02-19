#ifndef HASHMAP_H
#define HASHMAP_H
#include <vector>
struct Node{
	long long cnt, index;
	char* word;
	Node():cnt(0){}
	void setWord(char* w);
};

class HashMap{
public:
	HashMap();
	~HashMap();
	void addWord(char* word);
	long long Hash(char* word);
	long long searchWord(char* word);
	long long searchWordIndex(char* word);
	void show();
private:
	Node* content;
	const int hash_size;
	long long word_number;
};
#endif