/* 
* @Author: largelymfs
* @Date:   2015-02-18 11:15:37
* @Last Modified by:   largelyfs
* @Last Modified time: 2015-02-20 22:53:34
*/

#include <iostream>
#include "HashMap.h"

void sortlist(std::vector<std::string>& strlist, std::vector<int>& cntlist, int l, int r){
	int i, j, xcnt, mid, tmpcnt;
	std::string xstr, tmpstr;
	i = l;
	j = r;
	mid = (i + j) >> 1;
	xcnt = cntlist[mid];
	xstr = strlist[mid];
	while (i <= j){
		while ((i <= j) && (xcnt < cntlist[i])) i++;
		while ((i <= j) && (xcnt > cntlist[j])) j--;
		if (i <= j){
			tmpcnt = cntlist[i];cntlist[i] = cntlist[j];cntlist[j] = tmpcnt;
			tmpstr = strlist[i];strlist[i] = strlist[j];strlist[j] = tmpstr;
			i++;j--;
		}
	}
	if (l < j) sortlist(strlist, cntlist, l, j);
	if (i < r) sortlist(strlist, cntlist, i, r);
}

void Node::setWord( char* word, int cnt){
	int l = strlen(word);
	this->word = new char[l + 1];
	strcpy(this->word, word);
	this->cnt = cnt;
}
void Node::setWord(const char* word, int cnt){
	int l = strlen(word);
	this->word = new char[l + 1];
	strcpy(this->word, word);
	this->cnt = cnt;
}

HashMap::HashMap(): hash_size(30000007){
	this->content = new Node[this->hash_size];
	this->word_number = 0;
}
HashMap::~HashMap(){
	//delete all the content's words
	// for (int i = 0; i < this->hash_size; i++){
	// 	if (this->content[i].cnt!=0) std::cout << this->content[i].word << std::endl;
	// 	//if (this->content[i].cnt!=0) delete[] this->content[i].word;
	// }
	delete[] this->content;
}
long long HashMap::Hash( char* word){
	long long res = 0;
	int l = strlen(word);
	for (int i = 0; i < l; i++)
		res = (res << 8) + word[i];
	res = res % this->hash_size;
	res = (res + this->hash_size) % this->hash_size;
	return res;
}
long long HashMap::Hash(const char* word){
	long long res = 0;
	int l = strlen(word);
	for (int i = 0; i < l; i++)
		res = (res << 8) + word[i];
	res = res % this->hash_size;
	res = (res + this->hash_size) % this->hash_size;
	return res;
}
long long HashMap::searchWord( char *word){
	long long res = this->Hash(word);
	Node *tmp;
	while (true){		
		tmp = &(this->content[res]);
		if (tmp->cnt==0) return -1;
		if (strcmp(tmp->word, word)==0) return res;
		res++;
		if (res==this->hash_size) res = 0;
	}
	return -1;
}
long long HashMap::searchWordIndex( char* word){
	long long res = this->searchWord(word);
	return this->content[res].index;
}
void HashMap::addWord( char *word, int cnt){
	long long res = this->Hash(word);
	Node *tmp;
	if (this->word_number >= this->hash_size) return;

	while (true){
		tmp = &(this->content[res]);
		if (tmp->cnt==0){
			this->content[res].setWord(word, cnt);
			this->content[res].index = this->word_number;
			this->word_number++;
			return;
		}
		if (strcmp(tmp->word, word)==0){
			this->content[res].cnt+=cnt;
			return;
		}
		res++;
		if (res==this->hash_size) res = 0;
	}
}
void HashMap::addWord(const char *word, int cnt){
	long long res = this->Hash(word);
	Node *tmp;
	if (this->word_number >= this->hash_size) return;

	while (true){
		tmp = &(this->content[res]);
		if (tmp->cnt==0){
			this->content[res].setWord(word, cnt);
			this->content[res].index = this->word_number;
			this->word_number++;
			return;
		}
		if (strcmp(tmp->word, word)==0){
			this->content[res].cnt+=cnt;
			return;
		}
		res++;
		if (res==this->hash_size) res = 0;
	}
}

void HashMap::show(){
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "\t\tindex\t\tcount\t\twordindex\t\tword" << std::endl;
	for (int i = 0; i < this->hash_size; i++){
		if (this->content[i].cnt!=0){
			std::cout << "\t\t" << i << "\t\t" << this->content[i].cnt << "\t\t" << this->content[i].index << "\t\t" << this->content[i].word << std::endl;
		}
	}
}

void HashMap::reduce_vocab(int min_count){
	std::vector<std::string> strlist;
	std::vector<int> cntlist;
	for (int i = 0; i < this->hash_size; i++){
		if (this->content[i].cnt != 0 && this->content[i].cnt > min_count){
			strlist.push_back(std::string(this->content[i].word));
			cntlist.push_back(this->content[i].cnt);
		}
	}

	int l = strlist.size();

	sortlist(strlist, cntlist, 0, l-1);
	Node* old_content = this->content;
	this->content = new Node[this->hash_size];
	this->word_number = 0;
	for (int i = 0; i < l; i++)
		this->addWord(strlist[i].c_str(), cntlist[i]);

	delete[] old_content;
}

using namespace std;


// int main(){
// 	HashMap *h = new HashMap();
// 	char s[10]="hellolibo";
// 	h->addWord(s, 1);
// 	h->addWord(s, 1);
// 	std::cout << "BEGIN" << std::endl;
// 	h->addWord(s, 1);
// 	char t[11] = "largelymfs";
// 	h->addWord(t, 1);
// 	h->addWord(t, 1);
// 	h->show();
// 	h->reduce_vocab(2);
// 	h->show();
// 	delete h;	
//     return 0;
// }