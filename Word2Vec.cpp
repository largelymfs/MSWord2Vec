/* 
* @Author: largelyfs
* @Date:   2015-02-21 21:05:25
* @Last Modified by:   largelyfs
* @Last Modified time: 2015-02-23 11:17:19
*/

#include "pthread.h"
#include <iostream>



#define MAX_STRING_LENGTH 100
#define  TABLE_SIZE 1e8
#define EXPTABLE_MAX_TABLE_SIZE 1000
#define EXPTABLE_MAX_EXP 6


using namespace std;
#include "Word2Vec.h"
struct Word2vecWithInt{
	int id;
	Word2Vec* w;
	Word2vecWithInt(Word2Vec* w, int id):id(id),w(w){}
};

void* trainModelThread(void* id){
	Word2vecWithInt* data = (Word2vecWithInt*)(id);
	Word2Vec* w = data->w;
	
	return NULL;
}

Word2Vec::Word2Vec(	const char* filename, int min_count=4, 
					int window=5, int size=100, double alpha=0.25, 
					double min_alpha=0.001, int negative = 5,
					int thread_number = 4){
	this->v = new VocabGen(filename, MAX_STRING_LENGTH);
	this->r = new RandomGen();
	this->e = new ExpTable(EXPTABLE_MAX_TABLE_SIZE, EXPTABLE_MAX_EXP);
	this->min_count = min_count;
	this->window_size = window;
	this->alpha = alpha;
	this->min_alpha = min_alpha;
	this->layer1_size = size;
	this->negative = negative;
	this->tablesize = TABLE_SIZE;
	this->table = NULL;
	this->thread_number = thread_number;
	this->v->buildVocab();
	this->v->reduceVocab(this->min_count);
	this->word_number = this->v->size();
	this->resetWeights();
	this->inittable();
	this->trainModel();
}

Word2Vec::~Word2Vec(){
	if (v!=NULL) delete v;
	if (r!=NULL) delete r;
	if (e!=NULL) delete e;
	if (this->table!=NULL) delete this->table;
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
		this->clusternumber.push_back(0);
	}
	//generate the random weights
	for (int i = 0; i < this->word_number; i++){
		this->globalembeddings[i]->randomGenerate(*(this->r));
		this->clusterembeddings[i][0]->randomGenerate(*(this->r));
		this->senseembeddings[i][0]->randomGenerate(*(this->r));
	}
	// this->globalembeddings[0]->show();
	// this->senseembeddings[0][0]->show();
	// this->clusterembeddings[0][0]->show();
}

void Word2Vec::inittable(){
	int a, i;
	double train_words_pow = 0;
	double d1, power = 0.75;
	this->table = new int[this->tablesize];
	for (a = 0; a < this->word_number; a++) train_words_pow += pow(this->v->searchWordCnt(a), power);
	i = 0;
	d1 = pow(this->v->searchWordCnt(i), power) / train_words_pow;
	for (a = 0; a < this->tablesize; a++){
		this->table[a] = i;
		if (a / double(this->tablesize) > d1){
			i++;
			d1 += pow(this->v->searchWordCnt(i), power) / train_words_pow;
		}
		if (i >= this->word_number) i = this->word_number -1;
	}
}

void Word2Vec::saveModel(const char* filename){
	FILE *fo;
	fo = fopen(filename,"wb");
	fprintf(fo, "%lld %d\n", this->word_number, this->layer1_size);
	for (int i = 0; i < this->word_number; i++){
		fprintf(fo, "%s ", this->v->searchWordContent(i).c_str());
		for (int j = 0; j < this->layer1_size; j++)
			fprintf(fo,"%lf ", (*(this->globalembeddings[i]))[j]);
		fprintf(fo, "\n");
		for (int num = 0; num < this->clusterembeddings[i].size(); num++){
			for (int j = 0; j< this->layer1_size; j++)
				fprintf(fo, "%lf ", (*(this->senseembeddings[i][num]))[j]);
			fprintf(fo, "\n");
		}
	}
}

void Word2Vec::trainModel(){
	pthread_t *pt = new pthread_t[this->thread_number];
	Word2vecWithInt** data = new Word2vecWithInt*[this->thread_number];
	for (int i = 0; i < this->thread_number; i++){
		data[i] = new Word2vecWithInt(this, i);
	}
	for (int i = 0; i < this->thread_number; i++) pthread_create(&pt[i], NULL, trainModelThread, (void*)(data[i]));
	for (int i = 0; i < this->thread_number; i++) pthread_join(pt[i], NULL);
	for (int i = 0; i < this->thread_number; i++) delete data[i];
	delete data;
	delete pt;
}


int main(){
	Word2Vec *w = new Word2Vec("test.txt",0);
	w->saveModel("output.txt");
	delete w;
    return 0;
}