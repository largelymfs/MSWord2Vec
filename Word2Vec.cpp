/* 
* @Author: largelyfs
* @Date:   2015-02-21 21:05:25
* @Last Modified by:   largelyfs
* @Last Modified time: 2015-02-21 22:36:49
*/

#include <iostream>

#define MAX_STRING_LENGTH 100

using namespace std;
#include "Word2Vec.h"

Word2Vec::Word2Vec(	const char* filename, int min_count=4, 
					int window=5, int size=100, double alpha=0.25, 
					double min_alpha=0.001, int negative = 5){
	this->v = new VocabGen(filename, MAX_STRING_LENGTH);
	this->min_count = min_count;
	this->window_size = window;
	this->alpha = alpha;
	this->min_alpha = min_alpha;
	this->layer1_size = size;
	this->negative = negative;
	this->v->buildVocab();
	this->v->reduceVocab(this->min_count);
	this->resetWeights();
	std::cout << this->v->size() << std::endl;
}

Word2Vec::~Word2Vec(){
	if (v!=NULL) delete v; 
}

void Word2Vec::resetWeights(){
	this->globalembeddings.clear();
	this->senseembeddings.clear();
	this->clusterembeddings.clear();
}
int main(){
	Word2Vec *w = new Word2Vec("test.txt",0);
	delete w;
    return 0;
}