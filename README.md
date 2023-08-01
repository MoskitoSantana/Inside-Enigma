# Inside-Enigma
With a little passion for history, cryptography and a desire to program, I created my own version of the Enigma M4 
encryption machine model used by the Kriegsmarine, with alphabets extended to 64 ASCII printable characters.

## What is Enigma ?

To many, the Enigma machine is an enigma. But it’s really quite simple. 
The following is a step-by-step explanation of how it works, from the basics to the full machine.

Possibly the greatest dedicated cipher machine in human history the Enigma machine is a typewriter-sized machine,
with keyboard included, that the Germans used to encrypt and decrypt messages during World War II. It’s also one of
the machines that the Polish Cipher Bureau and those at Britain’s Bletchley Park figured out how to decipher, 
or break. Most recently the story of how it was broken was the topic of the movie The Imitation Game.

More information about how it works at :
** 1. [Hack A Day](https://hackaday.com/tag/enigma-machine/)**
** 2. [Wikipedia](https://en.wikipedia.org/wiki/Enigma_machine)**

# Code Examples 

Note : Two instances must be created ( one for encoding and one for decoding ) . As enigma encryption is symmetric it 
is necessary to use the same configuration of the instance used for encoding in the instance that will be used for decoding.

## C++ Snippets


### C++ Encryption Code Example
```
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

```

### C++ Desencryption Code Example
```
  {
    std::shared_ptr<enigma> decoder = std::make_shared<enigma>();
    (*decoder).manage_reflector_load( reflector_paths().B );
    (*decoder).manage_rotor_load( rotor_paths().II , rotor_paths().IV , rotor_paths().I , rotor_paths().V );
    (*decoder).ringstellum('A','(','/','f');
    (*decoder).manage_plugboard_connections(4,54);
    (*decoder).manage_plugboard_connections(90,24);
    (*decoder).manage_plugboard_connections(5,75);
    (*decoder).manage_plugboard_connections(84,31);
    (*decoder).encode_string(msg_for_enigma);
  }  
```

### C++ Rotor Files Generation
```
  auto rotor_names = { "R1" , "R2" , "R3" };

  for( auto rotor_name : rotor_names ){
    gen_rotors( rotor_name );
  }

```

### C++ Reflector Files Generation
```
  auto reflector_names = { "RFL1" , "RFL2" , "RFL3" };

  for( auto reflector_name : reflector_names ){
    gen_reflector( reflector_name );
  }

```

## Python Snippets

### Python Encryption Code Example
```
from enigma_py import enigma_py


def main():

    msg_for_enigma = "Alea Jacta Est!"
    cypher = enigma_py.enigma()

    cypher.manage_rotor_load( enigma_py.rotor_paths().I , enigma_py.rotor_paths().III , enigma_py.rotor_paths().IV , enigma_py.rotor_paths().V )
    cypher.manage_reflector_load( enigma_py.reflector_paths().B )
    cypher.ringstellum( 'A' , 'c' , '#' , 'p' )

    cyphered_msg_for_enigma = cypher.py_encode_string( msg_for_enigma )

```

### Python Desencyption Code Example
```
from enigma_py import enigma_py


def main():

    msg_for_enigma = "Alea Jacta Est!"
    decoder = enigma_py.enigma()

    decoder.manage_rotor_load( enigma_py.rotor_paths().I , enigma_py.rotor_paths().III , enigma_py.rotor_paths().IV , enigma_py.rotor_paths().V )
    decoder.manage_reflector_load( enigma_py.reflector_paths().B )
    decoder.ringstellum( 'A' , 'c' , '#' , 'p' )    
    
    decoded_msg_for_enigma = decoder.py_decode_string( cyphered_msg_for_enigma )

```

### Python Rotor Files Generation
```
from enigma_py import enigma_py as enp


def main():

    rotor_names : list = [ "R1" , "R2" , "R3" , "R4" ]

    for rotor_name in rotor_names:
      enp.gen_rotors( rotor_names )
```

### Python Reflector Fies Generation
```
from enigma_py import enigma_py as enp


def main():

    reflector_names : list = [ "RFL1" , "RFL2" , "RFL3" , "RFL4" ]

    for reflector_name in reflector_names:
      enp.gen_reflectors( reflector_names )
```

