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

PYBIND11_MAKE_OPAQUE( std::shared_ptr< std::vector<rotor> > );

PYBIND11_MODULE( libenigma , enigma_mod ){
    
    enigma_mod.def( "randomizer" , &randomizer );
    enigma_mod.def( "gen_rotors" , &gen_rotors , py::arg("path") , "Random Rotor File Configuration Generator " );
    enigma_mod.def( "gen_reflector" , &gen_reflectors , py::arg("path"), "Random Reflector File Configuration Generator" );

    py::class_<rotor , std::shared_ptr<rotor> >( enigma_mod , "rotor" )
        .def( py::init<>() )
        .def( "encode" , &rotor::encode , py::arg("character") )
        .def( "decode" , &rotor::decode , py::arg("character") )
        .def( "load" , &rotor::load , py::arg("path") )
        .def( "top" , &rotor::top )
        .def( "rotation", &rotor::rotation )
        .def( "reversed_rotation" , &rotor::reversed_rotation )
        .def_static("load_rotor_path" , &rotor::load_rotor_path, py::arg("file_name"))
        .def_readwrite( "alphabeth" , &rotor::alphabet)
        .def_readwrite( "rotation_count" , &rotor::rotation_count ); 

    py::class_<reflector , std::shared_ptr<reflector> >( enigma_mod , "reflector" )
        .def( py::init<>() )
        .def( "reflect" ,  &reflector::reflect , py::arg("character") )
        .def( "load" , &reflector::load , py::arg("path") )
        .def_static("load_reflector_path", &reflector::load_reflector_path, py::arg("file_name") )
        .def_readwrite( "alphabet" , &reflector::alphabet );

    
    py::class_<plugboard , std::shared_ptr<plugboard> >( enigma_mod , "plugboard" )
        .def( py::init<>() )
        .def( "encode" , &plugboard::encode , py::arg("character") )
        .def( "connect" ,  &plugboard::connect , py::arg("character_A") , py::arg("character_B")  )
        .def_readwrite( "alphabet" , &plugboard::alphabet );

    py::class_<enigma>( enigma_mod , "enigma" )
        .def( py::init<>() )
        .def( "encode_string" , &enigma::encode_string , py::arg("string") )
        .def( "encode_character" , &enigma::encode_character , py::arg("character") )
        .def( "decode_string" , &enigma::decode_string , py::arg("string") )
        .def( "decode_character" , &enigma::decode_character , py::arg( "character" ) , py::arg("index") )
        .def( "swap" , &enigma::swap , py::arg("A") , py::arg("D") , py::arg("C") , py::arg("D")  )
        .def( "ringstellum" , &enigma::ringstellum , py::arg("character_a") , py::arg("character_b") , py::arg("character_c") , py::arg("character_d") )
        .def( "handle_rotation" , &enigma::handle_rotation )
        .def( "handle_reversed_rotation" , &enigma::handle_reversed_rotation )
        .def( "manage_rotor_load" , &enigma::manage_rotor_load , py::arg( "path_A" ) ,py::arg( "path_B" ), py::arg( "path_C" ), py::arg( "path_D" ) )
        .def( "manage_reflector_load" , &enigma::manage_reflector_load , py::arg("path") )
        .def( "manage_plugboard_connections" , &enigma::manage_plugboard_connections , py::arg("A") , py::arg("B") )
        .def( "py_decode_string" , &enigma::py_decode_string , py::arg("string") )
        .def( "py_encode_string" , &enigma::py_encode_string , py::arg("string") )
        .def_readwrite( "wheels" , &enigma::wheels )
        .def_readwrite( "plug_board" , &enigma::plug_board )
        .def_readwrite( "mirror" , &enigma::mirror );
}