
#include "myGraph.h"

/*----------------------------------------*/
void myGraph::addVertex(const string& station_name)
{
    shared_ptr<Station> ptr(Station::makeStation(station_name));
    list<Vertex> new_vertex_adj;
    new_vertex_adj.push_back(Vertex(ptr));
    adjacencies.push_back(move(new_vertex_adj));
}
/*----------------------------------------*/


/*----------------------------------------*/
void myGraph::printGraph(ofstream& fout) const
{
    fout << "  stop_time=" << stopTime << endl;

    for (auto it = adjacencies.begin(); it != adjacencies.end(); ++it)
    {
        auto e = (*it).begin();
        fout << "source=" << (*e).getStation()->getName();
        fout << ":  transit time=" << (*e).getStation()->getTransitTime() << endl;

        ++e;
        while(e != (*it).end())
        {
            fout << "->destination=" << (*e).getStation()->getName();
            fout << "  travel_time=" << (*e).getTravelTime() << endl;
            ++e;
        }
            fout << endl;
    } // End for()

}
/*----------------------------------------*/


/*----------------------------------------*/
void myGraph::addEdge(const string& src,const string& dst, unsigned time)
{
    if(!vertexExist(src))
        addVertex(src);

    int index = getVertexIndexInVector(src);
    if(!vertexExist(dst)) // new vertex
    {
        addVertex(dst);
        Vertex vt(Station::makeStation(dst), time);
        adjacencies.at(index).push_back(move(vt));
        return;
    }

    auto it = getEdge(index, dst);
    if(adjacencies.at(index).end() == it) // edge not exist
    {
        Vertex vt(Station::makeStation(dst), time);
        adjacencies.at(index).push_back(move(vt));
    }
    else
    {
        if( time < (*it).getTravelTime() )
        {
            (*it).setTravelTime(time);
        }
    }

}
/*----------------------------------------*/


/*----------------------------------------*/
list<Vertex>::iterator myGraph::getEdge(unsigned index, const string& vertex_to_find)
{
    auto it_list_begin = adjacencies.at(index).begin();
    auto it_list_end = adjacencies.at(index).end();
    while(it_list_begin != it_list_end)
    {
        if ((*it_list_begin).getStation()->getName() == vertex_to_find)
        {
            return (it_list_begin);
        }

        ++it_list_begin;
    }

    return (it_list_begin);
}
/*----------------------------------------*/


/*----------------------------------------*/
bool myGraph::vertexExist(const string& vertex_to_find) const
{
    for(const auto& elem : adjacencies)
    {
        auto sp = elem.begin();
        if((*sp).getStation()->getName() == vertex_to_find)
            return true;
    }
    return false;
}
/*----------------------------------------*/


/*----------------------------------------*/
int myGraph::getVertexIndexInVector(const string& vertex_to_find)
{
    int i = 0;
    for (auto it = adjacencies.begin(); it != adjacencies.end(); ++it, ++i)
    {
        auto e = (*it).begin();
        if ((*e).getStation()->getName()== vertex_to_find)
            return i;
    }

    return -1;
}
/*----------------------------------------*/


/*----------------------------------------*/
void myGraph::outboundGraph(const string& source_vertex)
{
    if(!vertexExist(source_vertex))
    {
        cout << "no outbound travel";
        return;
    }

    unsigned i = getGraphSize();
    shared_ptr<bool> arrayBool(new bool[i](), default_delete<bool[]>() );
    int index = getVertexIndexInVector(source_vertex);

    if(adjacencies.at(index).size() == 1)
    {
        cout << "no outbound travel";
        return;
    }

    auxiliaryOutboundGraph(source_vertex, arrayBool);
}
/*----------------------------------------*/


/*----------------------------------------*/
void myGraph::auxiliaryOutboundGraph(const string& vertex, shared_ptr<bool> v_tbl)
{
    unsigned idx = getVertexIndexInVector(vertex);
    v_tbl.get()[idx] = true;
    auto a = ++adjacencies.at(idx).begin();
    for(; a!=adjacencies.at(idx).end(); ++a){
        if(!v_tbl.get()[getVertexIndexInVector( a->getStation()->getName() )]){
            auxiliaryOutboundGraph((*a).getStation()->getName(), v_tbl);
            cout << a->getStation()->getName() << '\t';
        }
    }
}
/*----------------------------------------*/


/*----------------------------------------*/
void myGraph::inboundGraph(const string& target_vertex)
{
    if(!vertexExist(target_vertex))
    {
        cout << "no inbound travel";
        return;
    }

    unsigned i = getGraphSize();
    shared_ptr<bool> arrayBool(new bool[i](), default_delete<bool[]>() );

    unsigned cnt = 0;
    auxiliaryInboundGraph(target_vertex, arrayBool, cnt, target_vertex);
    if(cnt == 0)
    {
        cout << "no inbound travel";
    }

}
/*----------------------------------------*/


/*----------------------------------------*/
void myGraph::auxiliaryInboundGraph(const string& vertex, shared_ptr<bool> v_tbl, unsigned& i, const string& target)
{
	string src_vertex_name;
	unsigned src_vertex_idx;

	for (src_vertex_idx = 0; src_vertex_idx < adjacencies.size(); src_vertex_idx++)
    {
		auto a = ++adjacencies.at(src_vertex_idx).begin();
		for (; a!=adjacencies.at(src_vertex_idx).end();a++)
		{
			if( (a->getStation()->getName() == vertex)  && (!v_tbl.get()[src_vertex_idx]) )
            {
				v_tbl.get()[src_vertex_idx]=true;
				src_vertex_name=adjacencies.at(src_vertex_idx).begin()->getStation()->getName();
				auxiliaryInboundGraph(src_vertex_name,v_tbl, i, target);
				if(src_vertex_name != target)
                    cout << src_vertex_name << '\t';
				i++;
			}
		} // End for()
	}// End for()
}
/*----------------------------------------*/


/*----------------------------------------*/
void myGraph::dijkstra(const string& source, const string& target)
{
	//Comparator by Travel time
	class CompareGreater {
	public:
		bool const operator()(const Vertex& nodeX, const Vertex& nodeY) {
			return (nodeX.getTravelTime() > nodeY.getTravelTime());
		}
	};

	//priority queue for dijkstra algorithm
	priority_queue<Vertex, vector<Vertex>, CompareGreater> Q;
	//min weights, result table
	vector<unsigned> weights(adjacencies.size());
	fill(weights.begin(), weights.end(), INT_MAX);
	//string vertex_name = start.getStation()->getName();
	unsigned vertex_idx = getVertexIndexInVector(source);
	//init Starting vertex to 0
	weights[vertex_idx] = 0;
	Q.push((adjacencies.at(vertex_idx).front()));

//start algorithm
while (!Q.empty())
{
    Vertex currentVertex = Q.top();
    Q.pop();

    if (currentVertex.getTravelTime() <= weights[ getVertexIndexInVector(currentVertex.getStation()->getName()) ])
    {
        for (auto it = ++adjacencies[getVertexIndexInVector(currentVertex.getStation()->getName())].begin(); it != adjacencies[getVertexIndexInVector(currentVertex.getStation()->getName())].end(); ++it)
        {
            if (weights[getVertexIndexInVector(it->getStation()->getName())] > weights[getVertexIndexInVector(currentVertex.getStation()->getName())] + it->getTravelTime())
            {
                if( (it->getStation()->getName() == target) )
                {
                    weights[getVertexIndexInVector(it->getStation()->getName())] = weights[getVertexIndexInVector(currentVertex.getStation()->getName())] + it->getTravelTime();
                }
                else
                {
                    weights[getVertexIndexInVector(it->getStation()->getName())] = weights[getVertexIndexInVector(currentVertex.getStation()->getName())] + it->getTravelTime() + stopTime;
                }
                Q.push(Vertex(Station::makeStation(it->getStation()->getName()), weights[getVertexIndexInVector(it->getStation()->getName())]));
            }
        }
    } // End if()

} // End While()

        unsigned idx_target = getVertexIndexInVector(target);
        if(weights[idx_target] == INT_MAX)
            cout << "route unavailable\n";
        else
            cout << weights[idx_target] << endl;
}
/*----------------------------------------*/
