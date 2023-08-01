from enigma_py import enigma_py


def main():

    msg_for_enigma = "Alea Jacta Est!"
    cypher = enigma_py.enigma()
    decoder = enigma_py.enigma()

    cypher.manage_rotor_load( enigma_py.rotor_paths().I , enigma_py.rotor_paths().III , enigma_py.rotor_paths().IV , enigma_py.rotor_paths().V )
    cypher.manage_reflector_load( enigma_py.reflector_paths().B )
    cypher.ringstellum( 'A' , 'c' , '#' , 'p' )

    cyphered_msg_for_enigma = cypher.py_encode_string( msg_for_enigma )

    decoder.manage_rotor_load( enigma_py.rotor_paths().I , enigma_py.rotor_paths().III , enigma_py.rotor_paths().IV , enigma_py.rotor_paths().V )
    decoder.manage_reflector_load( enigma_py.reflector_paths().B )
    decoder.ringstellum( 'A' , 'c' , '#' , 'p' )    
    
    decoded_msg_for_enigma = decoder.py_decode_string( cyphered_msg_for_enigma )

    print( cyphered_msg_for_enigma )
    print( decoded_msg_for_enigma )


if __name__ == "__main__":
    main()