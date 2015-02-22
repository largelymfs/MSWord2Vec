

#ifndef WORD2VEC_H
#define WORD2VEC_H

#include "embedding.h"
#include "VocabGen.h"

class Word2Vec{
public:
	Word2Vec(	const char* filename, 
				int min_count, int window, 
				int size, double alpha, 
				double min_alpha, int negative);
	void resetWeights();
	void saveModel(const char* filename);
	~Word2Vec();
private:
	VocabGen* v;
	RandomGen* r;
	int layer1_size, window_size, min_count, negative;
	long long word_number;
	double alpha, min_alpha;
	std::vector<Embedding*> globalembeddings;
	std::vector< std::vector<Embedding*> > senseembeddings;
	std::vector< std::vector<Embedding*> > clusterembeddings;
	std::vector<int> clusternumber;
	std::vector< std::vector<long long> > wordfreq;
};

#endif