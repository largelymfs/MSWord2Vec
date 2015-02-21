

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
	~Word2Vec();
private:
	VocabGen* v;
	int layer1_size, window_size, min_count, negative;
	double alpha, min_alpha;
	std::vector<Embedding*> globalembeddings;
	std::vector< std::vector<Embedding*> > senseembeddings;
	std::vector< std::vector<Embedding*> > clusterembeddings;
};

#endif