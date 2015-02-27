#ifndef EXPTABLE_H
#define EXPTABLE_H

#include <math.h>
//Exp-table Class

class ExpTable{
public:
	ExpTable(int MAX_TABLE_SIZE, int MAX_EXP);
	void init();								//initialize
	double& operator[](int index);				//index
	~ExpTable();
	void show();								//print it out
private:
	double* elem;
	int max_exp, max_table_size;
};


#endif