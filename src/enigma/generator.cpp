#include "generator.hpp"

std::mt19937 randomizer(){
    std::random_device rd;
    return std::mt19937( rd() );
}

void gen_rotors( std::string name ){
    std::vector< char >characters(95);
    int n = 32;
    std::generate(characters.begin(), characters.end(), [n]() mutable { return static_cast<char>(n++); }); 
    std::shuffle( characters.begin() , characters.end(), randomizer() );
    std::string file_path = "./rotor_files/" + (name + ".rot");
    std::ofstream writer( file_path , std::ios::out  );
    for( auto character : characters ){
        writer << character ;
    }
    writer.close();    
}

void gen_reflectors(std::string name) {

    std::vector< char > characters( 95 );
    int n = 32;
    std::generate(characters.begin(), characters.end(), [n]() mutable { return static_cast<char>(n++); });     
    std::shuffle(characters.begin(), characters.end(), randomizer());
    std::string file_path = "./reflector_files/" + (name + ".rfl");
    std::ofstream writer( file_path , std::ios::out  );
    for( auto character : characters ){
        writer << character ;
    }
    writer.close();     

}
