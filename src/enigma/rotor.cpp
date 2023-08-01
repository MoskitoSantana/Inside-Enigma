#include "rotor.hpp"


rotor::rotor(){
	this->rotation_count = 0;
	this->alphabet.resize(2);
    this->alphabet.at(0) = std::vector<char>(95);
    int n = 32;
    std::generate(this->alphabet.at(0).begin(), this->alphabet.at(0).end(), [n]() mutable { return static_cast<char>(n++); });
}

void rotor::encode( char &character ){
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

void rotor::decode( char &character){
	size_t SIZE = this->alphabet.at(0).size();
	for( size_t i = 0; i < SIZE ; i++ ){
        if( this->alphabet.at(1).at(i) == character ){
            character = this->alphabet.at(0).at(i); 
            return;
        }
        else if( this->alphabet.at(1).at(SIZE - i - 1) == character ) {
            character = this->alphabet.at(0).at(SIZE - i - 1);
            return;
        }
    }
}

void rotor::rotation(){
	this->rotation_count++;
	std::rotate( this->alphabet[1].begin() , this->alphabet[1].begin() + 1, this->alphabet[1].end() );
}

void rotor::reversed_rotation(){
	this->rotation_count--;
	std::rotate( this->alphabet[1].rbegin() , this->alphabet[1].rbegin() + 1, this->alphabet[1].rend() );
}


void rotor::load( const std::string& path ){
	std::ifstream file_( path , std::ios::in );
	if ( !file_.is_open() ) {
        exit(EXIT_FAILURE);
    }
    std::string text((std::istreambuf_iterator<char>(file_)), std::istreambuf_iterator<char>());
	file_.close();
	for( auto character : text ){
		this->alphabet.at(1).push_back(character);
	}
}

const char rotor::top(){
    return this->alphabet[1].front();
}