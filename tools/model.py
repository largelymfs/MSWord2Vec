# -*- coding:utf-8-*-
import random
import numpy as np
import sys
import numpy.linalg as LA

def convert2np(raw_string):
    return np.array([float(item) for item in raw_string.split()])

def similarity(emb1, emb2):
    try:
        return np.dot(emb1, emb2) / (LA.norm(emb1) * LA.norm(emb2))
    except:
        return 0.0

class MSWord2Vec:
    def __init__(self, vector_fn, cluster_fn, freq_fn):
        print "load vectors..."
        sys.stdout.flush()
        self.load_vectors(vector_fn)
        print "load cluster..."
        sys.stdout.flush()
        self.load_cluster(cluster_fn)
        print "load freq..."
        sys.stdout.flush()
        self.load_wordmap(freq_fn)
        print "ok"
        sys.stdout.flush()


    def load_vectors(self, filename):
        self.sense_vectors = {}
        self.global_vectors = {}
        with open(filename) as fin:
            vocab_size, layer_size = fin.readline().strip().split()
            self.vocab_size = int(vocab_size)
            self.layer_size = int(layer_size)
            for _ in range(self.vocab_size):
                words = fin.readline().strip().split()
                word = words[0]
                sense_number = int(words[1])
                self.global_vectors[word] = np.array([float(item) for item in words[2:]])
                self.sense_vectors[word] = []
                for _ in range(sense_number):
                    self.sense_vectors[word].append(convert2np(fin.readline().strip()))

    def load_wordmap(self, filename):
        self.wordmap = {}
        with open(filename) as f:
            for l in f:
                word = l.strip().split()[0]
                self.wordmap[word] = True

    def load_cluster(self, filename):
        self.cluster = {}
        with open(filename) as fin:
            vocab_size, layer_size = fin.readline().strip().split()
            vocab_size = int(vocab_size)
            layer_size = int(layer_size)
            for _ in range(vocab_size):
                word, sense_number = fin.readline().strip().split()
                sense_number = int(sense_number)
                self.cluster[word] = []
                for _ in range(sense_number):
                    self.cluster[word].append(convert2np(fin.readline().strip()))

    def compute_similarity(self, word1, sense1, word2, sense2):
        embedding1 = self.sense_vectors[word1][sense1]
        embedding2 = self.sense_vectors[word2][sense2]
        return (np.dot(embedding1, embedding2)) / (LA.norm(embedding1) * LA.norm(embedding2))

    def compute_kNN_one_sense(self, word1, sense1, k):
        res = []
        for word2 in self.wordmap:
            if word2==word1:
                continue
            for sense2 in range(len(self.sense_vectors[word2])):
                similarity = self.compute_similarity(word1, sense1, word2, sense2)
                res.append((word2, sense2, similarity))
        res = sorted(res, cmp=lambda x , y : -cmp(x[2],y[2]))
        return res[:k]

    def compute_kNN(self, word1, k = 10):
        result = []
        if word1 not in self.sense_vectors:
            return []
        for sense in range(len(self.sense_vectors[word1])):
            result.append(self.compute_kNN_one_sense(word1, sense, k))
        return result

    def infer_corpus(self, input_filename, output_filename, max_windows = 5):
        block_number = 0
        local_number = 0
        with open(input_filename) as fin, open(output_filename,"w") as fout:
            for l in fin:
                local_number +=1
                if (local_number == 1000):
                    block_number +=1
                    local_number = 0
                    print "LINE NUMBER : ", block_number , "K"
                words = l.strip().split()
                length = len(words)
                for (pos, word) in enumerate(words):
                    window = random.randint(1, max_windows)
                    start = max(0, pos - window)
                    finish = min(pos + window + 1, length)
                    cnt = 0.0
                    context = np.zeros(self.layer_size)
                    if word not in self.cluster:
                        continue

                    for my_pos in range(start, finish):
                        if my_pos==pos:
                            continue
                        word_item = words[my_pos]
                        if word_item not in self.global_vectors:
                            continue
                        else:
                            context = context + self.global_vectors[word_item]
                            cnt += 1.0

                    if cnt==0.0:
                        print >>fout, word, 0,
                    else:
                        max_distance = 0.0
                        my_label = 0
                        context = context * (1.0/float(cnt))
                        for (sense_number, cluster_vector) in enumerate(self.cluster[word]):
                            distance = similarity(context, cluster_vector)
                            if distance > max_distance:
                                max_distance = distance
                                my_label = sense_number
                        print >>fout, word, my_label,
                print >>fout


def check_main():
    #model = MSWord2Vec("./../Data/vector_rmrb-0.1.txt", "./../Data/cluster_rmrb-0.1.txt")
    model = MSWord2Vec("./../vector_rmrb-0.1.txt", "./../cluster_rmrb-0.1.txt", "./../freq_lite.txt")
    #model = MSWord2Vec("./../vector.demo","./../cluster.demo", "./../freq_lite.txt")
    while True:
        word = raw_input("Please Input a word : ")
        print word, type(word)
        if word=='EXIT':
            break
        result = model.compute_kNN(word, 10)
        for result_item in result:
            print "================================================="
            for (word, sense, similarity) in result_item:
                print word, similarity
            print "================================================="


if __name__=="__main__":
    model = MSWord2Vec("./../vector_rmrb-0.1.txt", "./../cluster_rmrb-0.1.txt","./../freq_lite.txt")
    model.infer_corpus("./../../rmrb.data","./../../rmrb.sense")
