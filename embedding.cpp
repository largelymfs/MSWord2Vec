/* 
* @Author: largelymfs
* @Date:   2015-02-17 23:37:15
* @Last Modified by:   largelyfs
* @Last Modified time: 2015-02-28 00:15:11
*/

#include "embedding.h"
#include "math.h"
#include <iostream>
using namespace std;

Embedding::Embedding(int n){
	this->size = n;
	this->elem = new double[n];
}
Embedding::~Embedding(){
	if (this->elem!=NULL) delete[] this->elem;
}
void Embedding::randomGenerate(RandomGen& r){
	for (int i = 0; i < this->size; i++)
		this->elem[i] = (r.Random() - 0.5) * (1.0 / double(this->size));
}
double Embedding::similarity( Embedding& e){
	double norm1,norm2;
	norm1 = this->Norm();
	norm2 = e.Norm();
	double res = this->Dot(e);
	return (res / norm1) / norm2;
}
void Embedding::Saxpy( Embedding& e, double g){
	for (int i = 0; i < this->size; i++)
		this->elem[i] += (g * e[i]);
}
double Embedding::Norm(){
	double res = 0.0;
	for (int i = 0; i < this->size; i++)
		res += (this->elem[i]) * (this->elem[i]);
	return sqrt(res);
}
void Embedding::show(){
	for (int i = 0; i < this->size; i++)
		std::cout << this->elem[i] << " ";
	std::cout << std::endl;
}
double Embedding::Dot( Embedding& e){
	double res = 0.0;
	for (int i = 0; i < this->size; i++)
		res += e[i] * this->elem[i];
	return res;
}
double& Embedding::operator[](int index){
	return this->elem[index];
}

void Embedding::Clear(){
	for (int i = 0; i < this->size; i++)
		this->elem[i] = 0.0;
}
void Embedding::Multi(double g){
	for (int i = 0; i < this->size; i++)
		this->elem[i] = this->elem[i] * g;
}

// int main(){
// 	Embedding *e = new Embedding(10);
// 	RandomGen *r = new RandomGen();
// 	Embedding *e1 = new Embedding(10);
// 	e->randomGenerate(*r);
// 	e1->randomGenerate(*r);
// 	e1->show();
// 	std::cout << e->Dot(*e1) << std::endl;
// 	std::cout << e1->Dot(*e) << std::endl;
// 	for (int i = 0; i < 10; i++){
// 		(*e1)[i] = 0.0;
// 	}
// 	e1->show();
// 	std::cout << e->Dot(*e1) << std::endl;
// 	std::cout << e1->Dot(*e) << std::endl;
// 	e1->randomGenerate(*r);
// 	std::cout << e->similarity(*e1) << std::endl;
// 	e1->randomGenerate(*r);
// 	e->randomGenerate(*r);
// 	e->show();
// 	e1->show();
// 	e1->Saxpy((*e), 0.5);
// 	e1->show();
// 	delete e;
// 	delete e1;
// 	delete r;
//     return 0;
// }