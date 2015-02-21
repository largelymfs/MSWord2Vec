#ifndef FILEREADER_H
#define FILEREADER_H
#include <string>
#include <stdlib>

class FileReader{
public:
	FileReader(const char* filename, int max_string);
	~FileReader();
	bool hasWord();
	void getWord(char* word);
private:
	const int MAX_STRING;
	char* filename;
	FILE* fin;
	long long filesize;
};

#endif