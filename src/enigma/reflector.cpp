#include "reflector.hpp"
#include <iostream>

reflector::reflector(){
    this->alphabet.resize(2);
}

void reflector::load( const std::string& path ){
	std::ifstream file_( path , std::ios::in );
	if( !file_.is_open() ) {
        exit(EXIT_FAILURE);
    }
    std::string text((std::istreambuf_iterator<char>(file_)), std::istreambuf_iterator<char>());
	file_.close();
	for( auto character : text ){
		this->alphabet.at(1).push_back(character);
	}
	for( auto character = this->alphabet.at(1).rbegin(); character != this->alphabet.at(1).rend(); character++){
		this->alphabet.at(0).push_back(*character);
	}
}

void reflector::reflect( char &character ){
    size_t SIZE = this->alphabet.at(0).size();
	for( size_t i = 0; i < SIZE ; i++ ){
        if( this->alphabet.at(0).at(i) == character ){
            character = this->alphabet.at(1).at(i); 
            return;
        }
        else if( this->alphabet.at(0).at(SIZE - i - 1) == character ) {
            character = this->alphabet.at(1).at(SIZE - i - 1);
            return;
        }
    }
}