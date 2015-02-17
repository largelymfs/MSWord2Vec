#ifndef RANDOMGEN_H
#define RANDOMGEN_H

class RandomGen{
public:
	RandomGen();
	~RandomGen();
	long long Next();
	double Random();  //A random number from 0 to 1
private:
	long long next_random;
};


#endif