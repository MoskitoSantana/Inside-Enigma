#include "reflector.hpp"
#include <iostream>

Reflector::Reflector(){
    this->alphabet.resize(2);
}

void Reflector::load( const std::string& path ){
    std::string text;
    std::ifstream file(path);
    if (!file.is_open()) {
        exit(EXIT_FAILURE);
    }
    std::getline(file, text, '\0');
    file.close();
	for( auto character : text ){
		this->alphabet.at(1).push_back(character);
	}
	for( auto character = this->alphabet.at(1).rbegin(); character != this->alphabet.at(1).rend(); character++){
		this->alphabet.at(0).push_back(*character);
	}
}


void Reflector::reflect( char &character ){
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


std::string Reflector::load_reflector_path( const std::string & file_name ){
	return "./reflector_files/"+file_name+".rfl";	
};