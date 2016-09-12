#ifndef APPLICATION_H
#define APPLICATION_H


#include <algorithm>
#include <exception>
#include "myGraph.h"
using namespace std;

const unsigned MAXNAMELENGTH = 16;
enum VehicleTypes{bus,tram,sprinter,rail};

/*---------------------------------------*/
class ArgumentsException : public exception
{
    public:
        ArgumentsException(){}
        virtual ~ArgumentsException() throw (){}
        virtual const char* what() const throw()
        {
            return "ERROR: Not enough arguments\n";
        }
};
/*---------------------------------------*/

/*---------------------------------------*/
class ProtocolException : public exception
{
    public:
        ProtocolException(){}
        virtual ~ProtocolException() throw (){}
        virtual const char* what() const throw()
        {
            return "ERROR: Protocol input error\n";
        }
};
/*---------------------------------------*/

/*---------------------------------------*/
class ErrorFileNameException : public exception
{
    public:
        ErrorFileNameException(){}
        virtual ~ErrorFileNameException() throw (){}
        virtual const char* what() const throw()
        {
            return "ERROR: Input file name is wrong\n";
        }
};
/*---------------------------------------*/


/*--------------------------------------*/
class FileOpeningException : public exception
{
    public:
        FileOpeningException(const string& val)
        :str("ERROR: Unable to open file <" + val + ">\n")
        {}
        virtual ~FileOpeningException() throw (){}

        virtual const char* what() const throw()
        {
            return str.c_str();
        }
    private:
        string str;

};
/*------------------------------------*/


/*--------------------------------------*/
class NodeDoesNotExistException : public exception
{
    public:
        NodeDoesNotExistException(const string& val)
        :str("<" + val + "> " + "does not exist in the current network\n") {}
        virtual ~NodeDoesNotExistException() throw (){}

        virtual const char* what() const throw()
        {
            return str.c_str();
        }
    private:
        string str;

};
/*------------------------------------*/


/*--------------------------------------*/
class FormatException : public exception
{
    public:
        FormatException(){}
        virtual ~FormatException() throw (){}
        virtual const char* what() const throw()
        {
            return "ERROR: Format is wrong\n";
        }
};
/*------------------------------------*/



class TransportApp
{
    public:
        TransportApp():output_file("output.dat"), // default output file
        graphBus(DEFAULT_TIME_BUS), graphTram(DEFAULT_TIME_TRAM),
        graphSprinter(DEFAULT_TIME_SPRINTER), graphRail(DEFAULT_TIME_RAIL)
        {} //default c'tor of graphs
        ~TransportApp() {} //default d'tor
        TransportApp(const TransportApp&) = delete; // disable copy c'tor
        void operator=(const TransportApp&) = delete; // disable assignment operator
        /* reads and checks files, that have been received as arguments to main function,
        ** if something is wrong, throws exceptions */
        void getAndCheckInputFiles(const int& number_of_files, const char *files[]);
        /* checks file name and returns its type,
        ** if something is wrong, throws ErrorFileNameException() */
        VehicleTypes checkFileName(const string& check_name) const;
        /* opens files, check the format, initializes graphs according to input files */
        void initialization(const vector<string>& infiles, const vector<VehicleTypes>& invehicle);
        /* beginning of the program running, waiting for the command from the user */
        void start();
        /* splitting and checking line depending on delimiter, throws ProtocolException() */
        void splitLine(string& temp, string& string_1, string& string_2, string& string_3, char delim);
        /* checks name of Vertex (Station), throws FormatException() */
        void checkNodeName(const string& check_str);
        /* checks hop time of edge (travel_time), throws FormatException() */
        void checkTime(const string& check_str);
        /* load input file, check its, and update graph */
        void load(const string& file_name);
        /* updating configurations in graph */
        void configUpdate(const char* file_name);
        /* printing all graph in output file */
        void print() const;
        void outbound(const string& vertex);
        void inbound(const string& vertex);
        void express(const string& source, const string& target);


    private:
        const unsigned DEFAULT_TIME_BUS=1;
        const unsigned DEFAULT_TIME_TRAM=2;
        const unsigned DEFAULT_TIME_SPRINTER=3;
        const unsigned DEFAULT_TIME_RAIL=5;

        string output_file;
        myGraph graphBus, graphTram, graphSprinter, graphRail;

};

/*=======================================*/
/* global function, returns 'true' if a string is integer number */
bool is_number(const std::string& s);
/* global function, returns 'true' if a string is alphabetic */
bool is_alphabet(const std::string& s);
/*=======================================*/


#endif // APPLICATION_H
