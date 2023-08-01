#include <vector>
#include <algorithm>

struct plugboard{

    plugboard();
    void encode( char & );
    void connect( int , int );
    std::vector<std::vector<char>>alphabet;

};