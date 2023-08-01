#include "enigma/enigma.hpp"
#include "enigma/generator.hpp"
#include <iostream>
#include <memory>

int main(){

  std::string msg_for_enigma = "Alea Jacta Est!";
  {
    std::shared_ptr<enigma> cypher = std::make_shared<enigma>();
    (*cypher).manage_reflector_load( reflector_paths().B );
    (*cypher).manage_rotor_load( rotor_paths().II , rotor_paths().IV , rotor_paths().I , rotor_paths().V );
    (*cypher).ringstellum('A','(','/','f');
    (*cypher).manage_plugboard_connections(4,54);
    (*cypher).manage_plugboard_connections(90,24);
    (*cypher).manage_plugboard_connections(5,75);
    (*cypher).manage_plugboard_connections(84,31);
    (*cypher).encode_string(msg_for_enigma);
  }  
  std::cout << msg_for_enigma << std::endl;
  {
    std::shared_ptr<enigma>decoder = std::make_shared<enigma>();
    (*decoder).manage_reflector_load( reflector_paths().B );
    (*decoder).manage_rotor_load( rotor_paths().II , rotor_paths().IV , rotor_paths().I , rotor_paths().V );
    (*decoder).ringstellum('A','(','/','f');
    (*decoder).manage_plugboard_connections(4,54);
    (*decoder).manage_plugboard_connections(90,24);
    (*decoder).manage_plugboard_connections(5,75);
    (*decoder).manage_plugboard_connections(84,31);
    (*decoder).decode_string(msg_for_enigma);
  } 
  std::cout << msg_for_enigma << std::endl;

  return EXIT_SUCCESS;

}