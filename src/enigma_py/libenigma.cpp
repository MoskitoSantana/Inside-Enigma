#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>

#include <memory>
#include <vector>
#include "../enigma/generator.hpp"
#include "../enigma/enigma.hpp"

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE( std::shared_ptr< std::vector<Rotor> > );

PYBIND11_MODULE( libenigma , enigma_mod ){
    
    enigma_mod.def( "randomizer" , &randomizer );
    enigma_mod.def( "gen_rotors" , &gen_rotors , py::arg("path") , "Random Rotor File Configuration Generator " );
    enigma_mod.def( "gen_reflector" , &gen_reflectors , py::arg("path"), "Random Reflector File Configuration Generator" );

    py::class_<Rotor , std::shared_ptr<Rotor> >( enigma_mod , "Rotor" )
        .def( py::init<>() )
        .def( "encode" , &Rotor::encode , py::arg("character") )
        .def( "decode" , &Rotor::decode , py::arg("character") )
        .def( "load" , &Rotor::load , py::arg("path") )
        .def( "top" , &Rotor::top )
        .def( "rotation", &Rotor::rotation )
        .def( "reversed_rotation" , &Rotor::reversed_rotation )
        .def_static("load_rotor_path" , &Rotor::load_rotor_path, py::arg("file_name"))
        .def_readwrite( "alphabeth" , &Rotor::alphabet)
        .def_readwrite( "rotation_count" , &Rotor::rotation_count ); 

    py::class_<Reflector , std::shared_ptr<Reflector> >( enigma_mod , "Reflector" )
        .def( py::init<>() )
        .def( "reflect" ,  &Reflector::reflect , py::arg("character") )
        .def( "load" , &Reflector::load , py::arg("path") )
        .def_static("load_Reflector_path", &Reflector::load_Reflector_path, py::arg("file_name") )
        .def_readwrite( "alphabet" , &Reflector::alphabet );

    
    py::class_<Plugboard , std::shared_ptr<Plugboard> >( enigma_mod , "Plugboard" )
        .def( py::init<>() )
        .def( "encode" , &Plugboard::encode , py::arg("character") )
        .def( "connect" ,  &Plugboard::connect , py::arg("character_A") , py::arg("character_B")  )
        .def_readwrite( "alphabet" , &Plugboard::alphabet );

    py::class_<Enigma>( enigma_mod , "Enigma" )
        .def( py::init<>() )
        .def( "encode_string" , &Enigma::encode_string , py::arg("string") )
        .def( "encode_character" , &Enigma::encode_character , py::arg("character") )
        .def( "decode_string" , &Enigma::decode_string , py::arg("string") )
        .def( "decode_character" , &Enigma::decode_character , py::arg( "character" ) , py::arg("index") )
        .def( "swap" , &Enigma::swap , py::arg("A") , py::arg("D") , py::arg("C") , py::arg("D")  )
        .def( "ringstellum" , &Enigma::ringstellum , py::arg("character_a") , py::arg("character_b") , py::arg("character_c") , py::arg("character_d") )
        .def( "handle_rotation" , &Enigma::handle_rotation )
        .def( "handle_reversed_rotation" , &Enigma::handle_reversed_rotation )
        .def( "manage_rotor_load" , &Enigma::manage_rotor_load , py::arg( "path_A" ) ,py::arg( "path_B" ), py::arg( "path_C" ), py::arg( "path_D" ) )
        .def( "manage_reflector_load" , &Enigma::manage_reflector_load , py::arg("path") )
        .def( "manage_plugboard_connections" , &Enigma::manage_plugboard_connections , py::arg("A") , py::arg("B") )
        .def( "py_decode_string" , &Enigma::py_decode_string , py::arg("string") )
        .def( "py_encode_string" , &Enigma::py_encode_string , py::arg("string") )
        .def_readwrite( "wheels" , &Enigma::wheels )
        .def_readwrite( "plug_board" , &Enigma::plug_board )
        .def_readwrite( "mirror" , &Enigma::mirror );
}