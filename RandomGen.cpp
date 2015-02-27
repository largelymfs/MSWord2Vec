/* 
* @Author: largelymfs
* @Date:   2015-02-17 23:45:12
* @Last Modified by:   largelyfs
* @Last Modified time: 2015-02-27 16:49:28
*/
#include "RandomGen.h"
#include <iostream>
#define TIMER 25214903917

RandomGen::RandomGen(int seed){
	this->next_random = seed;
}
RandomGen::~RandomGen(){
}
unsigned long long RandomGen::Next(){
	unsigned long long res = this->next_random;
	this->next_random = this->next_random * (unsigned long long)(TIMER) + 11;
	return res;
}
double RandomGen::Random(){
	unsigned long long res = this->Next();
	return ((res & 0xFFFF) / (float) 65536);
}

using namespace std;


/*
int main(){
	RandomGen *r = new RandomGen();
	for (int i = 0; i < 10; i++)
		std::cout << r->Random() << std::endl;
	delete r;
    return 0;
}*/