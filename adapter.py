#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author: largelyfs
# @Date:   2015-02-24 10:58:11
# @Last Modified by:   largelyfs
# @Last Modified time: 2015-02-27 16:34:17


#convert the MS-word2vec to Word2vec model
def convert(input, output):
	with open(input) as fin, open(output,"w") as fout:
		print >>fout, fin.readline().strip()
		while True:
			l1 = fin.readline()
			if not l1:
				break
			l2 = fin.readline()
			print >>fout, l1.strip().split()[0],
			print >>fout, l2.strip()


if __name__=="__main__":
	convert("./output.txt","vectors.bin")