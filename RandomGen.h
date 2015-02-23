#ifndef RANDOMGEN_H
#define RANDOMGEN_H

class RandomGen{
public:
	RandomGen(int seed = 1);
	~RandomGen();
	unsigned long long Next();
	double Random();  //A random number from 0 to 1
private:
	unsigned long long next_random;
};


#endif