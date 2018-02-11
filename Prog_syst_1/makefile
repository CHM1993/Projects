test: main.o tree_list.o bloomfilter.o
	g++ main.o tree_list.o bloomfilter.o -L . -loracle_v2 -lhash

main.o: main.cpp
	g++ - c main.cpp

tree_list.o: tree_list.cpp
	g++ -c tree_list.cpp

bloomfilter.o: bloomfilter.cpp
	g++ -c bloomfilter.cpp
