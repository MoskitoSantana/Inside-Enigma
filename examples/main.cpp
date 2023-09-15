#include "../src/enigma/enigma.hpp"
#include "../src/enigma/generator.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

enum MODES{
  UNSET = 0xFFFF,
  ENCODE = 0,
  DECODE = 1
};

static const std::string HELP = std::string(
std::string("\tNote : The commands should be use in the following order :\n") +
std::string("\t1> -e/d for encode/decode mode\n")+
std::string("\t2> -ri <\"a#oP\"> ringstellum configuration\n")+
std::string("\t3> -re <filename> reflector file name\n")+
std::string("\t4> -ro <filename> rotor files names  must be separated by comma eg. I,III,IV,VII\n")+
std::string("\t5> \"message\" keep \" \n")) ;

int main(int argv , char * argc[]){

  if( argv < 8 || std::string(argc[1]) == "-h" || std::string(argc[1]) == "--help" ){
    std::cout << std::endl <<"User Guide :" << std::endl << HELP << std::endl;
    return EXIT_FAILURE;
  }

  int mode = int(MODES::UNSET) ;
  if( std::string(argc[1]) == "-e"  ){
    mode = int(MODES::ENCODE);
  }
  if( std::string(argc[1]) == "-d"  ){
    mode = int(MODES::DECODE);
  }
  if( mode == int(MODES::UNSET) ){
    return EXIT_FAILURE;
  }
  if( std::string( argc[2] ) != "-ri" ){
    return EXIT_FAILURE;
  }
  
  if( sizeof(argc[3]) < 6 && argc[3][0] != '"' && argc[3][5] !='"' ){
    return EXIT_FAILURE;
  }

  if( std::string( argc[4] ) != "-re" ){
    return EXIT_FAILURE;
  }
  std::string reflector = reflector::load_reflector_path( argc[5] ) ;
  
  if( std::string( argc[6] ) != "-ro" ){
    return EXIT_FAILURE;
  }
  std::vector<std::string> rotors(0);
  int comma_count = 0;
  std::string rotor_name = "";
  for( size_t i = 0; i < std::string(argc[7]).length() ; i++  ){
    if( argc[7][i] == ',' ){
      comma_count++;
      rotors.push_back(rotor_name);
      rotor_name = "";
    }
    else {
      rotor_name.push_back( argc[7][i] );    
    }
  }

  rotors.push_back(rotor_name);

  if( comma_count != 3 || rotors.size() != 4  ){
    return EXIT_FAILURE;
  }
  std::string msg_for_enigma = std::string( argc[8] ) ;
  std::shared_ptr<enigma> cypher = std::make_shared<enigma>();
  (*cypher).manage_reflector_load( reflector );
  (*cypher).manage_rotor_load( 
    rotor::load_rotor_path(rotors[0]) , rotor::load_rotor_path(rotors[1])  , 
    rotor::load_rotor_path(rotors[2]) , rotor::load_rotor_path(rotors[3])
  );
  (*cypher).ringstellum( argc[3][1] , argc[3][2] , argc[3][3] , argc[3][4] );
  (*cypher).manage_plugboard_connections(4,54);
  (*cypher).manage_plugboard_connections(90,24);
  (*cypher).manage_plugboard_connections(5,75);
  (*cypher).manage_plugboard_connections(84,31);  
  switch (mode) {
    case MODES::ENCODE :{
      (*cypher).encode_string(msg_for_enigma);
      break;
    }
    case MODES::DECODE :{
      (*cypher).decode_string(msg_for_enigma);
      break;
    }
  }

  std::cout << msg_for_enigma << std::endl;

  return EXIT_SUCCESS;

}
