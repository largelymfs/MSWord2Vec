/* 
* @Author: largelyfs
* @Date:   2015-02-22 15:35:19
* @Last Modified by:   largelyfs
* @Last Modified time: 2015-02-26 01:33:37
*/

#include <iostream>
#include "ExpTable.h"
using namespace std;
#include "stdio.h"

ExpTable::ExpTable(int MAX_TABLE_SIZE, int MAX_EXP) : elem(NULL), max_table_size(MAX_TABLE_SIZE), max_exp(MAX_EXP){
	this->elem = new double[this->max_table_size];
	this->init();
}

ExpTable::~ExpTable(){
	if (elem!=NULL) delete[] elem;
}

void ExpTable::init(){
	for (int i = 0; i < this->max_table_size; i ++){
		this->elem[i] = exp((i / (double)(this->max_table_size) * 2.0 -1.0) * this->max_exp);
		this->elem[i] = (this->elem[i]) / (this->elem[i] + 1.0);
	}
}

void ExpTable::show(){
	for (int i = 0; i < this->max_table_size; i++)
		printf("%lf\n", this->elem[i]);
	fflush(stdout);
}

double& ExpTable::operator[](int index){
	return this->elem[index];
}

// int main(){
// 	ExpTable *e = new ExpTable(1000, 6);
// 	for (int i = 0; i< 10; i++)
// 		std::cout << (*e)[i] << std::endl;
// 	delete e;
//     return 0;
// }