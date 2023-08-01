#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

struct reflector{
    reflector();
    void reflect( char & );
    void load( const std::string & );
    std::vector<std::vector<char>>alphabet;   
};

struct reflector_paths{
	const std::string A = "./reflector_files/A.rfl";
	const std::string B = "./reflector_files/B.rfl";
	const std::string C = "./relfector_files/C.rfl";
	const std::string D = "./relfector_files/D.rfl";
	const std::string E = "./relfector_files/E.rfl";
	const std::string F = "./relfector_files/F.rfl";
	const std::string G = "./relfector_files/G.rfl";	
};