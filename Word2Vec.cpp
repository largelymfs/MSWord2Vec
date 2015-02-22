/* 
* @Author: largelyfs
* @Date:   2015-02-21 21:05:25
* @Last Modified by:   largelyfs
* @Last Modified time: 2015-02-22 15:02:45
*/

#include <iostream>

#define MAX_STRING_LENGTH 100

using namespace std;
#include "Word2Vec.h"

Word2Vec::Word2Vec(	const char* filename, int min_count=4, 
					int window=5, int size=100, double alpha=0.25, 
					double min_alpha=0.001, int negative = 5){
	this->v = new VocabGen(filename, MAX_STRING_LENGTH);
	this->r = new RandomGen();
	this->min_count = min_count;
	this->window_size = window;
	this->alpha = alpha;
	this->min_alpha = min_alpha;
	this->layer1_size = size;
	this->negative = negative;
	this->v->buildVocab();
	this->v->reduceVocab(this->min_count);
	this->word_number = this->v->size();
	this->resetWeights();
}

Word2Vec::~Word2Vec(){
	if (v!=NULL) delete v;
	if (r!=NULL) delete r;
	int l = this->globalembeddings.size();
	for (int i = 0; i < l; i++)
		if (this->globalembeddings[i] != NULL) delete this->globalembeddings[i];
	int li, lj;
	li = this->senseembeddings.size();
	for (int i = 0; i < li; i++){
		lj = this->senseembeddings[i].size();
		for (int j = 0; j < lj; j++) 
			if (this->senseembeddings[i][j] != NULL) delete this->senseembeddings[i][j];
	}
	li = this->clusterembeddings.size();
	for (int i = 0; i < li; i++){
		lj = this->clusterembeddings[i].size();
		for (int j = 0; j < lj; j++)
			if (this->clusterembeddings[i][j] != NULL) delete this->clusterembeddings[i][j];
	}
	this->clusternumber.clear();
	this->wordfreq.clear();
}

void Word2Vec::resetWeights(){
	this->globalembeddings.clear();
	this->senseembeddings.clear();
	this->clusterembeddings.clear();
	this->clusternumber.clear();
	this->wordfreq.clear();
	for (int i = 0; i < this->word_number; i++){
		this->globalembeddings.push_back(new Embedding(this->layer1_size));
		std::vector< Embedding* > v;
		v.clear();v.push_back(new Embedding(this->layer1_size));
		this->senseembeddings.push_back(v);
		std::vector<Embedding* > v1;
		v1.clear();v1.push_back(new Embedding(this->layer1_size));
		this->clusterembeddings.push_back(v1);
		std::vector<long long> v2;
		v2.clear();v2.push_back(0);
		this->wordfreq.push_back(v2);
		this->clusternumber.push_back(1);
	}
}
int main(){
	Word2Vec *w = new Word2Vec("test.txt",0);
	delete w;
    return 0;
}