
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <climits>
#include "Vertex.h"

/*------------------------------------*/
class myGraph{

private:
    /* implementation using Adjacency list */
	vector<list<Vertex>> adjacencies;
	unsigned stopTime;

public:

	myGraph(unsigned init_time):stopTime(move(init_time)){} // c'tor
	~myGraph(){} // d'tor
    /*===================================*/
    myGraph(const myGraph&) = delete; // disable copy c'tor
    void operator=(const myGraph&) = delete; // disable assignment operator
    unsigned getStopTime() const {return stopTime;}
    void setStopTime(unsigned new_time) {stopTime = new_time;}
    /* inserts Vertex to Graph */
    void addVertex(const string& station_name);
    /* add edge between 'src' and 'dst' with weight 'time' */
    void addEdge(const string& src,const string& dst, unsigned time);
    /* returns true if Vertex exists, else false */
    bool vertexExist(const string& vertex_to_find) const;
    /* returns the index in the array where the Vertex, else -1 */
    int getVertexIndexInVector(const string& vertex_to_find);
    /* prints Graph to output file */
    void printGraph(ofstream& fout) const;
    /* returns number of vertexes */
    unsigned getGraphSize() const {return adjacencies.size();}
    /* if edge does not exists, returns the start of iterator of source vertex */
    list<Vertex>::iterator getEdge(unsigned index, const string& vertex_to_find);
    /* find and print names of vertexes, which can be reached from 'source_vertex' */
    void outboundGraph(const string& source_vertex);
    void auxiliaryOutboundGraph(const string& vertex, shared_ptr<bool> v_tbl);
    /* find and print the nodes which can reach 'target_vertex' */
    void inboundGraph(const string& target_vertex);
    void auxiliaryInboundGraph(const string& vertex, shared_ptr<bool> v_tbl, unsigned& i, const string& target);
    /* finding the shortest paths between nodes in a graph */
    void dijkstra(const string& source, const string& target);
/*===================================*/
    class iterator
    {
        vector<list<Vertex>>* pItem; // pointer to Adjacency list
        unsigned index;

    public:
        iterator(vector<list<Vertex>>* p, unsigned i=0):pItem(p), index(i){}

        Vertex& operator*()
        {
            if(index<0 || index>=(*pItem).size())
               throw "out of range vector<list<Vertex>>::iterator\n";

            return (*pItem).at(index).front();
        }

        Vertex* operator->()
        {
            if(index<0 || index>=(*pItem).size())
               throw "out of range vector<list<Vertex>>::iterator\n";

            return &((*pItem).at(index).front());
        }

        iterator operator++(int)
        {
            iterator temp = *this;
            ++*this;
            return temp;
        }

        iterator& operator++()
        {
            if(index>=(*pItem).size())
               throw "out of range vector<list<Vertex>>::iterator\n";

            ++index;
            return *this;
        }

        iterator operator--()
        {
            if(index==0 || index>(*pItem).size())
               throw "out of range vector<list<Vertex>>::iterator\n";

            --index;
            return *this;
        }

        iterator operator--(int)
        {
            iterator temp = *this;
            --*this;
            return temp;
        }

        bool operator!=(const iterator& itr) const
        {
            return (index!=itr.index);
        }

        bool operator==(iterator lhs)
        {
            return (index==lhs.index);
        }
    };
/*===================================*/
    iterator begin() {return iterator(&adjacencies);}
    iterator end() {return iterator(&adjacencies, adjacencies.size());}
};

#endif

