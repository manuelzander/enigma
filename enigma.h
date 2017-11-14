#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <string>
#include "helper.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"

using namespace std;

class Enigma {
private:
  int number_rotors;
  Plugboard plugboard;
  Rotor *rotor_array;
  Reflector reflector;

public:
  Enigma(int argc, char** argv){ //Constructor --> Move into enigma.cpp
    if (argc == 3){ //No rotor at all
      number_rotors = 0;
    }
    else if (argc >= 5){ //At least one rotor

      number_rotors = argc - 4;
      cout << endl << "Number of rotors: " << number_rotors << endl;
      int argc_temp = argc - 2;

      //Creating dynamic array for the rotors
      this->rotor_array = new Rotor[number_rotors];

      //Loading rotor objects into the dynamic array
      for (int i = 0; i < number_rotors; i++){
        rotor_array[i] = Rotor();
      }

      // Load the rotor config in each rotor
      for (int i = 0; i < number_rotors; i++){
        cout << endl << "Loading config for rotor " << i << " with argc " << argc_temp << endl;
        rotor_array[i].loadRotor(argv[argc_temp]);
        argc_temp--;
      }

      // Load the rotor poitions in each rotor
      for (int i = number_rotors-1; i >= 0; i--){
        rotor_array[i].loadRotorPosition(argv[argc - 1], i, number_rotors);
      }
    }

    plugboard.checkPlugboardConfig(argv[1]);
    plugboard.loadPlugboard(argv[1]);
    reflector.loadReflector(argv[2]);

  }

  ~Enigma(){
    delete [] rotor_array; //Free memory
  }

  char encode(char c);
  char runRotors(char c);
  char runRotorsBack(char c);
  void turnRotors();
};

#endif
