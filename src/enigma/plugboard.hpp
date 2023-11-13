#include <vector>
#include <algorithm>

struct Plugboard{

    Plugboard();
    void encode( char & );
    void connect( int , int );
    std::vector<std::vector<char>>alphabet;

};