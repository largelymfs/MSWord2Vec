/* 
* @Author: largelymfs
* @Date:   2015-02-18 15:23:16
* @Last Modified by:   largelymfs
* @Last Modified time: 2015-02-19 13:54:07
*/

#include <iostream>
#include"FileReader.h"

using namespace std;

FileReader::FileReader(const char* filename):MAX_STRING(100){
	this->filename = new char[this->MAX_STRING];
	strcpy(this->filename, filename);
	this->fin = fopen(this->filename, "rb");
}
FileReader::~FileReader(){
	if (this->filename) delete[] this->filename;
}
void FileReader::getWord(char* word){
	int a = 0, ch;
	while (!feof(this->fin)){
		ch = fgetc(this->fin);
		if (ch == 13) continue;
		if ((ch == ' ') || (ch =='\t') || (ch == '\n')){
			if (a > 0){
				if (ch =='\n') ungetc(ch, this->fin);
				break;
			}
			if (ch =='\n'){
				strcpy(word, (char *) "</s>");
				return;
			}else continue;
		}
		word[a] = ch;
		a++;
		if (a >= this->MAX_STRING - 1) a--;
	}
	word[a] = 0;
}
bool FileReader::hasWord(){
	if (feof(fin)){
		this->filesize = ftell(fin);
		fclose(fin);
		return false;
	}
	return true;
}

int main(){
	char s[10]="test.txt";
	FileReader *f = new FileReader(s);
	char word[100];
	while (f->hasWord()){
		f->getWord(word);
		std::cout << word << std::endl;
	}
	delete f;
    return 0;
}