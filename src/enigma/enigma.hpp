#include <string>
#include <memory>
#include "rotor.hpp"
#include "reflector.hpp"
#include "plugboard.hpp"

struct enigma{
    
    enigma();
    void encode_string( std::string & );
    std::string py_encode_string( std::string & );
    void encode_character( char & );
    void decode_string( std::string & );
    void decode_character( char & , const size_t );
    std::string py_decode_string( std::string & );
    void swap( int , int , int , int );
    void ringstellum( char, char, char, char );
    void handle_rotation();
    void handle_reversed_rotation();
    void manage_reflector_load( const std::string & );
    void manage_rotor_load( const std::string &, const std::string &, const std::string &, const std::string & );
    void manage_plugboard_connections( int , int );
    std::shared_ptr<std::vector<rotor>>wheels;
    std::shared_ptr<plugboard>plug_board;
    std::shared_ptr<reflector>mirror;

};