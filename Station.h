#ifndef STATION_H_
#define STATION_H_

#include <string>
#include <memory>
#include <iostream>
using namespace std;

/* abstract class (Base) */
class Station{

protected:
	string name; // name of station

public:
    /*===== transit time =====*/
    static unsigned TIME_INTERCITY;
    static unsigned TIME_CITY;
    static unsigned TIME_CENTRAL;
    /*======================*/
    Station(const string& new_name):name(new_name){} // c'tor
	virtual ~Station()=0; // d'tor
	virtual unsigned getTransitTime()const =0; // abstract function
	virtual string getName()const {return name;}

    Station(const Station&) = delete; // disable copy c'tor
    void operator=(const Station&) = delete; // disable assignment operator
    /* create new station according to name */
	static shared_ptr<Station> makeStation(const string&);
};
/*---------------------------------------*/


/*---------------------------------------*/
class Intercity : public Station //derived class
{

public:

	Intercity(const string& new_name):Station(new_name){}
	virtual ~Intercity(){}
	virtual unsigned getTransitTime()const {return TIME_INTERCITY;}
};
/*---------------------------------------*/


/*---------------------------------------*/
class City : public Station //derived class
{

public:

	City(const string& new_name):Station(new_name){}
	virtual ~City(){}
	virtual unsigned getTransitTime()const {return TIME_CITY;}
};
/*---------------------------------------*/


/*---------------------------------------*/
class Central : public Station//derived class
{

public:

	Central(const string& new_name):Station(new_name){}
	virtual ~Central(){}
	virtual unsigned getTransitTime()const {return TIME_CENTRAL;}
};
/*---------------------------------------*/

#endif
