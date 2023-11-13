#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

struct Reflector{
    Reflector();
    void reflect( char & );
    void load( const std::string & );
    static std::string load_reflector_path( const std::string & file_name );
    std::vector<std::vector<char>>alphabet;   
};
