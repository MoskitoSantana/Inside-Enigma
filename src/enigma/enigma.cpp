#include "enigma.hpp"

Enigma::Enigma(){
    this->wheels = std::make_shared< std::vector<Rotor>>();
    this->wheels.get()->resize(4);
    this->plug_board = std::make_shared<Plugboard>();
    this->mirror = std::make_shared<Reflector>();
}

void Enigma::encode_string( std::string &string ){
    std::string new_string = "";
    for( auto& character : string ){
        this->encode_character( character );
        new_string.push_back( character );
    }
    string = new_string;
}

void Enigma::encode_character( char &character ){
    this->plug_board->encode( character );
    for( auto& rotor_in : ((*this->wheels)) ){
        rotor_in.encode( character );
    }
    this->handle_rotation();
    this->swap( 0 , 1 , 2, 3 );
    this->mirror->reflect( character );
    for( auto& rotor_in : ((*this->wheels)) ){
        rotor_in.decode( character );
    }
    this->swap( 0 , 1 , 2, 3 );
    this->plug_board->encode( character );    
}

void Enigma::decode_string( std::string &string ){
    const size_t length = string.length();
    std::string new_string = "";
    char tmp = ' ';
    for( size_t i = 0; i < length; i++ ){
        tmp = string[i];
        this->decode_character( tmp , i );
        new_string.push_back( tmp );
    }
    string = new_string;

}

void Enigma::decode_character( char &character , const size_t index ){
    for( size_t i = 0; i <= index ; i++ ){ 
        this->handle_rotation();  
    }
    this->plug_board->encode( character ); 
    for( auto& rotor_in : (*this->wheels) ){
        rotor_in.encode( character ); 
    }
    this->handle_reversed_rotation(); 
    this->mirror->reflect( character );  
    this->swap( 0 , 1 , 2 , 3 ); 
    for( auto& rotor_in : (*this->wheels) ){
        rotor_in.decode( character );
    }
    this->plug_board->encode( character );
    this->swap( 0 , 1 , 2 , 3 ); 
    for( size_t i = index; i > 0 ; i-- ){ 
        this->handle_reversed_rotation();   
    }    
}

void Enigma::swap( int I , int II , int III , int IV ){
    std::swap( (*this->wheels).at(I) , (*this->wheels).at(IV) );
    std::swap( (*this->wheels).at(II) , (*this->wheels).at(III) );
}

void Enigma::handle_rotation(){
    (*this->wheels).at(0).rotation();
    if( (*this->wheels).at(0).rotation_count == 95 ){
        (*this->wheels).at(1).rotation();
        (*this->wheels).at(0).rotation_count = 0;
    }
    if( (*this->wheels).at(1).rotation_count == 93 ){
        (*this->wheels).at(2).rotation();
        (*this->wheels).at(1).rotation_count = 0;
    }
    if( (*this->wheels).at(2).rotation_count == 91 ){
        (*this->wheels).at(3).rotation();
        (*this->wheels).at(2).rotation_count = 0;
    }
    if( (*this->wheels).at(3).rotation_count == 95 ){
        (*this->wheels).at(3).rotation_count = 0;
    }
}

void Enigma::handle_reversed_rotation(){
    (*this->wheels).at(0).reversed_rotation();
    if( (*this->wheels).at(0).rotation_count == 95  ){
        (*this->wheels).at(1).reversed_rotation();
        (*this->wheels).at(0).rotation_count = 0;
    }
    if( (*this->wheels).at(1).rotation_count == 93 ){
        (*this->wheels).at(2).reversed_rotation();
        (*this->wheels).at(1).rotation_count = 0;
    }
    if( (*this->wheels).at(2).rotation_count == 91 ){
        (*this->wheels).at(3).reversed_rotation();
        (*this->wheels).at(2).rotation_count = 0;
    }
    if( (*this->wheels).at(3).rotation_count == 95 ){
        (*this->wheels).at(3).rotation_count = 0;
    }      
}

void Enigma::ringstellum( char A , char B , char C, char D ){
    while( ((*this->wheels)[0].top() != A ) && ( (*this->wheels)[1].top() != B ) && ( (*this->wheels)[2].top() != C ) && ( (*this->wheels)[3].top() != D ) ){
        this->handle_rotation(); 
    }
    for( auto& rotor_in : (*this->wheels) ){
        rotor_in.rotation_count = 0;
    }
}

void Enigma::manage_reflector_load( const std::string &path ){
    this->mirror.get()->load(path);
}

void Enigma::manage_rotor_load( const std::string &path_A, const std::string &path_B, const std::string &path_C, const std::string &path_D ){
    (*this->wheels)[0].load(path_A);
    (*this->wheels)[1].load(path_B);
    (*this->wheels)[2].load(path_C);
    (*this->wheels)[3].load(path_D);
}

void Enigma::manage_plugboard_connections( int A , int B ){
    this->plug_board.get()->connect( A , B );
}

std::string Enigma::py_encode_string( std::string& string ){
    this->encode_string( string );
    return string;
}

std::string Enigma::py_decode_string( std::string& string ){
    this->decode_string( string );
    return string;
}