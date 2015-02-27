/* 
* @Author: largelyfs
* @Date:   2015-02-20 21:14:18
* @Last Modified by:   largelyfs
* @Last Modified time: 2015-02-27 12:32:19
*/

#include <iostream>
#include <stdlib.h>
#include "VocabGen.h"

VocabGen::VocabGen(const char* filename, int max_string):h(NULL),f(NULL), MAX_STRING(max_string){
	this->f = new FileReader(filename, this->MAX_STRING, 0);
	this->h = new HashMap();
	this->h->addWord("</s>",1);
}

VocabGen::~VocabGen(){
	if (this->h!=NULL) delete this->h;
	if (this->f!=NULL) delete this->f;
}

void VocabGen::buildVocab(){
	char buf[this->MAX_STRING];
	while (this->f->hasWord()){
		this->f->getWord(buf);
		this->h->addWord(buf, 1);
	}
}

void VocabGen::reduceVocab(int min_count){
	this->h->reduce_vocab(min_count);
}

long long VocabGen::searchWord(char* word){
	return this->h->searchWordIndex(word);
}

long long VocabGen::size(){
	return this->h->size();
}

std::string& VocabGen::searchWordContent(int index){
	return this->h->searchWordContent(index);
}

long long VocabGen::searchWordCnt(int index){
	return this->h->searchWordCnt(index);
}

long long VocabGen::fileSize(){
	return this->f->fileSize();
}
long long VocabGen::totalWords(){
	return this->h->totalWords();
}
using namespace std;

// int main(){
// 	VocabGen *g = new VocabGen("test.txt", 100);
// 	g->buildVocab();
// 	g->reduceVocab(0);
// 	char s[2] = "I";
// 	std::cout << g->searchWord(s) << std::endl;
// 	std::cout << g->size() << std::endl;
// 	delete g;
//     return 0;
// }