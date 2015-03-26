#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author: largelymfs
# @Date: Thu Mar 26 13:10:57 2015 +0800
# @Last Modified by:   largelyfs
# @Last Modified time: 2015-03-26 15:03:43

import numpy as np
import sys
import numpy.linalg as LA

def wordlist2array(l):
	return np.array([float(item) for item in l])



class Model:

	def __init__(self, filename):
		self._load_(filename)

	def similarity(self, word1, sense1, word2, sense2):
		embedding1 = self.senseembeddings[word1][sense1]
		embedding2 = self.senseembeddings[word2][sense2]
		return np.dot(embedding1, embedding2) / (LA.norm(embedding1) * LA.norm(embedding2))

	def _load_(self, filename):
		print "loading...",
		sys.stdout.flush();
		self.globalembeddings = {}
		self.senseembeddings = {}
		self.clusternumbers = {}
		with open(filename) as f:
			self.word_number, self.dimension = f.readline().strip().split()
			self.word_number = int(self.word_number)
			self.dimension = int(self.dimension)
			for _ in range(self.word_number):
				words = f.readline().strip().split()
				word = words[0]
				sense_number = int(words[1])
				self.clusternumbers[word] = sense_number
				self.globalembeddings[word] = wordlist2array(words[2:])
				self.senseembeddings[word] = [wordlist2array(f.readline().strip().split()) for _ in range(sense_number)]
		print "finished"



	def check(self, word, sense):
		res = []
		for worda in self.senseembeddings:
			number = len(self.senseembeddings[worda])
			for i in range(number):
				if (word==worda) and (sense==i):
					continue
				similarity = self.similarity(word, sense, worda, i)
				if similarity> 0.4:
					res.append((worda, i, similarity))
		res = sorted(res, cmp=lambda x, y : -cmp(x[2], y[2]))
		res = res[:10]
		print "============================================================"
		for (word, sense, similarity) in res:
			print word, sense, similarity
		print "============================================================"

	def show(self):
		
		total_times = 0.0
		total_cnt = 0.0
		for word in self.senseembeddings:
			total_cnt += 1.0
			total_times += len(self.senseembeddings[word])
		print "AVER SENSES : ", float(total_times) / float(total_cnt)

		while True:
			word = raw_input("Please input the word : ")
			if word=='EXIT':
				break
			for sense in range(self.clusternumbers[word]):
				self.check(word, sense)



if __name__ == '__main__':

	m = Model("vector.txt")
	m.show()



