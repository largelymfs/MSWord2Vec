/* 
* @Author: largelymfs
* @Date:   2015-02-18 11:15:37
* @Last Modified by:   largelymfs
* @Last Modified time: 2015-02-19 14:59:50
*/

#include <iostream>
#include "HashMap.h"

void Node::setWord(char* word){
	int l = strlen(word);
	this->word = new char[l + 1];
	strcpy(this->word, word);
	this->cnt = 1;
}

HashMap::HashMap(): hash_size(30000007){
	std::cout << this->hash_size << std::endl;
	this->content = new Node[this->hash_size];
	this->word_number = 0;
}
HashMap::~HashMap(){
	//delete all the content's words
	for (int i = 0; i < this->hash_size; i++)
		if (this->content[i].cnt!=0) delete[] this->content[i].word;
	delete[] this->content;
}
long long HashMap::Hash(char* word){
	long long res = 0;
	int l = strlen(word);
	for (int i = 0; i < l; i++)
		res = (res << 8) + word[i];
	res = res % this->hash_size;
	res = (res + this->hash_size) % this->hash_size;
	return res;
}
long long HashMap::searchWord(char *word){
	long long res = this->Hash(word);
	Node tmp;
	while (true){		
		tmp = this->content[res];
		if (tmp.cnt==0) return -1;
		if (strcmp(tmp.word, word)==0) return res;
		res++;
		if (res==this->hash_size) res = 0;
	}
	return -1;
}
long long HashMap::searchWordIndex(char* word){
	long long res = this->searchWord(word);
	return this->content[res].index;
}
void HashMap::addWord(char *word){
	long long res = this->Hash(word);
	Node tmp;
	if (this->word_number >= this->hash_size) return;

	while (true){
		tmp = this->content[res];
		if (tmp.cnt==0){
			this->content[res].setWord(word);
			this->content[res].index = this->word_number;
			this->word_number++;
			return;
		}
		if (strcmp(tmp.word, word)==0){
			this->content[res].cnt++;
			return;
		}
		res++;
		if (res==this->hash_size) res = 0;
	}
}
void HashMap::show(){
	std::cout << "\t\tindex\t\tcount\t\twordindex\t\tword" << std::endl;
	for (int i = 0; i < this->hash_size; i++){
		if (this->content[i].cnt!=0){
			std::cout << "\t\t" << i << "\t\t" << this->content[i].cnt << "\t\t" << this->content[i].index << "\t\t" << this->content[i].word << std::endl;
		}
	}
}


using namespace std;


int main(){
	HashMap *h = new HashMap();
	char s[10]="hellolibo";
	h->addWord(s);
	h->addWord(s);
	h->addWord(s);
	char t[11] = "largelymfs";
	h->addWord(t);
	h->addWord(t);
	h->show();
	delete h;	
    return 0;
}