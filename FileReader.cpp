/*
* @Date: Sun Mar 08 22:32:59 2015 +0800
* @Last Modified by:   largelyfs
* @Last Modified time: 2015-02-23 11:26:56
*/
#include "stdio.h"
#include <iostream>
#include"FileReader.h"

using namespace std;

FileReader::FileReader(const char* filename, int max_string, long long starting_pos):MAX_STRING(max_string){
	this->filename = new char[this->MAX_STRING];
	strcpy(this->filename, filename);
	this->fin = fopen(this->filename, "rb");
	fseek(this->fin, starting_pos, SEEK_SET);
	state = true;
}
FileReader::~FileReader(){
	fclose(this->fin);
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
//		fclose(fin);
		state = false;
	}
	return state;
}
long long FileReader::fileSize(){
	return this->filesize;
}

// int main(){
// 	char s[10]="test.txt";
// 	FileReader *f = new FileReader(s, 100);
// 	char word[100];
// 	while (f->hasWord()){
// 		f->getWord(word);
// 		std::cout << word << std::endl;
// 	}
// 	delete f;
//     return 0;
// }
