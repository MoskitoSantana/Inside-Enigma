#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

struct Rotor
{
	Rotor();
	void encode( char & );
	void decode( char & );
	void load( const std::string & );
	char top();
	void rotation();
	void reversed_rotation();
	static std::string load_rotor_path( const std::string & file_name );
	std::vector<std::vector<char>>alphabet;
	int rotation_count;
	
};

