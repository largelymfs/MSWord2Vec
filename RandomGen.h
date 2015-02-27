#ifndef RANDOMGEN_H
#define RANDOMGEN_H

// Random Generator
class RandomGen{
public:
	RandomGen(int seed = 1); 			// initial Function given a seed
	~RandomGen();
	unsigned long long Next();			// get the next random function 
	double Random();  					// a random number from 0 to 1
private:
	unsigned long long next_random;
};


#endif