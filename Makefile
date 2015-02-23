all:
	g++ -o test VocabGen.cpp Word2Vec.cpp HashMap.cpp embedding.cpp FileReader.cpp RandomGen.cpp ExpTable.cpp -lpthread