myTransportApp: main.o myGraph.o Station.o TransportApp.o
	g++ -std=c++11 -Wall -pedantic-errors main.o myGraph.o Station.o TransportApp.o -o myTransportApp

main.o: main.cpp TransportApp.h myGraph.h Vertex.h Station.h
	g++ -std=c++11 -Wall -pedantic-errors -c main.cpp

myGraph.o: myGraph.h myGraph.cpp Vertex.h Station.h
	g++ -std=c++11 -Wall -pedantic-errors -c myGraph.cpp
	
Station.o: Station.cpp Station.h
	g++ -std=c++11 -Wall -pedantic-errors -c Station.cpp
	
TransportApp.o: TransportApp.cpp TransportApp.h myGraph.h Vertex.h Station.h
	g++ -std=c++11 -Wall -pedantic-errors -c TransportApp.cpp
	