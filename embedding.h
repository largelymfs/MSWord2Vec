#ifndef EMBEDDING_H
#define EMBEDDING_H

#include "RandomGen.h"

//Word Embedding Class
class Embedding{
public:
	Embedding(int n = 0);
	~Embedding();
	void randomGenerate(RandomGen& r); 		// Obtain Random Embeddings
	double similarity( Embedding& e);
	void Saxpy( Embedding& e, double g); 	// calculate this+=g*e
	double Norm(); 							// norm
	void show(); 							// print
	double Dot(Embedding& e);				// calculate this * e
	double& operator[](int index);			// index
private:
	double *elem;
	int size;
};


#endif