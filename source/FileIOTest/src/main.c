//#include <iostream>
#include <fstream>
#include "ConfigSettings.H"


int main (void)
{
    configuration::data myconfigdata;
    std::ifstream f;
    f.open( "myprog.ini" );
    f >> myconfigdata;
    f.close();

    return 0;
}
