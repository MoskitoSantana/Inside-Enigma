#include "plugboard.hpp"

Plugboard::Plugboard() {
    this->alphabet.resize(2);
    this->alphabet.at(0) = std::vector<char>(95);
    this->alphabet.at(1) = std::vector<char>(95);
    int n = 32;
    std::generate(this->alphabet.at(0).begin(), this->alphabet.at(0).end(), [n]() mutable { return static_cast<char>(n++); });
    std::generate(this->alphabet.at(1).begin(), this->alphabet.at(1).end(), [n]() mutable { return static_cast<char>(n++); });
}

void Plugboard::connect( int character_A , int  character_B ){
    auto tmp = this->alphabet[0][character_A];
	this->alphabet[0][character_A] = this->alphabet[1][character_B];
	this->alphabet[1][character_B] = tmp; 
}

void Plugboard::encode( char & character ){
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