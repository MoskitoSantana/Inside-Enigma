# Inside-Enigma
With a little passion for history, cryptography and a desire to program, I created my own version of the Enigma M4 
encryption machine model used by the Kriegsmarine, with alphabets extended.

## What is Enigma ?

To many, the Enigma machine is an enigma. But it’s really quite simple. 
The following is a step-by-step explanation of how it works, from the basics to the full machine.

Possibly the greatest dedicated cipher machine in human history the Enigma machine is a typewriter-sized machine,
with keyboard included, that the Germans used to encrypt and decrypt messages during World War II. It’s also one of
the machines that the Polish Cipher Bureau and those at Britain’s Bletchley Park figured out how to decipher, 
or break. Most recently the story of how it was broken was the topic of the movie The Imitation Game.

More information about how it works at :
* [Hack A Day](https://hackaday.com/tag/enigma-machine/)
+ [Wikipedia](https://en.wikipedia.org/wiki/Enigma_machine)

# Code Examples 

Note : Two instances must be created ( one for encoding and one for decoding ) . As enigma encryption is symmetric it 
is necessary to use the same configuration of the instance used for encoding in the instance that will be used for decoding.

## C++ Snippets

### C++ Enigma Configuration
```cc
    std::shared_ptr<enigma> cypher = std::make_shared<enigma>();
    (*cypher).manage_reflector_load( reflector::load_reflector_path( "B" ) );
    (*cypher).manage_rotor_load(
      rotor::load_rotor_path("I") , rotor::load_rotor_path("V") , 
      rotor::load_rotor_path("IV") , rotor::load_rotor_path("VII")
    );
    (*cypher).ringstellum('A','(','/','f');
    (*cypher).manage_plugboard_connections(4,54);
    (*cypher).manage_plugboard_connections(90,24);
    (*cypher).manage_plugboard_connections(5,75);
    (*cypher).manage_plugboard_connections(84,31);
```

### C++ Encryption Code Example
```cc
  int mode = 0;
  switch (mode) {
    case 0 :{
      (*cypher).encode_string(msg_for_enigma);
      break;
    }
    case 1 :{
      (*cypher).decode_string(msg_for_enigma);
      break;
    }
  }

```

### C++ Rotor Files Generation
```cc
  auto rotor_names = { "R1" , "R2" , "R3" };

  for( auto rotor_name : rotor_names ){
    gen_rotors( rotor_name );
  }

```

### C++ Reflector Files Generation
```cc
  auto reflector_names = { "RFL1" , "RFL2" , "RFL3" };

  for( auto reflector_name : reflector_names ){
    gen_reflector( reflector_name );
  }

```

## Python Snippets

### Python Enigma Configuration Code Example
```python
import libenigma

STATIC_ROTOR = libenigma.rotor()
STATIC_REFLECTOR = libenigma.reflector()

def main():

    msg_for_enigma = "Alea Jacta Est!"
    cypher = libenigma.enigma()

    cypher.manage_rotor_load( STATIC_ROTOR.load_rotor_path("I") ,
                            STATIC_ROTOR.load_rotor_path("III") ,
                            STATIC_ROTOR.load_rotor_path("IV")  ,
                            STATIC_ROTOR.load_rotor_path("V")
     )
    cypher.manage_reflector_load( STATIC_REFLECTOR.load_reflector_path( "A" ) )
    cypher.manage_plugboard_connections(15,94)
    cypher.manage_plugboard_connections(74,31)
    cypher.ringstellum( 'A' , 'c' , '#' , 'p' )

```

### Python Desencyption Code Example
```python
    mode : int = 0
    msg = "Alea jacta est"
    match mode:
        case 0:
            msg = enigma.py_encode_string( msg )
        case 1:
            msg = enigma.py_decode_string( msg )
```

### Python Rotor Files Generation
```python
import libenigma.gen_rotors as grot

def main():

    rotor_names : list = [ "R1" , "R2" , "R3" , "R4" ]

    for rotor_name in rotor_names:
      grot( rotor_names )
```

### Python Reflector Fies Generation
```python
import libenigma.gen_reflectors as gref

def main():

    reflector_names : list = [ "RFL1" , "RFL2" , "RFL3" , "RFL4" ]

    for reflector_name in reflector_names:
      gref( reflector_names )
```

 ### Zig Build
 ```bash
$ zig build
```
* PS : Cross plataform build for python lib is not possible
+ PS2 : The rotor's and reflector's foler must be in the same folder as the executable
```
-enigma_bin
|-main.py // depends on libenigma.so shared lib
|-libenigma.so 
|-execfile
|-reflector_files/
|-rotor_files/
```
