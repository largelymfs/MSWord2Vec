#ifndef FILEREADER_H
#define FILEREADER_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

class FileReader{
public:
	FileReader(const char* filename, int max_string, long long starting_position);
	~FileReader();
	long long fileSize();															// get file size
	bool hasWord();																	// check whether file ends
	void getWord(char* word);														// fetch a word
private:
	const int MAX_STRING;
	char* filename;
	FILE* fin;
	long long filesize;
	int state;
};

#endif
