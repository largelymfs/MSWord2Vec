#ifndef EXPTABLE_H
#define EXPTABLE_H

#include <math.h>

class ExpTable{
public:
	ExpTable(int MAX_TABLE_SIZE, int MAX_EXP);
	void init();
	double& operator[](int index);
	~ExpTable();
	void show();
private:
	double* elem;
	int max_exp, max_table_size;
};


#endif