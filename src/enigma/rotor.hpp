#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

struct rotor
{
	rotor();
	void encode( char & );
	void decode( char & );
	void load( const std::string & );
	const char top();
	void rotation();
	void reversed_rotation();
	std::vector<std::vector<char>>alphabet;
	int rotation_count;
	
};

struct rotor_paths{
	const std::string I = "./rotor_files/I.rot";
	const std::string II = "./rotor_files/II.rot";
	const std::string III = "./rotor_files/III.rot";
	const std::string IV = "./rotor_files/IV.rot";
	const std::string V = "./rotor_files/V.rot";
	const std::string VI = "./rotor_files/VI.rot";
	const std::string VII = "./rotor_files/VII.rot";
	const std::string VIII = "./rotor_files/VIII.rot";	
};