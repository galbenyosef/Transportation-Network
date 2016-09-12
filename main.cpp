
#include "TransportApp.h"

int main(int argc, const char **argv)
{
    TransportApp app;

    try
    {
        app.getAndCheckInputFiles(argc, argv);
        app.start();
    }
    catch(exception& ex)
    {
        cerr << ex.what();
    }

    return 0;
}
