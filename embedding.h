#ifndef EMBEDDING_H
#define EMBEDDING_H

#include "RandomGen.h"

class Embedding{
public:
	Embedding(int n = 0);
	~Embedding();
	void randomGenerate(RandomGen& r);
	double similarity( Embedding& e);
	void Saxpy( Embedding& e, double g);
	double Norm();
	void show();
	double Dot(Embedding& e);
	double& operator[](int index);
private:
	double *elem;
	int size;
};


#endif