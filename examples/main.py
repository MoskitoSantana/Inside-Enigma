import sys
sys.path.append('../zig-out/lib')
import libenigma
from sys import argv as cmd
from enum import Enum

STATIC_ROTOR = libenigma.rotor()
STATIC_REFLECTOR = libenigma.reflector()

class MODES(Enum):
    UNSET = 0xFFF
    ENCODE = 0
    DECODE = 1

def HELP():
    print("""
    \tNote : The commands should be use in the following order :
    \t1> -e/d for encode/decode mode
    \t2> -ri <\"a#oP\"> ringstellum configuration
    \t3> -re <filename> reflector file name
    \t4> -ro <filename> rotor files names  must be separated by comma eg. I,III,IV,VII
    \t5> \"message\" keep \" 
    """)
    sys.exit(1)


def main():

    if( "-h" in cmd ):
        HELP()

    if( len(cmd) == 9):
        pass
    else:
        HELP()
        
    mode = MODES.UNSET.value
    if( cmd[1] == "-e" ):
        mode = MODES.ENCODE.value
    elif( cmd[1] == "-d" ):
        mode = MODES.DECODE.value
    else:
        HELP()

    if(cmd[2] == "-ri"):
        pass
    else:
        HELP()
    
    if( len(cmd[3]) == 4 ):
        pass
    else:
        HELP()

    if( cmd[4] == "-re" ):
        pass
    else:
        HELP()

    if( cmd[6] == "-ro"):
        pass
    else:
        HELP()
    rotors = cmd[7].split(',')
    if( len(rotors) != 4 ):
        HELP()
    
    enigma = libenigma.enigma()
    enigma.manage_rotor_load(
        STATIC_ROTOR.load_rotor_path( rotors[0] ),
        STATIC_ROTOR.load_rotor_path( rotors[1] ),
        STATIC_ROTOR.load_rotor_path( rotors[2] ),
        STATIC_ROTOR.load_rotor_path( rotors[3] )
    )
    enigma.ringstellum( cmd[3][0] , cmd[3][1] , cmd[3][2] , cmd[3][3] )
    enigma.manage_reflector_load( STATIC_REFLECTOR.load_reflector_path( cmd[5] ) )
    msg = cmd[8]

    match mode:
        case MODES.ENCODE.value:
            msg = enigma.py_encode_string( cmd[8] )
        case MODES.DECODE.value:
            msg = enigma.py_decode_string( cmd[8] )
    
    print(msg)



if __name__ == "__main__":
    main()
