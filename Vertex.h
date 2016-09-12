#ifndef VERTEX_H_
#define VERTEX_H_

#include "Station.h"

/*---------------------------------------*/
class Vertex{

private:
    /* pointer to station (Polymorphism) */
	shared_ptr<Station> station;
	/* hop time */
	unsigned travel_time;

public:

	Vertex(shared_ptr<Station> new_station, unsigned time=0) // c'tor
	:station(new_station), travel_time(time) {}
	~Vertex(){} // d'tor

    /* copy constructor */
	Vertex(const Vertex& other)
	:station(Station::makeStation(other.station->getName())),
	travel_time(other.getTravelTime()){}

    /* copy assignment */
    Vertex& operator=(const Vertex& rhs)
    {
        if(this == &rhs) // copying from the same object return *this;
            return *this;

        station.reset(); // Releases the ownership of the managed object
        station = Station::makeStation(rhs.station->getName()); // Replaces the managed object
        travel_time = rhs.travel_time;
        return *this;
    }

    /* move constructor */
    Vertex(Vertex&& that): station{that.station}, travel_time{that.travel_time}
    {
        that.travel_time = 0;
        that.station = nullptr;
    }

    /* move assignment */
    Vertex& operator=(Vertex&& that) {
        swap(travel_time, that.travel_time);
        swap(station, that.station);
        return *this;
    }

    /* return pointer to station */
    shared_ptr<Station> getStation()const {return station;}
    /* return hop time */
    unsigned getTravelTime() const {return travel_time;}
    /* set new hop time */
    void setTravelTime(unsigned new_time) {travel_time = new_time;}

};
/*---------------------------------------*/

#endif
