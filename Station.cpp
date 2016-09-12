
#include "Station.h"

/*---------------------------------------*/
Station::~Station(){} // default d'tor
/*---------------------------------------*/

/* initialization static variables */
unsigned Station::TIME_INTERCITY=15;
unsigned Station::TIME_CITY=10;
unsigned Station::TIME_CENTRAL=5;

/*---------------------------------------*/
shared_ptr<Station> Station::makeStation(const string& new_station_name)
{
	if (new_station_name.substr(0,2) == "IC"){
        return (shared_ptr<Station>(new Intercity(new_station_name)));
	}
	else if(new_station_name.substr(0,2) == "CS"){
            return (shared_ptr<Station>(new Central(new_station_name)));
	}
	else{
        return (shared_ptr<Station>(new City(new_station_name)));
	}
}
/*---------------------------------------*/
