#include "TransportApp.h"


/*---------------------------------------*/
void TransportApp::getAndCheckInputFiles(const int& num_arguments, const char *files[])
{
    if(num_arguments < 3)
    {
        throw ArgumentsException();
    }
    vector<string> infiles;
    vector<VehicleTypes> vec_vehicle;////

    string str_temp;

    str_temp = files[1];
    if(str_temp == "-i") // input files
    {
        for(int i=2; i<num_arguments; i++)
        {
            str_temp = files[i];
            if(str_temp == "-c") // configuration file
            {
                if(++i < num_arguments)
                {
                    configUpdate(files[i]);
                    continue;
                }
                else
                    throw ProtocolException();
            }
        /*====================================*/
            if(str_temp == "-o") // output file
            {
                if(++i < num_arguments)
                {
                    this->output_file = files[i];
                    continue;
                }
                else
                    throw ProtocolException();
            }
        /*====================================*/
            vec_vehicle.push_back(checkFileName(str_temp)); // add to vector of vehicle types
            infiles.push_back(str_temp); // add name of input file to vector
        }
    }// End if()

    initialization(infiles, vec_vehicle);
}
/*---------------------------------------*/


/*---------------------------------------*/
VehicleTypes TransportApp::checkFileName(const string& check_name) const
{
    if( check_name.substr(0,3) == "bus"){return bus;}

    if( check_name.substr(0,4) == "tram"){return tram;}

    if( check_name.substr(0,4) == "rail"){return rail;}

    if( check_name.substr(0,8) == "sprinter"){return sprinter;}

    throw ErrorFileNameException();
}
/*---------------------------------------*/


/*---------------------------------------*/
void TransportApp::initialization(const vector<string>& infiles, const vector<VehicleTypes>& invehicle)
{
    string temp_buffer, src, dest, time;
    VehicleTypes const*  p = invehicle.data();

    for(vector<string>::const_iterator it = infiles.begin() ; it != infiles.end(); ++it, ++p)
    {
        ifstream fin((*it).c_str());
        if(!fin.is_open())
           throw FileOpeningException((*it));

        while(getline(fin, temp_buffer))
        {
            splitLine(temp_buffer, src, dest, time, '\t');
            checkNodeName(src);
            checkNodeName(dest);
            checkTime(time);
            if(*p == bus)
            {
                graphBus.addEdge(src, dest, (unsigned)atoi(time.c_str()));
            }
            else
            if(*p == tram)
            {
                graphTram.addEdge(src, dest, (unsigned)atoi(time.c_str()));
            }
            else
            if(*p == sprinter)
            {
                graphSprinter.addEdge(src, dest, (unsigned)atoi(time.c_str()));
            }
            else
            if(*p == rail)
            {
                graphRail.addEdge(src, dest, (unsigned)atoi(time.c_str()));
            }
            temp_buffer.clear();
        }

        fin.close();
    }
}
/*---------------------------------------*/


/*---------------------------------------*/
void TransportApp::checkTime(const string& check_str)
{
    if( !is_number(check_str) )
        throw FormatException();
}
/*---------------------------------------*/


/*---------------------------------------*/
void TransportApp::checkNodeName(const string& check_str)
{
    if( check_str.length() > MAXNAMELENGTH || !is_alphabet(check_str))
        throw FormatException();
}
/*---------------------------------------*/


/*---------------------------------------*/
void TransportApp::start()
{
    string command, first, second, temp_buffer;

    do
    {
        command.clear(); first.clear(); second.clear(); temp_buffer.clear();


        try
        {
            getline(cin, temp_buffer); // wait to input from user
            splitLine(temp_buffer, command, first, second, ' ');

            if( command == "load" && !first.empty() && second.empty() )
            {
                load(first);
                cout << "Update was successful\n";
            }
            else
            if( command == "outbound" && !first.empty() && second.empty() )
            {
                outbound(first);
            }
            else
            if( command == "inbound" && !first.empty() && second.empty() )
            {
                inbound(first);
            }
            else
            if( command == "express" && !first.empty() && !second.empty() )
            {
                express(first,second);
            }
            else
            if( command == "print" && first.empty() && second.empty() )
            {
                print();
            }
            else
            if( command == "exit" && first.empty() && second.empty() )
            {
                cout << "Bye-Bye\n";
            }
            else
                throw ProtocolException();

        }
        catch(exception& ex)
        {
            cerr << ex.what();
        }

    }while(command != "exit");
}
/*---------------------------------------*/


/*---------------------------------------*/
void TransportApp::splitLine(string& temp, string& string_1, string& string_2, string& string_3, char delim)
{
    size_t pos;

    /*=============================*/
    pos = temp.find(delim);
    string_1 = temp.substr(0, pos);
    if (pos == string::npos)
        return;

    /*=============================*/
    temp = temp.substr(pos+1, string::npos);
    pos = temp.find(delim);
    string_2 = temp.substr(0, pos);
    if (pos == string::npos)
        return;

    /*=============================*/
    temp = temp.substr(pos+1, string::npos);
    pos = temp.find(delim);
    string_3 = temp.substr(0, pos);
    if (pos == string::npos)
        return;
    /*=============================*/

    throw ProtocolException();
}
/*---------------------------------------*/


/*---------------------------------------*/
void TransportApp::load(const string& file_name)
{
    VehicleTypes vt = checkFileName(file_name);
    string temp_buffer, src, dest, time;

    ifstream fin(file_name.c_str());
    if(!fin.is_open())
        throw FileOpeningException(file_name);

    while(getline(fin, temp_buffer))
    {
        splitLine(temp_buffer, src, dest, time, '\t');
        checkNodeName(src);
        checkNodeName(dest);
        checkTime(time);
        if(vt == bus)
        {graphBus.addEdge(src, dest, (unsigned)atoi(time.c_str()));}
        else
        if(vt == tram){graphTram.addEdge(src, dest, (unsigned)atoi(time.c_str()));}
        else
        if(vt == sprinter){graphSprinter.addEdge(src, dest, (unsigned)atoi(time.c_str()));}
        else
        if(vt == rail){graphRail.addEdge(src, dest, (unsigned)atoi(time.c_str()));}
        temp_buffer.clear();
    }

    fin.close();
}
/*---------------------------------------*/


/*---------------------------------------*/
bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),s.end(), [](char c)
                            { return !std::isdigit(c); }) == s.end();
}
/*---------------------------------------*/


/*---------------------------------------*/
bool is_alphabet(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),s.end(), [](char c)
                            { return !std::isalpha(c); }) == s.end();
}
/*---------------------------------------*/


/*---------------------------------------*/
void TransportApp::configUpdate(const char* file_name)
{
    string line_buffer, val_type, time, temp;

    ifstream fin(file_name);
        if(!fin.is_open())
           throw FileOpeningException(file_name);

    while(getline(fin, line_buffer))
    {
        splitLine(line_buffer, val_type, time, temp, ' ');
        if(!temp.empty())
            throw FormatException();

        checkTime(time);

        if(val_type == "bus"){
            graphBus.setStopTime((unsigned)atoi(time.c_str()));
        }
        else if(val_type == "tram"){
            graphTram.setStopTime((unsigned)atoi(time.c_str()));
        }
        else if(val_type == "rail"){
            graphRail.setStopTime((unsigned)atoi(time.c_str()));
        }
        else if(val_type == "sprinter"){
            graphSprinter.setStopTime((unsigned)atoi(time.c_str()));
        }
        else if(val_type == "intercity"){
            Station::TIME_INTERCITY = (unsigned)atoi(time.c_str());
        }
        else if(val_type == "city"){
            Station::TIME_CITY = (unsigned)atoi(time.c_str());
        }
        else if(val_type == "central"){
            Station::TIME_CENTRAL = (unsigned)atoi(time.c_str());
        }
        else {
            throw ProtocolException();
        }

        line_buffer.clear();
    } // End while()

        fin.close();
}
/*---------------------------------------*/


/*---------------------------------------*/
void TransportApp::print() const
{
    ofstream fout(output_file.c_str());
    fout << "BUS:";
    graphBus.printGraph(fout);
    fout << "====================\n";

    fout << "TRAM:";
    graphTram.printGraph(fout);
    fout << "====================\n";

    fout << "SPRINTER:";
    graphSprinter.printGraph(fout);
    fout << "====================\n";

    fout << "RAIL:";
    graphRail.printGraph(fout);
    fout << "====================\n";

    fout.close();
}
/*---------------------------------------*/


/*---------------------------------------*/
void TransportApp::outbound(const string& vertex)
{
    if(!graphBus.vertexExist(vertex) && !graphTram.vertexExist(vertex) &&
        !graphSprinter.vertexExist(vertex) && !graphRail.vertexExist(vertex) )
    {
        throw NodeDoesNotExistException(vertex);
    }

        cout << "bus: ";
        graphBus.outboundGraph(vertex);
        cout << endl;
        cout << "tram: ";
        graphTram.outboundGraph(vertex);
        cout << endl;
        cout << "sprinter: ";
        graphSprinter.outboundGraph(vertex);
        cout << endl;
        cout << "rail: ";
        graphRail.outboundGraph(vertex);
        cout << endl;
}
/*---------------------------------------*/


/*---------------------------------------*/
void TransportApp::inbound(const string& vertex)
{
    if(!graphBus.vertexExist(vertex) && !graphTram.vertexExist(vertex) &&
        !graphSprinter.vertexExist(vertex) && !graphRail.vertexExist(vertex) )
    {
        throw NodeDoesNotExistException(vertex);
    }

        cout << "bus: ";
        graphBus.inboundGraph(vertex);
        cout << endl;
        cout << "tram: ";
        graphTram.inboundGraph(vertex);
        cout << endl;
        cout << "sprinter: ";
        graphSprinter.inboundGraph(vertex);
        cout << endl;
        cout << "rail: ";
        graphRail.inboundGraph(vertex);
        cout << endl;
}
/*---------------------------------------*/


/*----------------------------------------*/
void TransportApp::express(const string& source, const string& target)
{
    if(!graphBus.vertexExist(source) && !graphTram.vertexExist(source) &&
        !graphSprinter.vertexExist(source) && !graphRail.vertexExist(source) )
    {
        throw NodeDoesNotExistException(source);
    }

    if(!graphBus.vertexExist(target) && !graphTram.vertexExist(target) &&
        !graphSprinter.vertexExist(target) && !graphRail.vertexExist(target) )
    {
        throw NodeDoesNotExistException(target);
    }

    cout << "bus: ";
    if(!graphBus.vertexExist(source) || !graphBus.vertexExist(target))
        cout << "route unavailable\n";
    else
        graphBus.dijkstra(source, target);

    cout << "tram: ";
    if(!graphTram.vertexExist(source) || !graphTram.vertexExist(target))
        cout << "route unavailable\n";
    else
        graphTram.dijkstra(source, target);

    cout << "sprinter: ";
    if(!graphSprinter.vertexExist(source) || !graphSprinter.vertexExist(target))
        cout << "route unavailable\n";
    else
        graphSprinter.dijkstra(source, target);

    cout << "rail: ";
    if(!graphRail.vertexExist(source) || !graphRail.vertexExist(target))
        cout << "route unavailable\n";
    else
        graphRail.dijkstra(source, target);

}
/*----------------------------------------*/
